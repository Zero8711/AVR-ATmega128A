/*
 * Button_Interrupt.c
 *
 * Created: 2022-07-26 오전 10:59:44
 * Author : KangHyeonGu
 */ 

#define F_CPU 14745600L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int count = 0;

unsigned char font[] = {0x3f, 0x06, 0x5b, 0x4f, 
						0x66, 0x6d, 0x7c, 0x07,
						0x7f, 0x6f, 0x77, 0x7c, 
						0x39, 0x5e, 0x79, 0x71, 
						0x08, 0x80};// 1, 2, 3, 4, 5, 6, 7, 8, 9, A, b, c, d, e, f, ., _);
						
void segment(unsigned char n)
{
	unsigned char n10, n1;
	n10 = n / 10;
	n1 = n % 10;
	
	for(int i = 0; i < 30; i++)
	{
		PORTG = 0x0b;
		PORTB = font[n10];
		_delay_ms(1);
		PORTG = 0x07;
		PORTB = font[n1];
		_delay_ms(1);
	}
}

ISR(INT0_vect)
{
	count++;
}

int main(void)
{
	DDRB = 0xFF;
	DDRG = 0x0F;
	DDRD = 0x00;
	
	EIMSK = 0x01; //Interrupt 0
	EICRA = 0x03; //Interrupt 0 RISING EDGE
	//SREG = 0x80;  //sei();
	sei();
    /* Replace with your application code */
    while (1) 
    {
		segment(count);
    }
}

