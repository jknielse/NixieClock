EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74LS145 U3
U 1 1 560DE655
P 5000 3000
F 0 "U3" H 5000 3000 60  0000 C CNN
F 1 "74LS145" H 4950 2700 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 5000 3000 60  0001 C CNN
F 3 "" H 5000 3000 60  0000 C CNN
	1    5000 3000
	1    0    0    -1  
$EndComp
$Comp
L 74LS145 U2
U 1 1 560DE6F9
P 5000 1700
F 0 "U2" H 5000 1700 60  0000 C CNN
F 1 "74LS145" H 4950 1400 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 5000 1700 60  0001 C CNN
F 3 "" H 5000 1700 60  0000 C CNN
	1    5000 1700
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U1
U 1 1 560DE829
P 3150 2350
F 0 "U1" H 3300 2950 70  0000 C CNN
F 1 "74HC595" H 3150 1750 70  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 3150 2350 60  0001 C CNN
F 3 "" H 3150 2350 60  0000 C CNN
	1    3150 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 1900 3850 1550
Wire Wire Line
	3850 1550 4400 1550
Wire Wire Line
	3850 2000 3950 2000
Wire Wire Line
	3950 2000 3950 1650
Wire Wire Line
	3950 1650 4400 1650
Wire Wire Line
	3850 2100 4050 2100
Wire Wire Line
	4050 2100 4050 1750
Wire Wire Line
	4050 1750 4400 1750
Wire Wire Line
	3850 2200 4150 2200
Wire Wire Line
	4150 2200 4150 1850
Wire Wire Line
	4150 1850 4400 1850
Wire Wire Line
	3850 2300 4400 2300
Wire Wire Line
	4400 2300 4400 2850
Wire Wire Line
	3850 2400 4300 2400
Wire Wire Line
	4300 2400 4300 2950
Wire Wire Line
	4300 2950 4400 2950
Wire Wire Line
	3850 2500 4200 2500
Wire Wire Line
	4200 2500 4200 3050
Wire Wire Line
	4200 3050 4400 3050
Wire Wire Line
	3850 2600 4100 2600
Wire Wire Line
	4100 2600 4100 3150
Wire Wire Line
	4100 3150 4400 3150
$Comp
L GND #PWR01
U 1 1 560DE8FD
P 2350 2700
F 0 "#PWR01" H 2350 2450 50  0001 C CNN
F 1 "GND" H 2350 2550 50  0000 C CNN
F 2 "" H 2350 2700 60  0000 C CNN
F 3 "" H 2350 2700 60  0000 C CNN
	1    2350 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 2200 2350 2700
Wire Wire Line
	2350 2500 2450 2500
Text Label 1100 2400 0    60   ~ 0
display_data
Wire Wire Line
	2350 2200 2450 2200
Connection ~ 2350 2500
Wire Wire Line
	850  2400 2450 2400
Text Label 1100 2200 0    60   ~ 0
clock_data
Text Label 1100 2000 0    60   ~ 0
data
Wire Wire Line
	850  2000 2450 2000
Wire Wire Line
	2450 2000 2450 1900
Wire Wire Line
	900  2200 1900 2200
Wire Wire Line
	1900 2200 1900 2100
Wire Wire Line
	1900 2100 2450 2100
$Comp
L VCC #PWR02
U 1 1 560DEB03
P 1850 2600
F 0 "#PWR02" H 1850 2450 50  0001 C CNN
F 1 "VCC" H 1850 2750 50  0000 C CNN
F 2 "" H 1850 2600 60  0000 C CNN
F 3 "" H 1850 2600 60  0000 C CNN
	1    1850 2600
	1    0    0    -1  
$EndComp
Text Label 1100 2600 0    60   ~ 0
power_in
Text Label 1100 2800 0    60   ~ 0
high_power_in
Text Label 1100 3000 0    60   ~ 0
gnd_in
Wire Wire Line
	1100 2600 1850 2600
$Comp
L VDD #PWR03
U 1 1 560DEB6F
P 1850 2800
F 0 "#PWR03" H 1850 2650 50  0001 C CNN
F 1 "VDD" H 1850 2950 50  0000 C CNN
F 2 "" H 1850 2800 60  0000 C CNN
F 3 "" H 1850 2800 60  0000 C CNN
	1    1850 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 560DEB8C
P 1850 3000
F 0 "#PWR04" H 1850 2750 50  0001 C CNN
F 1 "GND" H 1850 2850 50  0000 C CNN
F 2 "" H 1850 3000 60  0000 C CNN
F 3 "" H 1850 3000 60  0000 C CNN
	1    1850 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 2800 1850 2800
Wire Wire Line
	1000 3000 1850 3000
$Comp
L CONN_01X06 P1
U 1 1 560DEC1A
P 650 2450
F 0 "P1" H 650 2800 50  0000 C CNN
F 1 "CONN_01X06" V 750 2450 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_1x06" H 650 2450 60  0001 C CNN
F 3 "" H 650 2450 60  0000 C CNN
	1    650  2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	850  2200 850  2000
Wire Wire Line
	850  2300 900  2300
Wire Wire Line
	900  2300 900  2200
Wire Wire Line
	850  2500 1100 2500
Wire Wire Line
	1100 2500 1100 2600
Wire Wire Line
	850  2600 1050 2600
Wire Wire Line
	1050 2600 1050 2800
Wire Wire Line
	850  2700 1000 2700
Wire Wire Line
	1000 2700 1000 3000
