/***************************************************************
*
* I2C - Two Wire Interface (TWI) Hardware Definition for ATMEGA328P
* Author: Simon Reinbold
* Last Update: 26.03.2018
*
***************************************************************/

#ifndef _TWI_
#define _TWI_

// General Settings

#define F_SCL 100000UL
#define MAX_PAYLOAD 12

// Pin Configuration

#define TWI_REG 	DDRC
#define TWI_PORT 	PORTC
#define TWI_SDA		PC4
#define TWI_SCL		PC5

// Status Mask

#define STATUS_MASK 0xF8

// Read/Write command

#define READ 		0x01
#define WRITE 		0x00

/*******************************
*
* Error Flags
*
********************************/

#define OK_FLG 						255
#define M_ARBITRATION_LOST_FLG		1
#define M_SLAW_NACK_RECEIVED_FLG	2
#define M_DATA_NACK_RECEIVED_FLG	3
#define M_SLAR_NACK_RECEIVED_FLG	4
#define OTHER_FLG					5

/*******************************
*
* Status Codes
*
********************************/

// Miscellaneous States

#define NO_STATE_INFO_AVAILABLE 	0xF8
#define BUS_ERROR 					0x00

// Master Mode (Enter by transmitting START condtion)

#define M_START 					0x08
#define M_START_REP 				0x10
#define M_ARBITRATION_LOST 			0x38

// Master Transmitter Submode (Enter by transmitting SLA+W)

#define M_SLAW_ACK_RECEIVED 		0x18
#define M_SLAW_NACK_RECEIVED 		0x20
#define M_DATA_ACK_RECEIVED 		0x28
#define M_DATA_NACK_RECEIVED 		0x30

// Master Receiver Submode (Enter by transmitting SLA+R)

#define M_SLAR_ACK_RECEIVED 		0x40
#define M_SLAR_NACK_RECEIVED 		0x48
#define M_DATA_ACK_SENT 			0x50
#define M_DATA_NACK_SENT 	 		0x58

// Slave Mode (Slave mode not yet implemented in this environment - status codes however are listed)

// Slave Transmitter Submode

#define S_SLAR_ACK_SENT 			0xA8
#define S_SLAR_ARBITRATION_LOST 	0xB0
#define S_DATA_SENT_ACK_RECEIVED	0xB8
#define S_DATA_SENT_NACK_RECEIVED	0xC0
#define S_LAST_DATA_ACK_RECEIVED 	0xC8

// Slave Receiver Submode

#define S_SLAW_ACK_SENT 			0x60
#define S_SLAW_ARBITRATION_LOST 	0x68
#define S_GENERAL_ACK_SENT 			0x70
#define S_GENERAL_ARBITRATION_LOST 	0x78
#define S_PREV_SLAW_ACK_SENT		0x80
#define S_PREV_SLAW_NACK_SENT		0x88
#define S_PREV_GENERAL_ACK_SENT		0x90
#define S_PREV_GENERAL_NACK_SENT	0x98
#define S_STOP_OR_START_RECEIVED 	0xA0

/*******************************
*
* Variable Definitions
*
********************************/

#define STAT_READY 0
#define STAT_IS_READING 1

volatile struct{
	uint8_t status;
	uint8_t byte_cnt;
	uint8_t payload_length;
}twi_control;

uint8_t payload[MAX_PAYLOAD];
volatile uint8_t error_FLG;

/*******************************
*
* Function Definitions
*
********************************/

void init_twi();
uint8_t send_START();
uint8_t send_STOP();
uint8_t transmit_read(uint8_t address, uint8_t nbytes_to_receive);
uint8_t transmit_write(uint8_t address);
uint8_t transmit_data(uint8_t data);
uint8_t send_data(uint8_t *msg, uint8_t msgSize);
uint8_t wait_until_ready();
uint8_t master_read_register(uint8_t slave_address, uint8_t register_address, uint8_t nbytes);
uint8_t master_config_register(uint8_t slave_address, uint8_t register_address, uint8_t data);
uint8_t master_write_register(uint8_t slave_address, uint8_t register_address, uint8_t *data, uint8_t nbytes);

#endif /* _TWI_ */