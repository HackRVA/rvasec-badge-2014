/*
 7-17-2011
 Spark Fun Electronics 2011
 Nathan Seidle
 
 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 This code writes a series of images and text to the Nokia 5110 84x48 graphic LCD:
 http://www.sparkfun.com/products/10168
 
 Do not drive the backlight with 5V. It will smoke. However, the backlight on the LCD seems to be 
 happy with direct drive from the 3.3V regulator.

 Although the PCD8544 controller datasheet recommends 3.3V, the graphic Nokia 5110 LCD can run at 3.3V or 5V. 
 No resistors needed on the signal lines.
 
 You will need 5 signal lines to connect to the LCD, 3.3 or 5V for power, 3.3V for LED backlight, and 1 for ground.
 */
#include "nokia.h"
#include "badge_common.h"

//char gContrast=0xB0;
char gContrast=185;
//int gDelay=100;
int gDelay=20;


#define DELAY { int i; for (i=0; i<gDelay; i++) ; }


struct Font {
    
};

//This table contains the hex values that represent pixels
//for a font that is 5 pixels wide and 8 pixels high
static const byte ASCII_ol[][5] = {
  {0x00, 0x00, 0x00, 0x00, 0x00} // 20  
  ,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
  ,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
  ,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
  ,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
  ,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
  ,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
  ,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
  ,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
  ,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
  ,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
  ,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
  ,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
  ,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
  ,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
  ,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
  ,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
  ,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
  ,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
  ,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
  ,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
  ,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
  ,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
  ,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
  ,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
  ,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
  ,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
  ,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
  ,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
  ,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
  ,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
  ,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
  ,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
  ,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
  ,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
  ,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
  ,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
  ,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
  ,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
  ,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
  ,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
  ,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
  ,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
  ,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
  ,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
  ,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
  ,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
  ,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
  ,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
  ,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
  ,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
  ,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
  ,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
  ,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
  ,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
  ,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
  ,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
  ,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
  ,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
  ,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
  ,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c backslash
  ,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
  ,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
  ,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
  ,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
  ,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
  ,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
  ,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
  ,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
  ,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
  ,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
  ,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
  ,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
  ,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
  ,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j 
  ,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
  ,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
  ,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
  ,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
  ,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
  ,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
  ,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
  ,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
  ,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
  ,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
  ,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
  ,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
  ,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
  ,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
  ,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
  ,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
  ,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
  ,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
  ,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
  ,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ~
  ,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f DEL
};

static const byte ASCII_tiny[][3] =
{
    {0x2, 0x5, 0x7}, //a
    {0x7, 0x6, 0x6}, //b
    {0x2, 0x5, 0x5}, //c
    {0x6, 0x6, 0x7}, //d
    {0x2, 0x7, 0x5}, //e
    {0x7, 0x3, 0x1}, //f
    {0x3, 0x3, 0x7}, //g
    {0x7, 0x2, 0x6}, //h
    {0x00, 0x7, 0x0}, //i
    {0x6, 0x4, 0x7}, //j
    {0x7, 0x2, 0x5}, //k
    {0x7, 0x4, 0x4}, //L
    {0x6, 0x3, 0x6}, //m
    {0x6, 0x2, 0x6}, //n
    {0x7, 0x5, 0x7}, //o
    {0x7, 0x3, 0x3}, //p
    {0x3, 0x7, 0x3}, //q
    {0x7, 0x1, 0x3}, //r
    {0x4, 0x7, 0x1}, //s
    {0x1, 0x7, 0x1}, //T
    {0x7, 0x4, 0x7}, //u
    {0x3, 0x4, 0x3}, //v
    {0x3, 0x6, 0x3},//w
    {0x5, 0x2, 0x5},//x
    {0x3, 0x6, 0x7},//y
    {0x1, 0x7, 0x4}//z

};

