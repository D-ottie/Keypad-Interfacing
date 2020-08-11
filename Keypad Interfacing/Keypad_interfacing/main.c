/*
 * Keypad_interfacing.c
 *
 * Created: 6/28/2020 2:42:42 AM
 * Author : Orina Dorothy
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Keypadheader.h"

int main(void)
{
	int adc_value = 0;
	int keys = 16;
	LCD_Init();  /* Initialize LCD */
	ADC_Init();
	LCD_String("Press A Key");
	LCD_Cmd(0xc0);
	read_key();
	return 0;
}

									





