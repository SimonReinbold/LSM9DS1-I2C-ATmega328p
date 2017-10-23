#include <avr/io.h>
#include <avr/interrupt.h>
#include "twi.h"

void init_twi(){
	// Disable Power Reduction TWI
	PRR &= ~(1<<TWI0);

	// CPU in Slave must be at least 16 time higher than SCL frequency
	// ATmega328p CPU clock: 20 MHz
	TWSR &= ~( (0<<TWPS1) | (1<<TWPS0) ) 	// Set Prescaler to 1 - if changed it has to be considered below as well
	TWBR = (uint8_t) ( (uint16_t)( (uint32_t) F_CPU/ (uint32_t)F_SCL ) -16)/2;	// Calc Bitrate

	// Enable TWI Interrupt, Acknowledgement and TWI itself	
	TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWEN); // Enable ACK

	twi_control.ready = 1;
	twi_control.is_reading = 0;
	twi_control.byte_cnt = 0;
	twi_control.payload_length = 0;
}

void send_START(){
	wait_until_ready();
	twi_control.ready = 0;
	TWCR |= (1<<TWINT)| (1<<TWSTA);
}

void send_STOP(){
	wait_until_ready();
	twi_control.ready = 0;
	TWCR |= (1<<TWINT)| (1<<TWSTO);
}

void send_NMACK(){
	wait_until_ready();
	twi_control.ready = 0;
	TWCR &= ~(1<<TWEA); // Clear the enable acknowledge flag to virtually disconnect the device
	TWCR |= (1<<TWINT);	// Send
}

void transmit_read(uint8_t address, uint8_t nbytes_to_receive){
	wait_until_ready();
	twi_control.ready = 0;
	twi_control.is_reading = 1;
	twi_control.byte_cnt = 0; 							// Reset byte counter
	twi_control.payload_length = nbytes_to_receive;
	TWDR |= address | READ;
	TWCR |= (1<<TWINT);
}

void transmit_write(uint8_t address){
	wait_until_ready();
	twi_control.ready = 0;
	TWDR = address | WRITE;
	TWCR |= (1<<TWINT);
}

// Transmit one data byte
void transmit_data(uint8_t data){
	wait_until_ready();
	twi_control.ready = 0;
	TWDR = data;
	TWCR |= (1<<TWINT);
}

// Transmit multiple bytes
void send_data(uint8_t *msg, uint8_t msgSize){
	for(uint8_t i = 0; i < msgSize; i++){
		transmit_data(*msg);
		msg++;
	}
}

uint8_t wait_until_ready(){
	while(~twi_control.ready);
}

/****************************
* Check for TWI Status
****************************/
ISR(TWI_vect){
	uint8_t status = TWSR & STATUS_MASK; // Mask Status Flag to neglect Prescaler Value

	switch status{
		case M_START; // Do nothing
		case M_START_REP;
		case M_SLAW_ACK_RECEIVED;
		case M_SLAR_ACK_RECEIVED:
			// First Data Byte is received here
			payload[twi_control.byte_cnt] = TWDR;
			twi_control.byte_cnt++;
		case M_DATA_ACK_RECEIVED; 
		case M_DATA_ACK_SENT:
			// Receive further data bytes
			payload[twi_control.bytete_cnt] = TWDR;
			twi_control.byte_cnt++;
		case M_DATA_NACK_SENT:
			// Receive last data byte
			payload[twi_control.bytete_cnt] = TWDR;
			TWCR |= (1<<TWEA); 			// Reconnect after the virtual disconnect - to send ACK
			twi_control.is_reading = 0; // Reset Read Flag at the ent of a read cycle
		default: error = 1;
	}

	// Run just in (master) receiver mode
	if(twi_control.is_reading){
		if(twi_control.byte_cnt == twi_control.payload_length-1){
			// Penultimate byte received - Receive last byte and send NO ACK
			send_NMACK();
		}else{
			// Receive next byte and send ACK
			TWCR |= (1<<TWINT);
		}
	}

	if(~error){
		twi_control.ready = 1; // Reset Ready-Flag
	}
}