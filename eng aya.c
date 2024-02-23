#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdbool.h>
#include "macro.h"
#include "DIO.h"
#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include <avr/interrupt.h>//to use bilt in functions in interrupt
#include <stdio.h>
#include <math.h>
#include <float.h>
#define NOTPRESSED 0xff
int main(void)
{
 sei(); ///==set_bit(sreg,7);   to enable interrupt
 // to disable interrupt <<cli();<< ========== clear_bit(sreg,7);
 
 
 
 BUTTON_init('b',0);
 BUTTON_init('a',0);
 BUTTON_init('d',0);
 seven_seg_bcd_inti('A');
 seven_seg_bcd_inti('B');

 LED_init('d',1);
 LED_init('d',2);

 unsigned char counta=0;
 unsigned char countb=0;
 unsigned char max=0;
 unsigned char aya=0;
 bool flag1;
 bool flag2;
 DIO_CONNECT_PULLUP('a',0,1);
 DIO_CONNECT_PULLUP('b',0,1);
 //DIO_CONNECT_PULLUP('d',2,1);
 ////////////////////// end of inti
 
 //EEPROM_write(0x0001,'a');
 //EEPROM_write(0x0012,'b');
 //EEPROM_write(0x0020,'c');
 
 
 while(1){
	 
	 flag2=false;
	 flag1=true;
	 //////to accesss b
	 while(flag1){
		 aya=BUTTON_read('d',0);
		 if(BUTTON_read('b',0)==0){
			 countb++;
		 }
		 
		 seven_segbcd_write('B',countb);
		 _delay_ms(200);
		 
		 
		 
		 ///to access a
		 if(BUTTON_read('a',0)==0){
			 counta++;
		 }
		 
		 seven_segbcd_write('a',counta);
		 _delay_ms(200);
		 
		 if(aya==1){
			 flag1=false;
			 flag2=true;
		 }
		 
	 }
	 
	 
	 //////////////////////////
	 while(flag2){
		 if(countb>counta){
			 max='b';
		 }
		 else if(counta>countb){
			 max='a';
		 }
		 else if(countb==counta){
			 max='c';
		 }
		 
		 
		 
		 //connected pull up
		 if(max=='a'){
			 LED_ON('d',1);
		 }
		 else if(max=='b'){
			 LED_ON('d',2);
		 }
		 else if(max=='c'){
			 LED_ON('d',2);
			 LED_ON('d',1);
		 }
		 
		 flag2=false;
	 flag1=true;}
	 
	 
	 
	 
	 
	 
	 
 }//end of while 1
    }