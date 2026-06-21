#include <LPC21xx.h>

void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_string(char *);
void lcd_data(unsigned char);
void delay_ms(unsigned int);

void keypad_init(void);
char keypad_scan(void);

void rtc_init(void);
void rtc_display(void);

void adc_init(void);
unsigned int adc_read(void);

void led_init(void);
void led_on(void);
void led_off(void);

char key;
char temp[3];

unsigned int ldr;

void wait_release(void)
{
    delay_ms(1);

    while(keypad_scan() != 0);

    delay_ms(1);
}

void lcd_backspace(void)
{
    lcd_cmd(0x10);

    lcd_data(' ');

    lcd_cmd(0x10);
}

void rtc_edit(void)
{
    unsigned char i;

    unsigned int hour,min,sec;

    // ================= HOUR =================

    while(1)
    {
        lcd_cmd(0x01);

        lcd_string("ENTER HOUR:");

        lcd_cmd(0xC0);

        i = 0;

        while(1)
        {
            key = keypad_scan();

            if((key >= '0') && (key <= '9'))
            {
                if(i < 2)
                {
                    temp[i] = key;

                    lcd_data(key);

                    i++;

                    wait_release();
                }
            }

            else if(key == '*')
            {
                if(i > 0)
                {
                    i--;

                    lcd_backspace();

                    wait_release();
                }
            }

            else if(key == '#')
            {
                if(i == 2)
                {
                    wait_release();

                    break;
                }
            }
        }

        hour = ((temp[0]-48)*10) + (temp[1]-48);

        if(hour <= 23)
        {
            HOUR = hour;

            break;
        }
        else
        {
            lcd_cmd(0x01);

            lcd_string("INVALID HOUR");

            delay_ms(30);
        }
    }

    // ================= MINUTE =================

    while(1)
    {
        lcd_cmd(0x01);

        lcd_string("ENTER MIN:");

        lcd_cmd(0xC0);

        i = 0;

        while(1)
        {
            key = keypad_scan();

            if((key >= '0') && (key <= '9'))
            {
                if(i < 2)
                {
                    temp[i] = key;

                    lcd_data(key);

                    i++;

                    wait_release();
                }
            }

            else if(key == '*')
            {
                if(i > 0)
                {
                    i--;

                    lcd_backspace();

                    wait_release();
                }
            }

            else if(key == '#')
            {
                if(i == 2)
                {
                    wait_release();

                    break;
                }
            }
        }

        min = ((temp[0]-48)*10) + (temp[1]-48);

        if(min <= 59)
        {
            MIN = min;

            break;
        }
        else
        {
            lcd_cmd(0x01);

            lcd_string("INVALID MIN");

            delay_ms(30);
        }
    }

    // ================= SECOND =================

    while(1)
    {
        lcd_cmd(0x01);

        lcd_string("ENTER SEC:");

        lcd_cmd(0xC0);

        i = 0;

        while(1)
        {
            key = keypad_scan();

            if((key >= '0') && (key <= '9'))
            {
                if(i < 2)
                {
                    temp[i] = key;

                    lcd_data(key);

                    i++;

                    wait_release();
                }
            }

            else if(key == '*')
            {
                if(i > 0)
                {
                    i--;

                    lcd_backspace();

                    wait_release();
                }
            }

            else if(key == '#')
            {
                if(i == 2)
                {
                    wait_release();

                    break;
                }
            }
        }

        sec = ((temp[0]-48)*10) + (temp[1]-48);

        if(sec <= 59)
        {
            SEC = sec;

            break;
        }
        else
        {
            lcd_cmd(0x01);

            lcd_string("INVALID SEC");

            delay_ms(30);
        }
    }

    // UPDATE MESSAGE

    lcd_cmd(0x01);

    lcd_string("RTC UPDATED");

    delay_ms(30);

    lcd_cmd(0x01);
}
void get_2digit_value(unsigned int *value)
{
    unsigned char i=0;

    while(1)
    {
        key = keypad_scan();

        if((key >= '0') && (key <= '9'))
        {
            if(i < 2)
            {
                temp[i] = key;

                lcd_data(key);

                i++;

                wait_release();
            }
        }

        else if(key == '*')
        {
            if(i > 0)
            {
                i--;

                lcd_backspace();

                wait_release();
            }
        }

        else if(key == '#')
        {
            if(i == 2)
            {
                wait_release();

                break;
            }
        }
    }

    *value = ((temp[0]-48)*10) + (temp[1]-48);
}
void edit_hour(void)
{
    unsigned int value;

    while(1)
    {
        lcd_cmd(0x01);

        lcd_string("ENTER HOUR:");

        lcd_cmd(0xC0);

        get_2digit_value(&value);

        if(value <= 23)
        {
            HOUR = value;

            break;
        }

        lcd_cmd(0x01);

        lcd_string("INVALID HOUR");

        delay_ms(30);
    }

    lcd_cmd(0x01);

    lcd_string("HOUR UPDATED");

    delay_ms(30);
}
void edit_min(void)
{
    unsigned int value;

    while(1)
    {
        lcd_cmd(0x01);

        lcd_string("ENTER MIN:");

        lcd_cmd(0xC0);

        get_2digit_value(&value);

        if(value <= 59)
        {
            MIN = value;

            break;
        }

        lcd_cmd(0x01);

        lcd_string("INVALID MIN");

        delay_ms(30);
    }

    lcd_cmd(0x01);

    lcd_string("MIN UPDATED");

    delay_ms(30);
}

