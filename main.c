#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "I2C/twi.h"
#include "LSM9DS1/LSM9DS1.h"
#include "4bit-LCD/lcd-routines.h"

#define ACCEL_DATA_LENGTH 0

extern uint8_t payload[MAX_PAYLOAD];

void main(){
	init_twi();
	lcd_init();

	sei();

	// Debug LED
	PORTB &= ~(1<<PB1);

	while(1){
			if(master_read_register(ADDR_ACC_GYRO,WHO_AM_I,1) == OK_FLG){
				// Data Valid
				lcd_clear();
				lcd_setcursor(0,1);
				lcd_string("Payload:");
				display(payload,1,2);
			}
	}
}

void get_acceleration_data(){
	send_START();
	transmit_write(ADDR_ACC_GYRO); 					// Address Accel
	//transmit_data();								//TODO Sub-Register
	send_START(); 									// Repeat Start
	transmit_read(ADDR_ACC_GYRO,ACCEL_DATA_LENGTH);
	while(twi_control.status & (1<<STAT_IS_READING));					// Wait until all bytes are read
}