#!/usr/bin/python

import shapefile
from datetime import datetime
import pytz
import argparse
import pprint
import struct
import sys
import os


parser = argparse.ArgumentParser()

parser.add_argument('-r', '--regions', default=False, action='store_true')
parser.add_argument('-m', '--map', default=False, action='store_true')

args = parser.parse_args()

SCRIPT_DIR = os.path.abspath(os.path.dirname(__file__))
SD_DIR = os.path.join(SCRIPT_DIR, 'sdcard')
if not os.path.exists(SD_DIR):
    os.makedirs(SD_DIR)

# This is more for my memory than anything.
def lat_to_offset(lat, slice_depth):
    d = 180.0 / (2 ** (slice_depth + 1))
    return int((lat - 90) / -d - 1)

def is_between(p1, p2, lat):
    return (p1[1] < lat and lat < p2[1]) or (p2[1] < lat and lat < p1[1])

def get_midpoint_at_lattitude(p1, p2, lat):
    if is_between(p1, p2, lat):
        d = [p2[1] - p1[1], p2[0] - p1[0]]
        a = abs(lat - p1[1])
        return [p1[1] + d[0] * a, p1[0] + d[1] * a]

def is_entering(p1, p2, lat):
    return is_between(p1, p2, lat) and p2[1] >= p1[1]

def is_leaving(p1, p2, lat):
    return is_between(p1, p2, lat) and p2[1] <= p1[1]

def slice_timezones(shape_info, high_lat, low_lat, depth):
    # first we slice the shapes at the midpoint between high_lat and low_lat:
    lat = (high_lat + low_lat)/2.0

    slice_points = []
    lower_shape_info = []
    upper_shape_info = []
    for info in shape_info:
        shape = info[0]
        lower_shape = []
        upper_shape = []
        for i in range(0, len(shape)):
            p1 = shape[i-1]
            p2 = shape[i]

            if p1[1] < lat:
                lower_shape.append(p1)
            else:
                upper_shape.append(p1)
            if is_between(p1, p2, lat):
                if is_entering(p1, p2, lat):
                    lower_shape.append(p2)
                    upper_shape.append(p1)
                    slice_points.append((get_midpoint_at_lattitude(p1, p2, lat)[1], info[1]))
                else:
                    lower_shape.append(p1)
                    upper_shape.append(p2)

        if lower_shape:
            lower_shape_info.append((lower_shape, info[1]))
        if upper_shape:
            upper_shape_info.append((upper_shape, info[1]))
    slice_points.sort()

    if depth > 0:
        for s in slice_timezones(upper_shape_info, high_lat, lat, depth - 1):
            yield s
        yield slice_points
        for s in slice_timezones(lower_shape_info, lat, low_lat, depth - 1):
            yield s

    else:
        yield slice_points



sf = shapefile.Reader('world/tz_world')
boundaries = sf.shapes()
records = sf.records()


# we can do a divide and conquer algorithm to progressively subdivide the shapes into
# slices to avoid re-checking line segments that are way off-base.

# really, we want to slice the world into 1,800,000 slices (to get ~10m hashing)


# shape_info is a list of tuples of shapes and corresponding timezone
# so it looks like this: [(shape, timezone), (shape, timezone), ...]

tz_name_to_number = {}
tz_number_to_name = {}

n = 0
for rec in records:
    if rec[0] == 'uninhabited':
        continue
    if rec[0] not in tz_name_to_number:
        tz_name_to_number[rec[0]] = n
        tz_number_to_name[n] = rec[0]
        n += 1

shape_info = []

for i in range(0, len(boundaries)):
    if records[i][0] == 'uninhabited':
        continue
    shape_info.append((boundaries[i].points, tz_name_to_number[records[i][0]]))


if args.map:
    slice_depth = 21
    slice_count = 0
    total_count = 2 ** (slice_depth + 1)
    update_freq = total_count/1000
    update_num = 0

    with open(os.path.join(SD_DIR, 'timezone.hsh'), 'wb') as f:
        for s in slice_timezones(shape_info, 90.0, -90.0, slice_depth):
            slice_count += 1
            if slice_count % update_freq == 0:
                update_num += 1
                sys.stdout.write('\r{:>6.1%} Complete'.format(update_num/1000.0))
                sys.stdout.flush()
            c = 0
            for b in s:
                # 4 bytes
                f.write(struct.pack('f', b[0]))
                # 2 bytes
                f.write(struct.pack('h', b[1]))
                c += 1
            while c < 140:
                f.write(struct.pack('f', -1000.0))
                f.write(struct.pack('h', 0))
                c += 1
            if c > 140:
                # Note to self: 136 seems to be the most we hit.
                print ('Crap, there are too many timezone changes in this slice.')
                print (c)
                exit(1)
        print

def seconds_since_epoch(time):
    epoch = datetime.utcfromtimestamp(0)
    return (time - epoch).total_seconds()

override_map = {
    'America/Fort_Nelson': 'Canada/Mountain',
    'Indian/Christmas': 'Asia/Jakarta',
    'Asia/Srednekolymsk': 'Etc/GMT+11',
    'Asia/Chita': 'Etc/GMT+8',
    'Pacific/Bougainville': 'Etc/GMT+11',
}

# ourtz = datetime.now(pytz.timezone('America/Los_Angeles')).tzinfo


# for i in range(140, 180):
#     print round(seconds_since_epoch(ourtz._utc_transition_times[i]))
#     print ":".join("{:02x}".format(ord(c)) for c in struct.pack('I', round(seconds_since_epoch(ourtz._utc_transition_times[i]))))

# print
# ind = 141
# pprint.PrettyPrinter().pprint(seconds_since_epoch(ourtz._utc_transition_times[ind]))
# pprint.PrettyPrinter().pprint(ourtz._transition_info[ind][0].total_seconds() + ourtz._transition_info[ind][1].total_seconds())

m = 0

if args.regions:
    for region in tz_name_to_number:
        if region in override_map:
            t = datetime.now(pytz.timezone(override_map[region]))
        else:
            t = datetime.now(pytz.timezone(region))

        c = 1

        filename = '{}.tfl'.format(tz_name_to_number[region])
        transitions = []
        transition_times = []

        if '_transition_info' in dir(t.tzinfo):
            transitions = t.tzinfo._transition_info
            transition_times = t.tzinfo._utc_transition_times

        with open(os.path.join(SD_DIR, filename), 'wb') as f:
            f.write(struct.pack('i', int(t.tzinfo.utcoffset(t).total_seconds())))
            for i in range(0, len(transitions)):
                c += 2
                # If the time transition is before now, then we really don't need to worry about it.
                if (transition_times[i] < datetime.utcfromtimestamp(0)):
                    continue
                if (transition_times[i] < datetime.now()):
                    continue
                f.write(struct.pack('I', int(seconds_since_epoch(transition_times[i]))))
                f.write(struct.pack('i', int(transitions[i][0].total_seconds())))
        m = max(c, m)
    print (m)

