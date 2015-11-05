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
LIBS:NixieComponentLibrary
LIBS:russian-nixies
LIBS:NixieDisplayBoard-cache
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
L IN-12B N1
U 1 1 563969E1
P 6900 1850
F 0 "N1" H 6725 2675 50  0000 L BNN
F 1 "IN-12B" H 6900 1850 50  0000 L BNN
F 2 "IN12B:russian-nixies-IN-12" H 6900 2000 50  0001 C CNN
F 3 "" H 6900 1850 60  0000 C CNN
	1    6900 1850
	1    0    0    -1  
$EndComp
$Comp
L IN-12B N2
U 1 1 56396A4D
P 6900 3550
F 0 "N2" H 6725 4375 50  0000 L BNN
F 1 "IN-12B" H 6900 3550 50  0000 L BNN
F 2 "IN12B:russian-nixies-IN-12" H 6900 3700 50  0001 C CNN
F 3 "" H 6900 3550 60  0000 C CNN
	1    6900 3550
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X12 P1
U 1 1 56396AB9
P 5750 1700
F 0 "P1" H 5750 2350 50  0000 C CNN
F 1 "CONN_01X12" V 5850 1700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x12" H 5750 1700 60  0001 C CNN
F 3 "" H 5750 1700 60  0000 C CNN
	1    5750 1700
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X12 P2
U 1 1 56396B24
P 5750 3400
F 0 "P2" H 5750 4050 50  0000 C CNN
F 1 "CONN_01X12" V 5850 3400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x12" H 5750 3400 60  0001 C CNN
F 3 "" H 5750 3400 60  0000 C CNN
	1    5750 3400
	-1   0    0    1   
$EndComp
Wire Wire Line
	5950 1150 5950 1000
Wire Wire Line
	5950 1000 5500 1000
Wire Wire Line
	5500 1000 5500 2400
Wire Wire Line
	5500 2400 6400 2400
Wire Wire Line
	6400 2400 6400 2250
Wire Wire Line
	5950 1250 6100 1250
Wire Wire Line
	6100 1250 6100 900 
Wire Wire Line
	6100 900  7300 900 
Wire Wire Line
	7300 900  7300 1350
Wire Wire Line
	5950 2850 5950 2700
Wire Wire Line
	5950 2700 5500 2700
Wire Wire Line
	5500 2700 5500 4100
Wire Wire Line
	5500 4100 6400 4100
Wire Wire Line
	6400 4100 6400 3950
Wire Wire Line
	5950 2950 6100 2950
Wire Wire Line
	6100 2950 6100 2600
Wire Wire Line
	6100 2600 7300 2600
Wire Wire Line
	7300 2600 7300 3050
Wire Wire Line
	5950 3050 6400 3050
Wire Wire Line
	5950 3150 6400 3150
Wire Wire Line
	5950 3250 6400 3250
Wire Wire Line
	5950 3350 6400 3350
Wire Wire Line
	5950 3450 6400 3450
Wire Wire Line
	5950 3550 6400 3550
Wire Wire Line
	5950 3650 6400 3650
Wire Wire Line
	5950 3750 6400 3750
Wire Wire Line
	5950 3850 6400 3850
Wire Wire Line
	5950 1350 6400 1350
Wire Wire Line
	5950 1450 6400 1450
Wire Wire Line
	5950 1550 6400 1550
Wire Wire Line
	5950 1650 6400 1650
Wire Wire Line
	5950 1750 6400 1750
Wire Wire Line
	5950 1850 6400 1850
Wire Wire Line
	5950 1950 6400 1950
Wire Wire Line
	5950 2050 6400 2050
Wire Wire Line
	5950 2150 6400 2150
Wire Wire Line
	5950 2250 5950 2550
Wire Wire Line
	5950 2550 7300 2550
Wire Wire Line
	7300 2550 7300 1850
Wire Wire Line
	5950 3950 5950 4250
Wire Wire Line
	5950 4250 7300 4250
Wire Wire Line
	7300 4250 7300 3550
$EndSCHEMATC
