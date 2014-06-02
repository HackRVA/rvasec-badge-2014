/* 
 * File:   nokia.h
 * Author: morgan
 *
 * Created on March 29, 2014, 10:02 PM
 */

#ifndef NOKIA_H
#define	NOKIA_H


#include <p32xxxx.h>
#define byte char
#include "hackrva.h"
#include "rvasec_logo.h"
//#include "hackrva.xbm"

unsigned int current_index;
unsigned char X, Y;
typedef enum {ALPHA, OPAQUE } BLIT_STYLE_t;
void LCDString(char *characters) ;
void LCDCharacter(char character) ;
void LCDBitmap(const char my_array[]);
void putPixel(unsigned char x, unsigned char y, unsigned char val);
void gotoXY(int x, int y) ;
void loop(void) ;
void clear_screen_buff(void);
void LCDClear(void) ;
void LCDClearArea(unsigned char x, unsigned char y,
                    unsigned char width, unsigned char height);

//unsigned char blitBuff_toBuff_collision(struct pix_buff *src_buff, struct pix_buff *dest_buff,
//                      unsigned char x,
//                      unsigned char y,
//                      BLIT_STYLE_t style);
void LCDInit(void) ;
void LCDWrite(byte data_or_command, byte data) ;
void setBuf(unsigned char val);
void writeXBM(const char *bm, unsigned bm_width, unsigned bm_height) ;

#define PIN_RESET LATCbits.LATC9           // reset
#define PIN_SCE   LATCbits.LATC8           // chip enable active low
#define PIN_DC    LATCbits.LATC7           // data/comand
#define PIN_SDIN  LATCbits.LATC6           // serial data in
#define PIN_SCLK  LATBbits.LATB9           // clock

//The DC pin tells the LCD if we are sending a command or data
#define LCD_COMMAND 0
#define LCD_DATA  1

//You may find a different size screen, but this one is 84 by 48 pixels
#define LCD_X     84
#define LCD_Y     48



#endif	/* NOKIA_H */

