/***************************************************************
*
* Serial protocal ATmega328p
* Author: Simon Reinbold
* Last Update: 22.10.2017
*
***************************************************************/

#ifndef _USART_
#define _USART_

#define BAUDRATE 9600
#define BAUD_PRESCALLER ( ( (F_CPU/16) / BAUDRATE) - 1)

void USART_init();
void USART_Transmit(uint8_t data);
uint8_t USART_Receive(void);

#endif /* _USART_ */