static const byte ASCII[][5] =
{
{0x0,0x0,0x0,0x0,0x0},
{0x0,0x0,0x17,0x0,0x0},
{0x0,0x3,0x0,0x3,0x0},
{0xa,0x1f,0xa,0x1f,0xa},
{0x17,0x15,0x1f,0x15,0x1d},
{0x11,0x8,0x4,0x2,0x11},
{0xa,0x15,0xa,0x8,0x14},
{0x0,0x0,0x3,0x0,0x0},
{0x0,0x0,0xe,0x11,0x0},
{0x0,0x11,0xe,0x0,0x0},
{0x11,0xa,0x1f,0xa,0x11},
{0x4,0x4,0x1f,0x4,0x4},
{0x0,0x0,0x10,0x18,0x0},
{0x4,0x4,0x4,0x4,0x4},
{0x0,0x0,0x10,0x0,0x0},
{0x10,0x8,0x4,0x2,0x1},
{0xe,0x19,0x15,0x13,0xe},
{0x0,0x0,0x1f,0x0,0x0},
{0x12,0x11,0x19,0x15,0x12},
{0xa,0x11,0x15,0x15,0xa},
{0xc,0xa,0x9,0x1f,0x8},
{0x17,0x15,0x15,0x15,0x1d},
{0xe,0x15,0x15,0x15,0x8},
{0x1,0x1,0x19,0x5,0x3},
{0xa,0x15,0x15,0x15,0xa},
{0x2,0x15,0x15,0x15,0xe},
{0x0,0x0,0xa,0x0,0x0},
{0x0,0x10,0xa,0x0,0x0},
{0x0,0x4,0xa,0x11,0x0},
{0xa,0xa,0xa,0xa,0xa},
{0x0,0x11,0xa,0x4,0x0},
{0x2,0x1,0x19,0x5,0x2},
{0xe,0x11,0x1d,0x13,0xe},
{0x1c,0xa,0x9,0xa,0x1c},
{0x1f,0x15,0x15,0x15,0xa},
{0xe,0x11,0x11,0x11,0xa},
{0x1f,0x11,0x11,0x11,0xe},
{0x1f,0x15,0x15,0x15,0x15},
{0x1f,0x5,0x5,0x5,0x1},
{0xe,0x11,0x11,0x15,0xc},
{0x1f,0x4,0x4,0x4,0x1f},
{0x0,0x11,0x1f,0x11,0x0},
{0x8,0x10,0x10,0x10,0xf},
{0x1f,0x4,0x4,0xa,0x11},
{0x1f,0x10,0x10,0x10,0x10},
{0x1f,0x2,0x4,0x2,0x1f},
{0x1f,0x2,0x4,0x8,0x1f},
{0xe,0x11,0x11,0x11,0xe},
{0x1f,0x5,0x5,0x5,0x2},
{0xe,0x11,0x11,0x19,0x1e},
{0x1f,0x5,0x5,0xd,0x12},
{0x12,0x15,0x15,0x15,0x9},
{0x1,0x1,0x1f,0x1,0x1},
{0xf,0x10,0x10,0x10,0xf},
{0x7,0x8,0x10,0x8,0x7},
{0xf,0x10,0xf,0x10,0xf},
{0x11,0xa,0x4,0xa,0x11},
{0x1,0x2,0x1c,0x2,0x1},
{0x11,0x19,0x15,0x13,0x11},
{0x0,0x1f,0x11,0x11,0x0},
{0x1,0x2,0x4,0x8,0x10},
{0x0,0x11,0x11,0x1f,0x0},
{0x0,0x2,0x1,0x2,0x0},
{0x10,0x10,0x10,0x10,0x10},
{0x0,0x1,0x2,0x0,0x0},
{0xc,0x12,0x12,0xc,0x10},
{0x1e,0x14,0x14,0x8,0x0},
{0xc,0x12,0x12,0x12,0x0},
{0x8,0x14,0x14,0x1f,0x0},
{0xe,0x15,0x15,0x6,0x0},
{0x0,0x4,0x1f,0x5,0x0},
{0x0,0x2,0x15,0x15,0xe},
{0x0,0x1f,0x4,0x18,0x0},
{0x0,0x0,0x1a,0x0,0x0},
{0x0,0x10,0x1d,0x0,0x0},
{0x0,0x1f,0x8,0x14,0x0},
{0x0,0x1,0x1f,0x0,0x0},
{0x18,0x4,0x1c,0x4,0x18},
{0x18,0x4,0x4,0x18,0x0},
{0xc,0x12,0x12,0xc,0x0},
{0x1c,0xa,0xa,0x4,0x0},
{0x4,0xa,0xa,0x1c,0x0},
{0x1e,0x4,0x2,0x2,0x0},
{0x0,0x12,0x15,0x9,0x0},
{0x0,0x4,0x1e,0x14,0x0},
{0xe,0x10,0x10,0xe,0x10},
{0x4,0x8,0x10,0x8,0x4},
{0xc,0x10,0xc,0x10,0xc},
{0x0,0x14,0x8,0x14,0x0},
{0x10,0xa,0x4,0x2,0x0},
{0x0,0x12,0x1a,0x16,0x0},
{0x0,0x4,0x1b,0x11,0x0},
{0x0,0x0,0x1f,0x0,0x0},
{0x0,0x11,0x1b,0x4,0x0},
{0x2,0x1,0x2,0x4,0x2},
{0x0,0x0,0x0,0x0,0x0}
};

static byte ALPHA_ZERO = 1;
//screen is 6, 8 bit wide rows, with 84 columns
static byte screen_buf[6][84];

void gotoXY(int x, int y) {
  X = x;
  Y = y;

  LCDWrite(0, 0x80 | x);  // Column.
  LCDWrite(0, 0x40 | y);  // Row.  ?
  //current_index = x + (y - (y & 0xFFFFFFF8));
  current_index = x + (y*84);//((y >> 3) * 84); + auto increment

}

//This takes a large array of bits and sends them to the LCD
void LCDBitmap(const char my_array[]){
  int index;

  index += 2; /* xbmto5110 makes the first 2 bytes the x/y res. */

  for (/* see above index = 0 */ ; index < (LCD_X * LCD_Y / 8) ; index++)
    LCDWrite(LCD_DATA, my_array[index]);
}

void putPixel_toBuff(struct pix_buff *buff, 
                     unsigned char x, unsigned char y,
                     unsigned char pix_val)
{
  if (x > buff->width || y > buff->height) { return; }

  // The LCD has 6 rows, with 8 pixels per  row.
  // 'y_mod' is the row that the pixel is in.
  // 'y_pix' is the pixel in that row we want to enable/disable
  unsigned char y_mod = (y >> 3);	// >>3 divides by 8
  unsigned char y_pix = (y-(y_mod << 3));// <<3 multiplies by 8
  unsigned char val = 1 << y_pix;
  unsigned int index = x + (y_mod*84);

  gotoXY(x,y_mod);

  if(pix_val)
      buff->pixels[ index ] |=  val;
      //LCDWrite (1, val | screen_buf[y_mod][x]);
  else if(!ALPHA_ZERO)
      buff->pixels[ x + (y_mod*84)] &= ((1 << y_pix) ^ 0xff);
      //LCDWrite (1, ((1 << y_pix) ^ 0xff) & screen_buf[y_mod][x]);

}

void putPixel(unsigned char x, unsigned char y, unsigned char pix_val)
{
  if (x > 84 || y > 48) { return; }

  // The LCD has 6 rows, with 8 pixels per  row.
  // 'y_mod' is the row that the pixel is in.
  // 'y_pix' is the pixel in that row we want to enable/disable
  unsigned char y_mod = (y >> 3);	// >>3 divides by 8
  unsigned char y_pix = (y-(y_mod << 3));// <<3 multiplies by 8
  unsigned char val = 1 << y_pix;

  // Write the updated pixel out to the LCD
//  if(current_index != (x + (y_mod*84)))
    gotoXY(x,y_mod);
//  else
//      current_index++;
  
  if(pix_val)
      LCDWrite (1, val | screen_buf[y_mod][x]);
  else if(!ALPHA_ZERO)
      LCDWrite (1, ((1 << y_pix) ^ 0xff) & screen_buf[y_mod][x]);
  //LCDWrite (1,0xff);
}

