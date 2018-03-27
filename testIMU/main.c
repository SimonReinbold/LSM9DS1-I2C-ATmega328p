#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
//#include "../LCD/lcd-routines.h"
#include "../USART/USART.h"
#include "imu.h"

#define SAMPLE 200

int main(){
	// Debug LED
	DDRB |= _BV(DDB1);
	sei();
	init_IMU();
	USART_init();
	
	while(1){
		USART_Transmit((int8_t)theta_SA_rad);
		USART_Transmit((int8_t)phi_SA_rad);
			
		//USART_Transmit(*theta_ptr);
		//USART_Transmit(*(theta_ptr+1));
		//USART_Transmit(*(theta_ptr+2));
		//USART_Transmit(*(theta_ptr+3));
		//USART_Transmit(*phi_ptr);
		//USART_Transmit(*(phi_ptr+1));
		//USART_Transmit(*(phi_ptr+2));
		//USART_Transmit(*(phi_ptr+3));
		USART_Transmit(0x0A);
		PORTB &= ~(1<<PB1);
		_delay_ms(SAMPLE);
		PORTB |= (1<<PB1);
	}
}