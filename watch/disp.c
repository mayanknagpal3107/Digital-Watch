#include<avr/io.h>
#include<util/delay.h>
#include"uart.h"
#include"uart.c"
#include<compat/deprecated.h>
#include"lcd.c"
#include"lcd.h"
volatile int a=0;
void timer()
{
	TCNT0=0x00;
	TCCR0=0x05;
	TIMSK=0x01;
}
ISR(TIMER0_OVF_vect)
{
	a++;
}


void main()
{
	int m=0,h=0,s=0,sa,sb,ma,mb,ha,hb,t[10];
	char c;
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	timer();
	sei();
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	uart_puts("Set Time");
	while(1)
	{
		if(a==61)
		{	s++;
			a=0;
			{if(s==60)
				{	s=0;
					m++;	
					if(m==60)
						{m=0;
						h++;
						if(h==24)
						{h=0;
						}
						}	
				}
			}
		}
		sa=s%10;
		sb=s/10;
		ma=m%10;
		mb=m/10;
		ha=h%10;
		hb=h/10;
		lcd_gotoxy(2,0);
		lcd_puts("Digital Clock");
		lcd_gotoxy(4,1);
		itoa(hb,t,10);
		lcd_puts(t);
		lcd_gotoxy(5,1);
		itoa(ha,t,10);
		lcd_puts(t);
		lcd_gotoxy(6,1);
		lcd_puts(":");
		lcd_gotoxy(7,1);
		itoa(mb,t,10);
		lcd_puts(t);
		lcd_gotoxy(8,1);
		itoa(ma,t,10);
		lcd_puts(t);
		lcd_gotoxy(9,1);
		lcd_puts(":");
		lcd_gotoxy(10,1);
		itoa(sb,t,10);
		lcd_puts(t);
		lcd_gotoxy(11,1);
		itoa(sa,t,10);
		lcd_puts(t);
		c=uart_getc();
		if(c!=0)
		
		{
			if(c=='H')
			{
				h++;
				uart_puts("Increment Hour \n\r");
				if(h==24)
				h=0;
			}
			if(c=='S')
			{
				s++;
				if(s==60)
				s=0;
				uart_puts("Increment Second \n\r");
			}
			if(c=='M')
			{
				m++;
				if(m==60)
				m=0;
				uart_puts("Increment Minute \n\r");
			}
			if(c=='Q')
			{
			uart_puts("Stop \n\r");
			TCCR0=0;
			}
			if(c=='W')
			{
			uart_puts("Start \n\r");
			TCCR0=0x05;			
			}
			if(c=='R')
			{
			uart_puts(" Reset\n\r");
			h=0;
			m=0;
			s=0;
			}
			
		}

		
		
		
	}
}