void invertBuffArea(unsigned char x,
                    unsigned char y,
                    unsigned char width,
                    unsigned char height,
                    struct pix_buff *buff)
{
    unsigned char y_mod_start, y_pix_start, y_mod_end, y_pix_end, y_mod_diff;
    unsigned int base_y_start, base_y_end, sw_buff_i = 0;
    //start at top left corder,
    //determine y for top horizontel line
    y_mod_start = y >> 3; // determines byte element
    y_pix_start = 1 << (y - (y_mod_start << 3)); //determines bit within byte element

    base_y_start = y_mod_start * width; // start index

    y_mod_end = (y + height) >> 3;

    y_mod_diff = y_mod_end - y_mod_start;

    y_pix_end = 1 << ( (y + height ) - (y_mod_end << 3));

    //base_y_end = y_mod_end * buff->width;
    base_y_end = y_mod_end * width;

    unsigned int i = 0, j = 0, k = 0;

    unsigned char shift_down = (y - (y_mod_start << 3));
    unsigned char shift_down_end = ((y + height) - (y_mod_end << 3));
    unsigned char temp_x = x, stop = 0, data = 0xff;
    i = y_mod_start;

    if(!y_mod_diff)
    {
        stop = y_mod_start;
        data = (data >> (8 - height));
    }
    else
        stop = y_mod_end - 1;

    if(!shift_down)
    {
        sw_buff_i = (buff->width * y_mod_start) + x;

        for(j = y_mod_start * width + x, k = 0;
                j < ( (stop) * width + x) + width ; j++, k++)
        {
           //reached end of invert area's width?
           if(!( width - k - 1  ))
           {
                // reset index to start of next row in invert area  
                i += 1;
                k = 0;
                temp_x = x;
                buff->pixels[sw_buff_i] ^=  data;
                sw_buff_i = (buff->width * i) + x;
           }
           else
           {
               buff->pixels[sw_buff_i++] ^= data;
           }
        }

        sw_buff_i = (buff->width * y_mod_end) + x;
        if(y_mod_end != y_mod_start)
            for(j = ( (y_mod_end) * width + x );
                    j < (y_mod_end) * width + x + width;
                        j++)
            {
                buff->pixels[sw_buff_i++] ^=  (0xff >> shift_down_end);
            }
    }
    // if data pushed out of first row, or there is more to go
    else
    {
        sw_buff_i = 0;//buff->width;

        //should check if this cursor set is needed
        temp_x = x;

        // go through the first row in the buffer
        for(j = ( (y_mod_start) * buff->width + x );  //start w.r.t the buffer
                j < (y_mod_start) * buff->width + x + width;
                    j++)
        {
            buff->pixels[j] ^= (0xff << shift_down);
        }
        
        i = y_mod_start + 1;
        sw_buff_i = (buff->width * (y_mod_start + 1) ) + x;
        
        if( (y_mod_end - y_mod_start) > 1 && (y_mod_end - y_mod_start ) <7)
            for(j = (y_mod_start + 1) * width + x, k = 0;
                    j < ( (y_mod_end - 1 ) * width + x) + width; j++, k++)
            {

               //reached end of invert area's width?
               if(!( width - k - 1 ))
               {
                   buff->pixels[sw_buff_i++] ^=  0xff;
                    // reset index to start of next row in invert area
                    //sw_buff_i = (buff->width * i) + x;
                    k = 0;
                    i += 1;
                    temp_x = x;
                    sw_buff_i = (buff->width * i) + x;
               }
               else
               {
                buff->pixels[sw_buff_i++] ^=  0xff;
               }
            }

        sw_buff_i = (buff->width * y_mod_end) + x;
        if(y_mod_end != y_mod_start)
        for(j = ( (y_mod_end) * width + x );
                j < (y_mod_end) * width + x + width;
                    j++)
        {
            buff->pixels[sw_buff_i++] ^=  (0xff >> (8 - shift_down_end));
        }
    }
}

void putBuffByte(unsigned char x,
                 unsigned y,
                 unsigned char data,
                 struct pix_buff *buff)
{
  if (x > buff->width || y > buff->height) { return; }

  // The LCD has 6 rows, with 8 pixels per  row.
  // 'y_mod' is the row that the pixel is in.
  // 'y_pix' is the pixel in that row we want to enable/disable
  unsigned char y_mod_start = (y >> 3);	// >>3 divides by 8
  unsigned char y_pix = (y-(y_mod_start << 3));// <<3 multiplies by 8
  unsigned char val = 1 << y_pix;

  unsigned char shift_down = (y - (y_mod_start << 3));
  unsigned int index = (y_mod_start * buff->width) + x;

    if(!shift_down)
    {
        buff->pixels[index] |= data;
    }
    else
    {
        buff->pixels[index] |= (data << shift_down);
        index = ((y_mod_start + 1) * buff->width) + x;
        buff->pixels[index] |= (data >> 8 - shift_down);
    }
}

void putColumnByte(unsigned char x, unsigned char y, unsigned char pix_val)
{
if (x > 84 || y > 48) { return; }

  // The LCD has 6 rows, with 8 pixels per  row.
  // 'y_mod' is the row that the pixel is in.
  // 'y_pix' is the pixel in that row we want to enable/disable
  int y_mod = (int)(y >> 3);	// >>3 divides by 8
  int y_pix = (y-(y_mod << 3));// <<3 multiplies by 8
  int val = 1 << y_pix;

  // Write the updated pixel out to the LCD
  gotoXY(x,y_mod);
  if(pix_val)
      LCDWrite (1, 1 << y_pix | screen_buf[y_mod][x]);
  else
      LCDWrite (1, ((1 << y_pix) ^ 0xff) & screen_buf[y_mod][x]);
}