void edit_sec(void)
{
    unsigned int value;

    while(1)
    {
        lcd_cmd(0x01);

        lcd_string("ENTER SEC:");

        lcd_cmd(0xC0);

        get_2digit_value(&value);

        if(value <= 59)
        {
            SEC = value;

            break;
        }

        lcd_cmd(0x01);

        lcd_string("INVALID SEC");

        delay_ms(30);
    }

    lcd_cmd(0x01);

    lcd_string("SEC UPDATED");

    delay_ms(30);
}
void edit_date(void)
{
    unsigned int value;

    while(1)
    {
        lcd_cmd(0x01);

        lcd_string("ENTER DATE:");

        lcd_cmd(0xC0);

        get_2digit_value(&value);

        if((value >= 1) && (value <= 31))
        {
            DOM = value;

            break;
        }

        lcd_cmd(0x01);

        lcd_string("INVALID DATE");

        delay_ms(30);
    }

    lcd_cmd(0x01);

    lcd_string("DATE UPDATED");

    delay_ms(30);
}
void edit_month(void)
{
    unsigned int value;

    while(1)
    {
        lcd_cmd(0x01);

        lcd_string("ENTER MONTH:");

        lcd_cmd(0xC0);

        get_2digit_value(&value);

        if((value >= 1) && (value <= 12))
        {
            MONTH = value;

            break;
        }

        lcd_cmd(0x01);

        lcd_string("INVALID MON");

        delay_ms(30);
    }

    lcd_cmd(0x01);

    lcd_string("MON UPDATED");

    delay_ms(30);
}

void edit_year(void)
{
    unsigned int y1,y2,y3,y4;
    unsigned int value;

    while(1)
    {
        lcd_cmd(0x01);

        lcd_string("ENTER YEAR:");

        lcd_cmd(0xC0);

        while(1)
        {
            y1 = keypad_scan();

            if((y1 >= '0') && (y1 <= '9'))
            {
                lcd_data(y1);

                wait_release();

                break;
            }
        }

        while(1)
        {
            y2 = keypad_scan();

            if((y2 >= '0') && (y2 <= '9'))
            {
                lcd_data(y2);

                wait_release();

                break;
            }
        }

        while(1)
        {
            y3 = keypad_scan();

            if((y3 >= '0') && (y3 <= '9'))
            {
                lcd_data(y3);

                wait_release();

                break;
            }
        }

        while(1)
        {
            y4 = keypad_scan();

            if((y4 >= '0') && (y4 <= '9'))
            {
                lcd_data(y4);

                wait_release();

                break;
            }
        }

        value =
        ((y1-48)*1000) +
        ((y2-48)*100) +
        ((y3-48)*10) +
        (y4-48);

        if((value >= 2000) && (value <= 2099))
        {
            YEAR = value;

            break;
        }

        lcd_cmd(0x01);

        lcd_string("INVALID YEAR");

        delay_ms(30);
    }

    lcd_cmd(0x01);

    lcd_string("YEAR UPDATED");

    delay_ms(30);
}
void rtc_menu(void)
{
    unsigned char page = 0;

    while(1)
    {
        lcd_cmd(0x01);

        if(page == 0)
        {
            lcd_cmd(0x80);
            lcd_string("1.HOUR");

            lcd_cmd(0xC0);
            lcd_string("2.MIN #NEXT");
        }
        else if(page == 1)
        {
            lcd_cmd(0x80);
            lcd_string("3.SEC");

            lcd_cmd(0xC0);
            lcd_string("4.DATE#NEXT");
        }
        else
        {
            lcd_cmd(0x80);
            lcd_string("5.MON");

            lcd_cmd(0xC0);
            lcd_string("6.YEAR#EXIT");
        }

        while(1)
        {
            key = keypad_scan();

            if(key != 0)
            {
                wait_release();
                break;
            }
        }

        if(page == 0)
        {
            if(key == '1')
            {
                edit_hour();
                return;
            }

            else if(key == '2')
            {
                edit_min();
                return;
            }

            else if(key == '#')
            {
                page = 1;
            }
        }

        else if(page == 1)
        {
            if(key == '3')
            {
                edit_sec();
                return;
            }

            else if(key == '4')
            {
                edit_date();
                return;
            }

            else if(key == '#')
            {
                page = 2;
            }
        }

        else
        {
            if(key == '5')
            {
                edit_month();
                return;
            }

            else if(key == '6')
            {
                edit_year();
                return;
            }

            else if(key == '#')
            {
                lcd_cmd(0x01);

                lcd_string("EXIT");

                delay_ms(30);

                lcd_cmd(0x01);

                return;
            }
        }
    }
}

int main()
{
    lcd_init();

    keypad_init();

    rtc_init();

    adc_init();

    led_init();

    lcd_cmd(0x80);

    lcd_string("STREET LIGHT");

    delay_ms(30);

    lcd_cmd(0x01);

    while(1)
    {
        // DISPLAY RTC

        rtc_display();

        // READ KEYPAD

        key = keypad_scan();

        // OPEN MENU

        if(key == '1')
        {
            wait_release();

            rtc_menu();

            lcd_cmd(0x01);
        }

        // READ LDR

        ldr = adc_read();

        // DISPLAY LDR VALUE

        lcd_cmd(0x8A);

        lcd_data((ldr/1000) + 48);
        lcd_data(((ldr/100)%10) + 48);
        lcd_data(((ldr/10)%10) + 48);
        lcd_data((ldr%10) + 48);

        // NIGHT CONDITION

        if((HOUR >= 18) || (HOUR < 6))
        {
            if(ldr < 400)
            {
                led_on();
            }
            else
            {
                led_off();
            }
        }
        else
        {
            led_off();
        }

        delay_ms(1);
    }
		// OPEN MENU

if(key == '1')
{
    wait_release();

    rtc_menu();

    lcd_cmd(0x01);
}
}