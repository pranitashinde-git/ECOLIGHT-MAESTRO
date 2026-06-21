#include<lpc21xx.h>
#include"types.h"
#include"lcd.h"
#include"delayy.h"
#include"Adc_definee.h"
void adc_init(void)
{
	PINSEL1=0x15400000;
	ADCR=(1<<PDN)|(CLKDIV<<8);
}	

void Readadc(u8 chno,u32 *adcval,f32 *eAR)
{
	
ADCR&=0XFFFFFF00;
ADCR|=(1<<chno)|(1<<START);
delay_us(3);

while(((ADDR>>DONE)&1)==0);
ADCR&= ~(1<<START);
*adcval=((ADDR>>RESULT)&1023);
eAR=*adcval(3.3/1023);
	
}

unsigned int Dval;
float eAR;
int main()
{
	adc_init();
	Init_lcd();
	while(1)
	{
		Readadc(0,&Dval,&eAR);
		cmd_lcd(0x80);
		StrLCD("Dval: ");
		cmd_lcd(0xc0);
		StrLCD("Analog: ");
	  F32LCD(eAR,2);
}
	}