void LCDLogo() {
  LCDClear();
  LCDBitmap(hackrva);
  return;
//  writeXBM(hackrva_bits, hackrva_width, hackrva_height/8) ;
}

void LCD_RVASec_Logo() {
  LCDClear();
  LCDBitmap(rvasec_logo);
  return;
//  writeXBM(hackrva_bits, hackrva_width, hackrva_height/8) ;
}

//This function takes in a character, looks it up in the font table/array
//And writes it to the screen
//Each character is 8 bits tall and 5 bits wide. We pad one blank column of
//pixels on each side of the character for readability.
void LCDCharacter(char character) {
  int index;

  if(character == '\n' && Y < 6)
  {
      gotoXY(0, Y+1);
      return;
  }

  LCDWrite(LCD_DATA, 0x00); //Blank vertical line padding
  //current_index+=2;
  for (index = 0 ; index < 5 ; index++)// current_index++)
  {
      LCDWrite(LCD_DATA, ASCII[character - 0x20][index]);
      X = current_index % 84;
      Y = current_index / 84;
      screen_buf[Y][X] |=  ASCII[character - 0x20][index];
    //0x20 is the ASCII character for Space (' '). The font table starts with this character
  }

  LCDWrite(LCD_DATA, 0x00); //Blank vertical line padding
  X = current_index % 84;
  Y = current_index / 84;
}

//Given a string of characters, one by one is passed to the LCD
void LCDString(char *characters) {
  while (*characters)
    LCDCharacter(*characters++);
}

void buffCharacter(unsigned char x,
                    unsigned char y,
                    char character,
                    struct pix_buff *buff)
{
  int index;

  for (index = 0 ; index < 5 ; index++)// current_index++)
  {
    //  LCDWrite(LCD_DATA, ASCII[character - 0x20][index]);
      putBuffByte(x + index, y, ASCII[character - 0x20][index], buff);
      X = current_index % 84;
      Y = current_index / 84;
      //screen_buf[Y][X] |=  ASCII[character - 0x20][index];
    //0x20 is the ASCII character for Space (' '). The font table starts with this character
  }

  //LCDWrite(LCD_DATA, 0x00); //Blank vertical line padding
  X = current_index % 84;
  Y = current_index / 84;
}

#define CHAR_HEIGHT 7
#define CHAR_WIDTH 6
void buffString(unsigned char x, 
                unsigned char y,
                char *characters,
                struct pix_buff *buff)
{
    while(*characters)
    {
        if(x > 79 || *characters == '\n')
        {
            if(*characters == '\n')
                *characters++;
            
            y += CHAR_HEIGHT;
            x = 0;
        }
        buffCharacter(x, y, *characters++, buff);
        x += CHAR_WIDTH;
    }
}

void buffString_trunc(unsigned char x,
                        unsigned char y,
                        char *characters,
                        unsigned char trunc_lim,         //truncate if it exceeds
                        unsigned char trunc_start,       //index to inser trunc
                        const unsigned char *trunc_string,
                        struct pix_buff *buff)
{
    unsigned char cnt = 0;

    while((characters[cnt]) && (cnt < trunc_lim) )  
        cnt++;

    if(cnt == trunc_lim && characters[cnt])
    {
        cnt = 0;
        while(*characters && (cnt++ < trunc_start) )
        {
            if(x > 79 || *characters == '\n' )
            {
                if(*characters == '\n')
                    *characters++;

                y += CHAR_HEIGHT;
                x = 0;
            }

            buffCharacter(x, y, *characters++, buff);
            x += CHAR_WIDTH;
        }
        if(cnt >= trunc_start)
            while(*trunc_string)
            {
                if(x > 79 || *trunc_string == '\n' )
                {
                    if(*trunc_string == '\n')
                        *trunc_string++;

                    y += CHAR_HEIGHT;
                    x = 0;
                }

                buffCharacter(x, y, *trunc_string++, buff);
                x += CHAR_WIDTH;
            }
    }
    else
    {
        while(*characters)
        {
            if(x > 79 || *characters == '\n')
            {
                if(*characters == '\n')
                    *characters++;

                y += CHAR_HEIGHT;
                x = 0;
            }
            buffCharacter(x, y, *characters++, buff);
            x += CHAR_WIDTH;
        }
    }
}


void clear_screen_buff(void)
{
  unsigned char y, x;
  //for (index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
  for (y = 0 ; y < 6 ; y++)
  {
      for( x =0; x < 84; x++)
      {
          screen_buf[y][x] = 0x00;
      }
  }
}

//Clears the LCD by writing zeros to the entire screen
void LCDClear(void) {
  unsigned char y, x;
  //for (index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
  for (y = 0 ; y < 6 ; y++)
  {
      for( x =0; x < 84; x++)
      {
          LCDWrite(LCD_DATA, 0x00);
          screen_buf[y][x] = 0x00;
      }
  }
  current_index = 0;
  gotoXY(0, 0); //After we clear the display, return to the home position
}


void LCDReset(void) {
  PIN_SCE = 0;
  DELAY;

  PIN_RESET = 1;
  DELAY;
  DELAY; // XXX

  PIN_RESET = 0;
  DELAY;
  DELAY; // XXX

  PIN_RESET = 1;
  DELAY;
  DELAY; // XXX

  PIN_SCE = 1;
  DELAY;
}

//This sends the magical commands to the PCD8544
void LCDInit(void) {

//  LCDReset();

  LCDWrite(LCD_COMMAND, 0x21); //Tell LCD that extended commands follow (H=1) V=0

  // set Vop (bit 8 set or with Vop value)
  LCDWrite(LCD_COMMAND, gContrast); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
//  LCDWrite(LCD_COMMAND, 0xB0); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark

  LCDWrite(LCD_COMMAND, 0x04); //Set Temp coefficent
  LCDWrite(LCD_COMMAND, 0x14); //LCD bias mode 1:48: Try 0x13 or 0x14

  LCDWrite(LCD_COMMAND, 0x20); //We must send 0x20 before modifying the display control mode
  LCDWrite(LCD_COMMAND, 0x0C); //Set display control, normal mode. 0x0D for inverse

   current_index = 0;
}

