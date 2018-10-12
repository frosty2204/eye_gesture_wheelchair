
#include <inttypes.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <ctype.h>






void uart_init(void)                            // initializing UART
{
	UBRRH = 0x00;
	UBRRL = 0x33;

	UCSRC |= 0x86;                              // 8N1 Data
	UCSRB  = 0x18;                              // Receiving and Transmitting
}

int uart_putch(char ch, FILE *stream)           // Function for sending Data to PC
{
	if (ch == '\n')
	uart_putch('\r', stream);
	while (!(UCSRA & (1<<UDRE)));
	UDR=ch;
	return 0;
}

int uart_getch(FILE *stream)                    // Function for receiving Data from PC
{
	unsigned char ch;   while (!(UCSRA & (1<<RXC)));
	ch=UDR;

	uart_putch(ch,stream);                      // Echo the output back to the terminal

	return (ch);

}

FILE uart_str = FDEV_SETUP_STREAM(uart_putch, uart_getch, _FDEV_SETUP_RW);
void delay (void);
void initialize(void);

int main(void)
{
	int move;
	// 0 - left, 1- right, 2- straight, 3 - stop
	initialize();

	while(1){
		fscanf(stdin,"%d",&move); // receive data
		switch (move)
		{
			case 0:
			PORTC = 0x01; // move left
			_delay_ms (1000);
			break;
			
			case 1:
			
			PORTC = 0x04; // move right
			_delay_ms (1000);
			break;
			
			case 2:
			
			PORTC = 0x05; // move straight
			_delay_ms (1000);
			break;
			
			case 3:
			
			PORTC = 0x00; // halt
			_delay_ms (1000);
			break;

			default:
			PORTC = 0x00; // halt
			_delay_ms (1000);
			break;

		}
	}

}

void initialize(void)
{
	DDRC =0xFF;

	
	uart_init();
	stdout = stdin = stderr = &uart_str;

	fprintf(stdout,"Starting ...\n\r");
	
}