$Comp
L CONN_01X06 P2
U 1 1 560DEF53
P 3050 3850
F 0 "P2" H 3050 4200 50  0000 C CNN
F 1 "CONN_01X06" V 3150 3850 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Angled_1x06" H 3050 3850 60  0001 C CNN
F 3 "" H 3050 3850 60  0000 C CNN
	1    3050 3850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR05
U 1 1 560DEF9D
P 3300 3650
F 0 "#PWR05" H 3300 3400 50  0001 C CNN
F 1 "GND" H 3300 3500 50  0000 C CNN
F 2 "" H 3300 3650 60  0000 C CNN
F 3 "" H 3300 3650 60  0000 C CNN
	1    3300 3650
	-1   0    0    1   
$EndComp
$Comp
L VDD #PWR06
U 1 1 560DEFC0
P 3200 3650
F 0 "#PWR06" H 3200 3500 50  0001 C CNN
F 1 "VDD" H 3200 3800 50  0000 C CNN
F 2 "" H 3200 3650 60  0000 C CNN
F 3 "" H 3200 3650 60  0000 C CNN
	1    3200 3650
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR07
U 1 1 560DEFE3
P 3100 3650
F 0 "#PWR07" H 3100 3500 50  0001 C CNN
F 1 "VCC" H 3100 3800 50  0000 C CNN
F 2 "" H 3100 3650 60  0000 C CNN
F 3 "" H 3100 3650 60  0000 C CNN
	1    3100 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2400 2200 3150
Wire Wire Line
	2200 3150 3000 3150
Wire Wire Line
	3000 3150 3000 3650
Connection ~ 2200 2400
Wire Wire Line
	2100 2100 2100 3250
Wire Wire Line
	2100 3250 2900 3250
Wire Wire Line
	2900 3250 2900 3650
Connection ~ 2100 2100
Wire Wire Line
	3850 2800 3850 3350
Wire Wire Line
	3850 3350 2800 3350
Wire Wire Line
	2800 3350 2800 3650
$Comp
L VDD #PWR08
U 1 1 560DF8C4
P 6400 1000
F 0 "#PWR08" H 6400 850 50  0001 C CNN
F 1 "VDD" H 6400 1150 50  0000 C CNN
F 2 "" H 6400 1000 60  0000 C CNN
F 3 "" H 6400 1000 60  0000 C CNN
	1    6400 1000
	0    1    1    0   
$EndComp
$Comp
L CONN_01X11 P3
U 1 1 560DF96A
P 5800 1650
F 0 "P3" H 5800 2250 50  0000 C CNN
F 1 "CONN_01X11" V 5900 1650 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x11" H 5800 1650 60  0001 C CNN
F 3 "" H 5800 1650 60  0000 C CNN
	1    5800 1650
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X11 P4
U 1 1 560DFA5D
P 5800 2950
F 0 "P4" H 5800 3550 50  0000 C CNN
F 1 "CONN_01X11" V 5900 2950 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x11" H 5800 2950 60  0001 C CNN
F 3 "" H 5800 2950 60  0000 C CNN
	1    5800 2950
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR09
U 1 1 560DFA94
P 6400 2300
F 0 "#PWR09" H 6400 2150 50  0001 C CNN
F 1 "VDD" H 6400 2450 50  0000 C CNN
F 2 "" H 6400 2300 60  0000 C CNN
F 3 "" H 6400 2300 60  0000 C CNN
	1    6400 2300
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 560DFB26
P 6150 1000
F 0 "R1" V 6230 1000 50  0000 C CNN
F 1 "68K" V 6150 1000 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 6080 1000 30  0001 C CNN
F 3 "" H 6150 1000 30  0000 C CNN
	1    6150 1000
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 560DFBE3
P 6150 2300
F 0 "R2" V 6230 2300 50  0000 C CNN
F 1 "68K" V 6150 2300 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 6080 2300 30  0001 C CNN
F 3 "" H 6150 2300 30  0000 C CNN
	1    6150 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 2300 6400 2300
Wire Wire Line
	6300 1000 6400 1000
Wire Wire Line
	6000 1000 5600 1000
Wire Wire Line
	5600 1000 5600 1150
Wire Wire Line
	5600 2450 5600 2300
Wire Wire Line
	5600 2300 6000 2300
$Comp
L PWR_FLAG #FLG010
U 1 1 560E009D
P 1650 2600
F 0 "#FLG010" H 1650 2695 50  0001 C CNN
F 1 "PWR_FLAG" H 1650 2780 50  0000 C CNN
F 2 "" H 1650 2600 60  0000 C CNN
F 3 "" H 1650 2600 60  0000 C CNN
	1    1650 2600
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG011
U 1 1 560E00CA
P 1650 2800
F 0 "#FLG011" H 1650 2895 50  0001 C CNN
F 1 "PWR_FLAG" H 1650 2980 50  0000 C CNN
F 2 "" H 1650 2800 60  0000 C CNN
F 3 "" H 1650 2800 60  0000 C CNN
	1    1650 2800
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG012
U 1 1 560E00F0
P 1650 3000
F 0 "#FLG012" H 1650 3095 50  0001 C CNN
F 1 "PWR_FLAG" H 1650 3180 50  0000 C CNN
F 2 "" H 1650 3000 60  0000 C CNN
F 3 "" H 1650 3000 60  0000 C CNN
	1    1650 3000
	1    0    0    -1  
$EndComp
Connection ~ 1650 3000
Connection ~ 1650 2800
Connection ~ 1650 2600
$EndSCHEMATC