//#define SDELAY { int i; for (i=0; i<100; i++) ; }
// short delay
#define SDELAY { int i; for (i=0; i<20; i++) ; }

//There are two memory banks in the LCD, data/RAM and commands. This 
//function sets the DC pin high or low depending, and then sends
//the data byte
void LCDWrite(byte data_or_command, byte data) {
  if(data_or_command == LCD_DATA)
  {
    setBuf(data);
    current_index++;
    X = current_index % 84;
    Y = current_index / 84;
  }
  
  PIN_DC = data_or_command;
  SDELAY;

  PIN_SCE = 0;
  SDELAY;

  PIN_SDIN = (data & 0b10000000) ? 1 : 0;
  PIN_SCLK = 1;
  SDELAY;
  PIN_SCLK = 0;
  PIN_SDIN = 0;
  SDELAY;

  PIN_SDIN = (data & 0b01000000) ? 1 : 0;
  PIN_SCLK = 1;
  SDELAY;
  PIN_SCLK = 0;
  PIN_SDIN = 0;
  SDELAY;

  PIN_SDIN = (data & 0b00100000) ? 1 : 0;
  PIN_SCLK = 1;
  DELAY;
  PIN_SCLK = 0;
  PIN_SDIN = 0;
  SDELAY;

  PIN_SDIN = (data & 0b00010000) ? 1 : 0;
  PIN_SCLK = 1;
  SDELAY;
  PIN_SCLK = 0;
  PIN_SDIN = 0;
  SDELAY;

  PIN_SDIN = (data & 0b00001000) ? 1 : 0;
  PIN_SCLK = 1;
  SDELAY;
  PIN_SCLK = 0;
  PIN_SDIN = 0;
  SDELAY;

  PIN_SDIN = (data & 0b00000100) ? 1 : 0;
  PIN_SCLK = 1;
  SDELAY;
  PIN_SCLK = 0;
  PIN_SDIN = 0;
  SDELAY;

  PIN_SDIN = (data & 0b00000010) ? 1 : 0;
  PIN_SCLK = 1;
  SDELAY;
  PIN_SCLK = 0;
  PIN_SDIN = 0;
  SDELAY;

  PIN_SDIN = (data & 0b00000001) ? 1 : 0;
  PIN_SCLK = 1;
  SDELAY;
  PIN_SCLK = 0;
  PIN_SDIN = 0;
  SDELAY;

  PIN_SCE = 1;
  SDELAY;

}

//============================================================================
// Name: xbmto5110.cpp - host side code to convert .xbm to c
// Author: rick@kimballsoftware.com
// Version: 1.0
// Date:  2-1-2013
// Copyright: copyright (c) 2013 rick@kimballsoftware.com
// License: public domain
// Description: .xbm to nokia 5110 c unsigned array .c
//============================================================================

// PEB ripped and converted to run in pic32

unsigned getpixel(unsigned row, unsigned col, const char *bm_bits, unsigned bm_width) {
  unsigned byte_offset = (row * ((bm_width + 7) / 8)) + (col / 8);
  unsigned bitmask_offset = 1 << (col % 8);

  return (bm_bits[byte_offset] & bitmask_offset) ? 1 : 0;
}

/*
* flip bitmap bytes from xbm style where each byte is a row by 8 columns of bits to
* 5510 style where each byte is a column by 8 rows of bits
*
* see: nokia 5110 datasheet for details
*/
void writeXBM(const char *bm, unsigned bm_width, unsigned bm_height) {
  unsigned row, col;

  for (row = 0; row < bm_height; row += 8) {
    for (col = 0; col < bm_width; col++) {
      unsigned char ucol_8rows = 0; // one column by 8 rows of bits
      unsigned indx;

      // repack bits into new col order
      for (indx = 0; indx < 8; indx++) {
        unsigned bit = getpixel(row + indx, col, bm, bm_width);
        ucol_8rows |= (bit << indx);

        LCDWrite(LCD_DATA, ucol_8rows);
      }
    }
  }
}

//void drawLine

void setBuf(unsigned char val)
{
  //int y_mod = (int)(y >> 3);	// >>3 divides by 8
  //int y_pix = (y-(y_mod << 3));// <<3 multiplies by 8
  //int val = 1 << y_pix;
    unsigned char x, y;
    x = current_index % 84; // - (84 * current_index/84);
    y = current_index / 84;
    screen_buf[y][x] = val;
  // Write the updated pixel out to the LCD
  //gotoXY(x,y_mod);
}

