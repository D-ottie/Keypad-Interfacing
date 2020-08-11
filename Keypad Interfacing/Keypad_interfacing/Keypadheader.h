/*
 * Keypadheader.h
 *
 * Created: 6/29/2020 9:14:43 AM
 *  Author: Panda
 */ 


#ifndef KEYPADHEADER_H_
#define KEYPADHEADER_H_

/*Function Declarations*/
void LCD_Cmd(unsigned char cmd);
void LCD_Char(unsigned char char_data);
void LCD_Init(void);
void LCD_Clear(void);
void LCD_String(char *str);
void LCD_String_xy(char row, char pos, char *str);
//void Load_Custom_Char();
//void LCD_Custom_Char(int , unsigned char *str);
void ADC_Init(void);
int ADC_Read(char channel);
char read_key(void);


#endif /* KEYPADHEADER_H_ */