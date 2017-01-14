/*
 * ultra_sonic.c
 *
 * Created: 4/4/2016 8:28:37 PM
 *  Author: oody
 */ 

#include "STD_TYP.h"
#include "timer0.h"


int main(void)
{
	set_bit(DDRA,0);
	clr_bit(PORTA,0);      //pa.0 trig
	clr_bit(DDRA,1);       //pa.1 echo
	clr_bit(PINA,1);
	set_bit(DDRD,5);       //pd.5 puzzer
	clr_bit(PORTD,5);
	set_bit(DDRA,2);
	clr_bit(PORTA,2);      //pa.2 led
	timer0_init();
volatile int time_count=0;
	volatile float distance=0;

    while(1)
    {
		clr_bit(PORTA,0);
		_delay_us(5);
		set_bit(PORTA,0);   // trig on
		_delay_us(10);
		clr_bit(PORTA,0);   // trig off
		while(get_bit(PINA,1)==0);  // echo pin
		timer0_start();
		while(get_bit(PINA,1)==1);  // echo pin
		timer0_stop();
		time_count=TCNT0*128;    // 128us >>zaman el3ada elwa7da 1024(prescaler)/8,000,000(F_cpu)  elnateg madrob fe million 3shan 27awel mn second le us
		distance=0.017*time_count;  // 0.017 = sor3et elsoot (340m/s) *100(3shan distance tb2a bl cm)*(1/1,000,000)(3shan time yb2a bl us)>>3shan el3ada 
		if((distance<30)&&(distance>20))                                                                                       //elwa7da bl us
		{
			set_bit(PORTD,5);
			_delay_ms(200);
			clr_bit(PORTD,5);
			_delay_ms(200);
		}
		else if((distance<20)&&(distance>10))
		{
				set_bit(PORTD,5);
				_delay_ms(100);
				clr_bit(PORTD,5);
				_delay_ms(100);
		}
			else if((distance<10)&&(distance>6))
			{
				set_bit(PORTD,5);
				_delay_ms(50);
				clr_bit(PORTD,5);
				_delay_ms(50);
			}
			else if (distance<6)
			{
				set_bit(PORTD,5);
			}
		else
		{
			clr_bit(PORTD,5);
		}
		
		_delay_ms(50);
		timer0_clear();
		
        //TODO:: Please write your application code 
    }
}