void blitBuff_toBuff(struct pix_buff *src_buff, struct pix_buff *dest_buff,
                      unsigned char x,
                      unsigned char y,
                      BLIT_STYLE_t style)
{
    unsigned char src_y_mod_start, src_y_pix_start, src_y_mod_end, src_y_pix_end;
    unsigned char dest_y_mod_start, dest_y_pix_start, dest_y_mod_end, dest_y_pix_end;
    //unsigned char y_mod_start, y_pix_start, y_mod_end, y_pix_end;
    unsigned int src_base_y_start, src_base_y_end, src_sw_buff_i = 0;
    unsigned int dest_base_y_start, dest_base_y_end, dest_sw_buff_i = 0;

    // how many byte rows are in the source buffer
    unsigned char buff_mods = (src_buff->height >> 3) + 1;
    
    //do checks
    if( dest_buff->height < (src_buff->height + y)
        || dest_buff->width < src_buff->width + x)
        return;

    // determines starting byte row
    dest_y_mod_start = y >> 3;
    //determines bit within starting byte element
    dest_y_pix_start = 1 << (y - (dest_y_mod_start << 3));
    // start index of destination given x and y
    dest_base_y_start = dest_y_mod_start * dest_buff->width;
    // end byte row of destination given x and by and src height
    dest_y_mod_end = (y + src_buff->height) >> 3;
    // where last pixel is in end byte row
    dest_y_pix_end = 1 << ( (y + src_buff->height ) - (dest_y_mod_end << 3));

    //need this?
    dest_base_y_end = dest_y_mod_end * dest_buff->width;

    src_y_mod_start = 0;
    // this can be greater than the mod where real data is (x = 0, height =
    src_y_mod_end = src_y_mod_start + buff_mods;
    
    unsigned int i = 0, j = 0, k = 0;

    unsigned char shift_down = (y - (dest_y_mod_start << 3));
    unsigned char shift_down_end = (y - (dest_y_mod_end << 3));
    
    unsigned int sw_buff_i_end = buff_mods * src_buff->width;
    unsigned char temp_x = x;


    i = src_y_mod_start;
    j = dest_y_mod_start;
    // if src will be blitted at start of byte
    if(!shift_down)
    {
        //go through the entire source buffer index
        for(src_sw_buff_i = 0; 
                src_sw_buff_i < sw_buff_i_end ;
                    src_sw_buff_i++, dest_sw_buff_i++)
        {
           //check for start of row
           if(!(src_sw_buff_i % src_buff->width))
           {
               //get index of dest buff location
               dest_sw_buff_i = (j * dest_buff->width) + x;
               j++;
               src_sw_buff_i = i * src_buff->width;
               i++;
               //temp_x = x;
           }

           if(style == ALPHA)
               dest_buff->pixels[dest_sw_buff_i] |= src_buff->pixels[src_sw_buff_i];
           else// if (style == OPAQUE)
                dest_buff->pixels[dest_sw_buff_i] = src_buff->pixels[src_sw_buff_i];
        }
    }

    else
    {
        src_sw_buff_i = 0;//buff->width;
        dest_sw_buff_i = dest_y_mod_start * dest_buff->width + x;

        //set LCD cursor to the right row
        //gotoXY(x, i);
        //reset x
        temp_x = x;

        // go through the first row in the buffer, it has to be split
        // given the y value
        for(j = src_sw_buff_i; j < src_sw_buff_i + src_buff->width; j++, dest_sw_buff_i++)
        {
           if(style == ALPHA)
               dest_buff->pixels[dest_sw_buff_i] |= (src_buff->pixels[j] << shift_down);
           else// if (style == OPAQUE)
                dest_buff->pixels[dest_sw_buff_i] = (src_buff->pixels[j] << shift_down);
        }

        // reset SW buff, since first SW byte row is only partially blit
        src_sw_buff_i = 0;

        //enter loop if buffer will span more than two LCD rows
        // -> if so, this should write out the middle portions
        for (i = src_y_mod_start + 1, k = dest_y_mod_start +1;
                i < src_y_mod_end; i++, k++)
        {
            //go to the next row
            //gotoXY(x, i);
            dest_sw_buff_i = k * dest_buff->width + x;
            temp_x = x;

            // go through the first row in the buffer
            for(j = src_sw_buff_i , k = src_sw_buff_i + src_buff->width;
                        j < src_sw_buff_i + src_buff->width; j++, k++, dest_sw_buff_i++)
            {
               if(style == ALPHA)
                   dest_buff->pixels[dest_sw_buff_i] |= 
                           (src_buff->pixels[j] >> 8 -shift_down)
                          |(src_buff->pixels[k] << shift_down);
               else// if (style == OPAQUE)
                    dest_buff->pixels[dest_sw_buff_i] =
                            (src_buff->pixels[j] >> 8 -shift_down)
                           |(src_buff->pixels[k] << (shift_down));
            }

            src_sw_buff_i += src_buff->width;
        }

        //blit last row byte
        if(src_y_mod_start != src_y_mod_end)
        {
            //reset to the last row in the buffer
            src_sw_buff_i = ((src_buff->height >> 3 )) * src_buff->width;
            dest_sw_buff_i = ( (src_buff->height + y) >> 3 ) * dest_buff->width + x;
            i = src_y_mod_end;
            //should check if this cursor set is needed
            //gotoXY(x, i);
            temp_x = x;

            // go through the first row in the buffer
            for(j = src_sw_buff_i , k = src_sw_buff_i + src_buff->width;
                        j < src_sw_buff_i + src_buff->width; j++, k++, dest_sw_buff_i++)
            {

               if(style == ALPHA)
                   dest_buff->pixels[dest_sw_buff_i] |= (src_buff->pixels[j] >> 8 -shift_down);
               else// if (style == OPAQUE)
                    dest_buff->pixels[dest_sw_buff_i] = (src_buff->pixels[j] >> 8 -shift_down);
            }
        }
    }
}


