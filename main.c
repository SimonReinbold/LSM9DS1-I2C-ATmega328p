#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "I2C/twi.h"
#include "LSM9DS1/LSM9DS1.h"
#include "4bit-LCD/lcd-routines.h"
#include "USART/USART.h"

#define ACCEL_DATA_LENGTH 0

extern uint8_t payload[MAX_PAYLOAD];

void main(){
	init_twi();
	lcd_init();
	//USART_init();

	sei();

	// Debug LED
	PORTB &= ~(1<<PB1);

	// Activate gyro and acceleration module
	// For now hard coded values are used:
	uint8_t conf = 0b01101011;
	master_config_register(ADDR_ACC_GYRO, CTRL_REG1_G, conf);

	while(1){
		if(0){
			if(master_read_register(ADDR_ACC_GYRO,CTRL_REG1_G,1) == OK_FLG){
				// Data Valid
				lcd_clear();
				lcd_setcursor(0,1);
				lcd_string("Payload:");
				display(payload,1,2);
			}
		}
		if(1){
			uint8_t sign = get_acceleration_data();
		if(sign == 0){
			lcd_setcursor(0,1);
			lcd_data('-');
		}else{
			lcd_setcursor(0,1);
			lcd_data('+');
		}
		}
		
	}
}