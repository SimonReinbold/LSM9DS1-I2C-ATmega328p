/***************************************************************
*
* I2C - Two Wire Interface (TWI) Protocol
* Author: Simon Reinbold
* Last Update: 26.03.2018
*
***************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "twi.h"

void init_twi(){
	// Disable Power Reduction TWI
	//PRR &= ~(1<<PRTWI);
	TWCR = 0;
	// CPU in Slave must be at least 16 time higher than SCL frequency
	// ATmega328p CPU clock: 16 MHz
	//TWSR &= ~( (1<<TWPS1) | (1<<TWPS0) ); 	// Set Prescaler to 1 - if changed it has to be considered below as well
	TWBR = (uint8_t) ( (uint16_t)( (uint32_t) F_CPU/ (uint32_t)F_SCL ) -16)/2;	// Calc Bitrate

	twi_control.status = (1<<STAT_READY) | (0<<STAT_IS_READING);
	twi_control.byte_cnt = 0;
	twi_control.payload_length = 0;

	error_FLG = OK_FLG;
}

uint8_t send_START(){
	twi_control.status &= ~(1<<STAT_READY);
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWIE);
	return wait_until_ready();
}

uint8_t send_STOP(){
	twi_control.status &= ~(1<<STAT_READY);
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
	return wait_until_ready();
}

uint8_t transmit_read(uint8_t address, uint8_t nbytes_to_receive){
	twi_control.status &= ~(1<<STAT_READY);
	twi_control.status |= (1<<STAT_IS_READING);
	twi_control.byte_cnt = 0; 							// Reset byte counter
	twi_control.payload_length = nbytes_to_receive;
	TWDR = (address<<1) | READ;
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
	return wait_until_ready();
}

uint8_t transmit_write(uint8_t address){
	twi_control.status &= ~(1<<STAT_READY);
	TWDR = (address<<1) | WRITE;
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
	return wait_until_ready();
}

// Transmit one data byte
uint8_t transmit_data(uint8_t data){
	twi_control.status &= ~(1<<STAT_READY);
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE);
	return wait_until_ready();
}

// Transmit multiple bytes
uint8_t send_data(uint8_t *msg, uint8_t msgSize){
	for(uint8_t i = 0; i < msgSize; i++){
		if(transmit_data(*msg) != OK_FLG) return error_FLG;
		msg++;
	}
	return OK_FLG;
}

uint8_t wait_until_ready(){
	while(!(twi_control.status & (1<<STAT_READY)));
	_delay_us(100);
	return error_FLG;
}

uint8_t master_read_register(uint8_t slave_address, uint8_t register_address, uint8_t nbytes){
	if(send_START() != OK_FLG) return error_FLG;
	_delay_us(100); // No delay leads to errors - don't know why
	if(transmit_write(slave_address) != OK_FLG) return error_FLG;
	_delay_us(100);
	if(transmit_data(register_address) != OK_FLG) return error_FLG;
	_delay_us(100);
	if(send_START() != OK_FLG) return error_FLG;
	_delay_us(100);
	if(transmit_read(slave_address,nbytes) != OK_FLG) return error_FLG;
	_delay_us(100);
	while( twi_control.status & (1<<STAT_IS_READING) ); // Wait until all bytes are read
	return OK_FLG;
}

uint8_t master_config_register(uint8_t slave_address, uint8_t register_address, uint8_t data){
	if(send_START() != OK_FLG) return error_FLG;
	_delay_us(100);
	if(transmit_write(slave_address) != OK_FLG) return error_FLG;
	_delay_us(100);
	if(transmit_data(register_address) != OK_FLG) return error_FLG;
	_delay_us(100);
	if(transmit_data(data) != OK_FLG) return error_FLG;
	_delay_us(100);
	if(send_STOP() != OK_FLG) return error_FLG;
	_delay_us(100);
	return OK_FLG;
}

uint8_t master_write_register(uint8_t slave_address, uint8_t register_address, uint8_t *data, uint8_t nbytes){
	if(send_START() != OK_FLG) return error_FLG;
	_delay_us(100);
	if(transmit_write(slave_address) != OK_FLG) return error_FLG;
	_delay_us(100);
	if(transmit_data(register_address) != OK_FLG) return error_FLG;
	_delay_us(100);
	if(send_data(data,nbytes) != OK_FLG) return error_FLG;
	_delay_us(100);
	if(send_STOP() != OK_FLG) return error_FLG;
	_delay_us(100);
	return OK_FLG;
}

/****************************
* Check for TWI Status
****************************/

ISR(TWI_vect){
	uint8_t status = TWSR & STATUS_MASK; // Mask Status Flag to neglect Prescaler Value
	
	// Reset READY flag
	twi_control.status |= (1<<STAT_READY);

	switch(status) {
		// Expected status
		case M_START:
			error_FLG = OK_FLG;
			break;
		case M_START_REP:
			error_FLG = OK_FLG;
			break;
		case M_SLAW_ACK_RECEIVED:
			error_FLG = OK_FLG;
			break;
		case M_SLAR_ACK_RECEIVED:
			error_FLG = OK_FLG;
			if(twi_control.payload_length < 2){
				TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE); // Clear the enable acknowledge flag to virtually disconnect the device
			}else{
				TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE) | (1<<TWEA);
			}			
			break;
		case M_DATA_ACK_RECEIVED:
			error_FLG = OK_FLG;
			break;
		case M_DATA_ACK_SENT:
			error_FLG = OK_FLG;
			// Receive data bytes	
			payload[twi_control.byte_cnt] = TWDR;
			twi_control.byte_cnt++;
			if(twi_control.byte_cnt == twi_control.payload_length-1){
				// Penultimate byte received - Receive last byte and send NO ACK
				TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE); // Clear the enable acknowledge flag to virtually disconnect the device
			}else{
				TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE) | (1<<TWEA);
			}
			break;
		case M_DATA_NACK_SENT:
			error_FLG = OK_FLG;
			// Receive last data byte
			payload[twi_control.byte_cnt] = TWDR;
			twi_control.status &= ~(1<<STAT_IS_READING); // Reset Read Flag at the ent of a read cycle
			TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN); // Reconnect after the virtual disconnect and send STOP
			break;
		// Unexpected status
		case M_ARBITRATION_LOST:
			error_FLG = M_ARBITRATION_LOST_FLG;
			break;
		case M_SLAW_NACK_RECEIVED:
			error_FLG = M_SLAW_NACK_RECEIVED_FLG;
			break;
		case M_DATA_NACK_RECEIVED:
			error_FLG = M_DATA_NACK_RECEIVED_FLG;
			break;
		case M_SLAR_NACK_RECEIVED:
			error_FLG = M_SLAR_NACK_RECEIVED_FLG;
			break;
		// Provided erros flags
		case BUS_ERROR:
			error_FLG = BUS_ERROR;	
			break;
		case NO_STATE_INFO_AVAILABLE:
			error_FLG = OK_FLG;
			break;
		default: 
			error_FLG = status;
			break;
	}
}