void blitBuff_opt(struct pix_buff* buff,
                  unsigned char x,
                  unsigned char y,
                  BLIT_STYLE_t style)
{
    unsigned char y_mod_start, y_pix_start, y_mod_end, y_pix_end;
    unsigned int base_y_start, base_y_end, sw_buff_i = 0;
    //start at top left corder,
    //determine y for top horizontel line
    y_mod_start = y >> 3; // determines byte element
    y_pix_start = 1 << (y - (y_mod_start << 3)); //determines bit within byte element
    base_y_start = y_mod_start * buff->width; // start index

    //y_mod_end = (y + buff->height - 1) >> 3;
    y_mod_end = (y + buff->height) >> 3;
    
    //y_pix_end = 1 << ( (y + buff->height - 1) - (y_mod_end << 3));
    y_pix_end = 1 << ( (y + buff->height ) - (y_mod_end << 3));

    base_y_end = y_mod_end * buff->width;

    unsigned int i = 0, j = 0, k = 0;

    unsigned char shift_down = (y - (y_mod_start << 3));
    unsigned char shift_down_end = (y - (y_mod_end << 3));
    unsigned char buff_mods = (buff->height >> 3) + 1;
    y_mod_end = y_mod_start + buff_mods;
    unsigned int sw_buff_i_end = buff_mods * buff->width;
    unsigned char temp_x = x;
    i = y_mod_start;
    if(!shift_down)
    {
        //for(sw_buff_i = 0; sw_buff_i < base_y_end ; sw_buff_i++)
        for(sw_buff_i = 0; sw_buff_i < sw_buff_i_end ; sw_buff_i++)
        {
           if(!(sw_buff_i % buff->width))
           {
                gotoXY(x, i);
                i += 1;
                temp_x = x;
           }

           if(style == ALPHA)
            LCDWrite(LCD_DATA,
                buff->pixels[sw_buff_i]
               | screen_buf[i - 1][temp_x++] );
           else// if (style == OPAQUE)
               LCDWrite(LCD_DATA,
                buff->pixels[sw_buff_i]);
        }
    }

    // -->if byte data is not aligned with the LCD byte rows,
    //then every data byte is split across two LCD rows
    // -->this would be much more simple if we based blit on the
    // SW data, but this would require re-addressing the LCD
    // cursor multiple times for each bytes in the buffer
    else
    {
        sw_buff_i = 0;//buff->width;

        //set LCD cursor to the right row
        gotoXY(x, i);
        //reset x
        temp_x = x;

        // go through the first row in the buffer, it has to be split
        // given the y value
        for(j = sw_buff_i; j < sw_buff_i + buff->width; j++)
        {
            //push the row
            if(style == ALPHA)
                LCDWrite(LCD_DATA,
                       (buff->pixels[j] << shift_down)
                        | screen_buf[i][temp_x++]);
            else
                LCDWrite(LCD_DATA,
                       (buff->pixels[j] << shift_down));
        }

        // reset SW buff, since first SW byte row is only partially blit
        sw_buff_i = 0;

        //enter loop if buffer will span more than two LCD rows
        // -> if so, this should write out the middle portions
        for (i = y_mod_start+1; i < y_mod_end; i++)
        {
            //go to the next row
            gotoXY(x, i);
            temp_x = x;

            // go through the first row in the buffer
            for(j = sw_buff_i , k = sw_buff_i + buff->width;
                        j < sw_buff_i + buff->width; j++, k++)
            {
//                //push the row
                if(style == ALPHA)
                    LCDWrite(LCD_DATA,
                           (buff->pixels[j] >> 8 -shift_down)
                          | (buff->pixels[k] << (shift_down))
                          | screen_buf[i][temp_x++]  );
                else
                    LCDWrite(LCD_DATA,
                           (buff->pixels[j] >> 8 -shift_down)
                          | (buff->pixels[k] << (shift_down)));
            }

            sw_buff_i += buff->width;
        }

        //blit last row byte
        if(y_mod_start != y_mod_end)
        {
            //reset to the last row in the buffer
            sw_buff_i = ((buff->height >> 3 )) * buff->width;
            i = y_mod_end;
            //should check if this cursor set is needed
            gotoXY(x, i);
            temp_x = x;

            // go through the first row in the buffer
            for(j = sw_buff_i , k = sw_buff_i + buff->width;
                        j < sw_buff_i + buff->width; j++, k++)
            {
                //push the row
                if(style == ALPHA)
                    LCDWrite(LCD_DATA,
                           (buff->pixels[j] >> 8 -shift_down)
      //                    | (buff->pixels[k] << (shift_down))
                            //(buff->pixels[j] << (shift_down))
                          | screen_buf[i][temp_x++]  );
                else
                    LCDWrite(LCD_DATA,
                           (buff->pixels[j] >> 8 -shift_down));

            }
        }
    }
}


//this blit needs to be smarter and utilize the LCD auto increment
// and not put pixel!
void blitBuff(struct pix_buff* buff, unsigned char x, unsigned char y)
{
    unsigned char lcd_y, lcd_x, buff_y, buff_x;
    unsigned int buff_index = 0;

    //start at top left corner,
    for(lcd_y = y; lcd_y < y + buff->height; lcd_y+=8) // 0 -> 48 {8,16,24,32}
    {
        for( lcd_x = x; lcd_x < x + buff->width; lcd_x++, buff_index++) //0 -> 84
        {
            // saves loop operation overhead, stays simple
            putPixel(lcd_x, lcd_y,     buff->pixels[ buff_index ] & 0x01);
            putPixel(lcd_x, lcd_y + 1, buff->pixels[ buff_index ] & 0x02);
            putPixel(lcd_x, lcd_y + 2, buff->pixels[ buff_index ] & 0x04);
            putPixel(lcd_x, lcd_y + 3, buff->pixels[ buff_index ] & 0x08);
            putPixel(lcd_x, lcd_y + 4, buff->pixels[ buff_index ] & 0x10);
            putPixel(lcd_x, lcd_y + 5, buff->pixels[ buff_index ] & 0x20);
            putPixel(lcd_x, lcd_y + 6, buff->pixels[ buff_index ] & 0x40);
            putPixel(lcd_x, lcd_y + 7, buff->pixels[ buff_index ] & 0x80);
        }
    }
}

