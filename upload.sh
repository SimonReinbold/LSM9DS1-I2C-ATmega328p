#!/bin/bash
#avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p main.c I2C/twi.c LSM9DS1/LSM9DS1.c 4bit-LCD/lcd-routines.c -o imu.o &&
#avr-gcc -mmcu=atmega328p imu.o -o imu &&
#avr-objcopy -O ihex -R .eeprom imu imu.hex &&
#avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:imu.hex
avr-gcc -g -Os -DF_CPU=16000000UL -mmcu=atmega328p -c main.c -o main.o &&
avr-gcc -g -Os -DF_CPU=16000000UL -mmcu=atmega328p -c I2C/twi.c -o twi.o &&
avr-gcc -g -Os -DF_CPU=16000000UL -mmcu=atmega328p -c LSM9DS1/LSM9DS1.c -o LSM9DS1.o &&
avr-gcc -g -Os -DF_CPU=16000000UL -mmcu=atmega328p -c 4bit-LCD/lcd-routines.c -o lcd-routines.o &&
avr-gcc -g -mmcu=atmega328p -o imu.elf main.o twi.o LSM9DS1.o lcd-routines.o &&
avr-objcopy -O ihex -R .eeprom imu.elf imu.hex &&
avrdude -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:imu.hex
