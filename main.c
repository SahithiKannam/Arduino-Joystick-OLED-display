#define F_CPU 16000000UL
#include "lcd.h"
#include "i2c.h"
#include "font.h"
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>

void InitADC(void)
{
  ADMUX|=(1<<REFS0);
  ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); //ENABLE ADC, PRESCALER 128
}

uint16_t readadc(uint8_t ch)
{
  ch&=0b00000111;               // ANDing to limit input to 7
  //ADMUX = (ADMUX & 0xF0) | (ch & 0x0F);
  ADMUX = (ADMUX & 0xf8)|ch;    // Clear last 3 bits of ADMUX, OR with ch
  
  ADCSRA|=(1<<ADSC);            // START CONVERSION
  while((ADCSRA)&(1<<ADSC));    // WAIT UNTIL CONVERSION IS COMPLETE
  return(ADC);                  // RETURN ADC VALUE
}

int main(void){
	/*
  char a[10], b[10];
  uint16_t x,y;
  InitADC();              //INITIALIZE ADC
  lcd_init(LCD_DISP_ON);  //INITIALIZE LCD
  lcd_clrscr();
  
  while(1)
  {   
    
    lcd_home();
    x=readadc(1);      // READ ADC VALUE FROM PA.1
    y=readadc(0);      // READ ADC VALUE FROM PA.0
    
    itoa(x,a,10);
    lcd_puts("x= ");   // DISPLAY THE RESULTS ON LCD
    lcd_gotoxy(2,0);
    lcd_puts(a);
    itoa(y,b,10);
    lcd_gotoxy(0,1);
    lcd_puts("y= ");
    lcd_gotoxy(2,1);
    lcd_puts(b);
    
    _delay_ms(200);
  }*/
	lcd_init(0xAF);    // init lcd and turn on
	Print_pos(0,5);
	
	
  return 0;
}


void Print_pos(int x,int y){

	lcd_clrscr();
	
	lcd_gotoxy(x,y);  //line x column y
	i2c_start(LCD_I2C_ADR << 1);
	i2c_byte(0x40);
	for (uint8_t i = 0; i < 7; i++)
	{
		i2c_byte(pgm_read_byte(&(FONT[34][i])));
	}
	i2c_stop();
}


