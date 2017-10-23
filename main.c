#include <avr/io.h>
#include "twi.h"
#include "LSM9DS1.h"

#define ACCEL_DATA_LENGTH 0

void main(){
	init_twi();


}

void get_acceleration_data(){
	send_START();
	transmit_write(ADDR_ACC_GYRO); 					// Address Accel
	transmit_data();								//TODO Sub-Register
	send_START(); 									// Repeat Start
	transmit_read(ADDR_ACC_GYRO,ACCEL_DATA_LENGTH);
	while(twi_control.is_reading);					// Wait until all bytes are read
	send_STOP();
}