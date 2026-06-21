#include<lpc21xx.h>
#include"lcd.h"

#include "delayy.h"

void write_lcd(char data)
{
	IOCLR0=1<<RW_PIN;
	IOPIN0=IOPIN0&~(255<<LCD_DATA)|(data<<LCD_DATA);
	IOSET0=1<<EN_PIN;
	delay_us(1);
	IOCLR0=1<<EN_PIN;
	delay_ms(2);
}

void cmd_lcd(char cmd)
{
	IOCLR0=1<<RS_PIN;
	write_lcd(cmd);
}

void Init_lcd(void)
{
	IODIR0|=255<<LCD_DATA;
	IODIR0|=7<<RS_PIN;
	delay_ms(15);
	cmd_lcd(0x30);
	delay_ms(4);
	delay_us(100);
	cmd_lcd(0x30);
	delay_us(100);
	cmd_lcd(0x30);
	cmd_lcd(0x38);
	cmd_lcd(0x0E);
	cmd_lcd(0x01);
	cmd_lcd(0x06);
}

void char_lcd(char dat)
{
	IOSET0=1<<RS_PIN;
	write_lcd(dat);
}


//Pass Integer 
void U32LCD(unsigned int n)
{
	unsigned char a[10];
	signed int i=0;
	if(n==0)
	{
		char_lcd('0');
	}
  else
	{
    while(n)
		{
      a[i++]=(n%10)+'0';
        n/=10;
		}
    for(--i;i>=0;i--)
    {
       char_lcd(a[i]);
			//delay_s(1);
    }
   }
}

//Print signed (+/-) on LCD
void S32LCD(signed int n)
{
	if(n<0)
	{
		char_lcd('-');
		n=-n;
	}
  U32LCD(n);
}	
	//display float value

void F32LCD(float f,unsigned char ndp)
{
	unsigned int n,i;
	if(f<0)
	{
		char_lcd('-');
		f=-f;
	}
  n=f;
  U32LCD(n);
  char_lcd('.');
  for(i=0;i<ndp;i++)
  {
	   f=(f-n)*10;
		n=f;
		char_lcd(n+48);
	}
}	

//Pass String
void StrLCD(char *str)
{
	while(*str)
	{
		char_lcd(*str);
		*str++;
	}
}

//Custom char
void BuildCGRAM(unsigned char *p, unsigned int nbytes)
{
	int i;

	// Go to CGRAM
	cmd_lcd(0x40);

	for(i=0;i<nbytes;i++)
	{
		char_lcd(p[i]);
	}

	// Back to DDRAM
	cmd_lcd(0x80);
}