// buff to buff and check for overlap (collisions)
unsigned char blitBuff_toBuff_collision(struct pix_buff *src_buff, struct pix_buff *dest_buff,
                      unsigned char x,
                      unsigned char y,
                      BLIT_STYLE_t style)
{
    unsigned char src_y_mod_start, src_y_pix_start, src_y_mod_end, src_y_pix_end;
    unsigned char dest_y_mod_start, dest_y_pix_start, dest_y_mod_end, dest_y_pix_end;
    //unsigned char y_mod_start, y_pix_start, y_mod_end, y_pix_end;
    unsigned int src_base_y_start, src_base_y_end, src_sw_buff_i = 0;
    unsigned int dest_base_y_start, dest_base_y_end, dest_sw_buff_i = 0;

    // how many byte rows are in the source buffer
    unsigned char buff_mods = (src_buff->height >> 3) + 1;
    unsigned char found = 0;
    //do checks
    if( dest_buff->height < (src_buff->height + y)
        || dest_buff->width < src_buff->width + x)
        return found;

    // determines starting byte row
    dest_y_mod_start = y >> 3;
    //determines bit within starting byte element
    dest_y_pix_start = 1 << (y - (dest_y_mod_start << 3));
    // start index of destination given x and y
    dest_base_y_start = dest_y_mod_start * dest_buff->width;
    // end byte row of destination given x and by and src height
    dest_y_mod_end = (y + src_buff->height) >> 3;
    // where last pixel is in end byte row
    dest_y_pix_end = 1 << ( (y + src_buff->height ) - (dest_y_mod_end << 3));

    //need this?
    dest_base_y_end = dest_y_mod_end * dest_buff->width;

    src_y_mod_start = 0;
    // this can be greater than the mod where real data is (x = 0, height =
    src_y_mod_end = src_y_mod_start + buff_mods;

    unsigned int i = 0, j = 0, k = 0;

    unsigned char shift_down = (y - (dest_y_mod_start << 3));
    unsigned char shift_down_end = (y - (dest_y_mod_end << 3));

    unsigned int sw_buff_i_end = buff_mods * src_buff->width;
    unsigned char temp_x = x;


    i = src_y_mod_start;
    j = dest_y_mod_start;
    // if src will be blitted at start of byte
    if(!shift_down)
    {
        //go through the entire source buffer index
        for(src_sw_buff_i = 0;
                src_sw_buff_i < sw_buff_i_end ;
                    src_sw_buff_i++, dest_sw_buff_i++)
        {
           //check for start of row
           if(!(src_sw_buff_i % src_buff->width))
           {
               //get index of dest buff location
               dest_sw_buff_i = (j * dest_buff->width) + x;
               j++;
               src_sw_buff_i = i * src_buff->width;
               i++;
               //temp_x = x;
           }
           if(dest_buff->pixels[dest_sw_buff_i] & src_buff->pixels[src_sw_buff_i])
               found = 1;
           
           if(style == ALPHA)
               dest_buff->pixels[dest_sw_buff_i] |= src_buff->pixels[src_sw_buff_i];
           else// if (style == OPAQUE)
                dest_buff->pixels[dest_sw_buff_i] = src_buff->pixels[src_sw_buff_i];
           

        }
    }

    else
    {
        src_sw_buff_i = 0;//buff->width;
        dest_sw_buff_i = dest_y_mod_start * dest_buff->width + x;

        //set LCD cursor to the right row
        //gotoXY(x, i);
        //reset x
        temp_x = x;

        // go through the first row in the buffer, it has to be split
        // given the y value
        for(j = src_sw_buff_i; j < src_sw_buff_i + src_buff->width; j++, dest_sw_buff_i++)
        {
           if( dest_buff->pixels[dest_sw_buff_i] & (src_buff->pixels[j] << shift_down) )
                found = 1;

           if(style == ALPHA)
               dest_buff->pixels[dest_sw_buff_i] |= (src_buff->pixels[j] << shift_down);
           else// if (style == OPAQUE)
               dest_buff->pixels[dest_sw_buff_i] = (src_buff->pixels[j] << shift_down);
        }

        // reset SW buff, since first SW byte row is only partially blit
        src_sw_buff_i = 0;

        //enter loop if buffer will span more than two LCD rows
        // -> if so, this should write out the middle portions
        for (i = src_y_mod_start + 1, k = dest_y_mod_start +1;
                i < src_y_mod_end; i++, k++)
        {
            //go to the next row
            //gotoXY(x, i);
            dest_sw_buff_i = k * dest_buff->width + x;
            temp_x = x;

            // go through the first row in the buffer
            for(j = src_sw_buff_i , k = src_sw_buff_i + src_buff->width;
                        j < src_sw_buff_i + src_buff->width; j++, k++, dest_sw_buff_i++)
            {
               if (dest_buff->pixels[dest_sw_buff_i] &
                        ((src_buff->pixels[j] >> 8 -shift_down)
                       |src_buff->pixels[k] << (shift_down)) )
                    found = 1;

               if(style == ALPHA)
                   dest_buff->pixels[dest_sw_buff_i] |=
                           (src_buff->pixels[j] >> 8 -shift_down)
                          |(src_buff->pixels[k] << shift_down);
               else// if (style == OPAQUE)
                    dest_buff->pixels[dest_sw_buff_i] =
                            (src_buff->pixels[j] >> 8 -shift_down)
                           |(src_buff->pixels[k] << (shift_down));
            }

            src_sw_buff_i += src_buff->width;
        }

        //blit last row byte
        if(src_y_mod_start != src_y_mod_end)
        {
            //reset to the last row in the buffer
            src_sw_buff_i = ((src_buff->height >> 3 )) * src_buff->width;
            dest_sw_buff_i = ( (src_buff->height + y) >> 3 ) * dest_buff->width + x;
            i = src_y_mod_end;
            //should check if this cursor set is needed
            //gotoXY(x, i);
            temp_x = x;

            // go through the first row in the buffer
            for(j = src_sw_buff_i , k = src_sw_buff_i + src_buff->width;
                        j < src_sw_buff_i + src_buff->width; j++, k++, dest_sw_buff_i++)
            {
               if( dest_buff->pixels[dest_sw_buff_i] & (src_buff->pixels[j] >> 8 -shift_down) )
                    found = 1;

               if(style == ALPHA)
                   dest_buff->pixels[dest_sw_buff_i] |= (src_buff->pixels[j] >> 8 -shift_down);
               else// if (style == OPAQUE)
                    dest_buff->pixels[dest_sw_buff_i] = (src_buff->pixels[j] >> 8 -shift_down);
            }
        }
    }
    return found;
}
