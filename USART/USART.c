#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

void USART_init()
{
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR0L = (uint8_t)BAUD_PRESCALLER;

	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( uint8_t data )
{
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

uint8_t USART_Receive(void){
 
	 while(!(UCSR0A & (1<<RXC0)));
	 return UDR0; 
}