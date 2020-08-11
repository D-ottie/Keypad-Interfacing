/*
 * Function.c
 *
 * Created: 6/29/2020 10:33:12 AM
 *  Author: Panda
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define LCD_Dir DDRD
#define LCD_Port PORTD
#define RS PD0
#define EN PD1


/*LCD command write*/
void LCD_Cmd(unsigned char cmd){
	/*Sending the first nibble of data (Higher 4 bits)*/
	LCD_Port = (LCD_Port & 0x0F) | (cmd & 0xF0);/* Sending upper nibble */
	LCD_Port &= ~ (1<<RS); /* RS=0, command reg. */
	LCD_Port |= (1<<EN); /* Enable pulse ON */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN); /* Enable pulse OFF */
	_delay_us(200);
	/*Sending the second nibble of data (Lower 4 bits)*/
	LCD_Port = (LCD_Port & 0x0F) | (cmd << 4);/* Sending lower nibble */
	LCD_Port |= (1<<EN); /* Enable pulse ON */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN); /* Enable pulse OFF */
	_delay_ms(2);
}
/*LCD data write function */
void LCD_Char (unsigned char char_data){
	/*Sending the first nibble of data (Higher 4 bits)*/
	LCD_Port = (LCD_Port & 0x0F) | (char_data & 0xF0);/* Sending upper nibble */
	LCD_Port |= (1<<RS); /* RS=1, data reg. */
	LCD_Port |= (1<<EN); /* Enable pulse ON */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN); /* Enable pulse OFF */
	_delay_us(200);
	/*Sending the second nibble of data (Lower 4 bits)*/
	LCD_Port = (LCD_Port & 0x0F) | (char_data << 4); /* Sending lower nibble */
	LCD_Port |= (1<<EN); /* Enable pulse ON */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN); /* Enable pulse OFF */
	_delay_ms(2);
}
/*LCD Initialize function */
void LCD_Init (void){
	LCD_Dir = 0xFF; /* Make LCD command port direction as output pins*/
	_delay_ms(20); /* LCD Power ON delay always > 15ms */
	LCD_Cmd(0x33);
	LCD_Cmd(0x32); /*send for 4 bit initialization of LCD*/
	//LCD_Cmd(0x80); /* Return display to its home position */
	LCD_Cmd(0x28); /* 2 line 4bit mode */
	LCD_Cmd(0x0C); /* Display ON Cursor OFF */
	LCD_Cmd(0x06); /* Auto Increment cursor */
	LCD_Cmd(0x01); /* Clear display */
	_delay_ms(2);
	LCD_Cmd (0x80);
}
/*Clear LCD Function*/
void LCD_Clear(void){
	LCD_Cmd(0x01); /* clear display */
	_delay_ms(2);
	LCD_Cmd(0x80); /* Return display to its home position */
}

/*Send string to LCD function */
void LCD_String (char *str){
	int i;
	/* Send each char of string till the NULL */
	for(i=0;str[i]!=0;i++){
		LCD_Char(str[i]);
	}
}/*Send string to LCD with xy position */
void LCD_String_xy (char row, char pos, char *str){
	if (row == 0 && pos<16){
		LCD_Cmd((pos & 0x0F)|0x80);/* Command of first row and required
		position<16 */
	}
	else if (row == 1 && pos<16){
		LCD_Cmd((pos & 0x0F)|0xC0);/* Command of second row and required
		position<16 */
	}
	LCD_String(str); /* Call LCD string function */
}

void ADC_Init()
{
	DDRA=0x0;			/* Make ADC port as input */
	ADCSRA = 0x87;			/* Enable ADC, fr/128  */
	ADMUX = 0x40;			/* Vref: Avcc, ADC channel: 0 */
	
}

int ADC_Read(char channel)
{
	ADMUX = 0x40 | (channel & 0x07);
	ADCSRA |= (1<<ADSC);  /* Start ADC conversion */
	while (!(ADCSRA & (1<<ADIF))); /* Wait until end of conversion */
	ADCSRA |= (1<<ADIF);  /* Clear interrupt flag */
	_delay_ms(1);   
	return ADCW;   /* Return ADC word */
}

char read_key()
{
	int keys = 16;
	unsigned char *keypad[] = {"7","8","9","/","4","5","6","*","1","2","3","-","ON","0","=","+"};
	int adc_value = ADC_Read(0);
	int values[] = {1023,512,341,256,180,153,133,118,98,90,83,76,68,64,60,57};
		
	while(1)
	{
		adc_value = ADC_Read(0);
		
		for (int i =0; i<=keys; i++)
		{
			if (adc_value ==(values[i]))
			{
				LCD_Clear(); //Clear screen before displaying another key
				LCD_String(keypad[i]);
			}
		}
		
		_delay_ms(300);
		
	}
	
}

