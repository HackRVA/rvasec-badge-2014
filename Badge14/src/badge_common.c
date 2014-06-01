#include "badge_common.h"
#include "Common/Compiler.h"



char do_BTM_CapTouch_Right() {

    register char s0, s1, s2, s3, s4, s5, s6, s7;
   
   //G_lower_slider_right = 0;

   // pulls up off
   CNPUCbits.CNPUC4 = 0;
   // set as output
   TRISCbits.TRISC4 = 0;
   // zero output. according to datasheet also writes latch bit
   PORTCbits.RC4  = 0;

   // config as input
   TRISCbits.TRISC4 = 1;
   // pull up on
   CNPUCbits.CNPUC4 = 1;

   // wait for cap to charge
   s0 = PORTCbits.RC4;
   s1 = PORTCbits.RC4;
   s2 = PORTCbits.RC4;
   s3 = PORTCbits.RC4;
   s4 = PORTCbits.RC4;
   s5 = PORTCbits.RC4;
   s6 = PORTCbits.RC4;
   s7 = PORTCbits.RC4;

   return s0 + s1 + s2 + s3 + s4 + s5 + s6 + s7;
}

char do_BTM_CapTouch_Left() {
   register char s0, s1, s2, s3, s4, s5, s6, s7;

   //G_lower_slider_left = 0;

   // pulls up off
   CNPUCbits.CNPUC5 = 0;
   // set as output
   TRISCbits.TRISC5 = 0;
   // zero output. according to datasheet also writes latch bit
   PORTCbits.RC5  = 0;

   // config as input
   TRISCbits.TRISC5 = 1;
   // pull up on
   CNPUCbits.CNPUC5 = 1;
   // see when cap is charged

   s0 = PORTCbits.RC5;
   s1 = PORTCbits.RC5;
   s2 = PORTCbits.RC5;
   s3 = PORTCbits.RC5;
   s4 = PORTCbits.RC5;
   s5 = PORTCbits.RC5;
   s6 = PORTCbits.RC5;
   s7 = PORTCbits.RC5;

   return s0 + s1 + s2 + s3 + s4 + s5 + s6 + s7;
}

void set_leds(unsigned char leds)
{
    TRISBbits.TRISB14 = 0;
//RB3, RB2, RB1, RB0, RA1, RA0, RB15, RB14
 //  RB14, RB15, RA0, RA1, RB0, RB1, RB2, RB3
   LATBbits.LATB3 = 0x01 & leds;
   LATBbits.LATB2 =(0x02 & leds) >> 1;
   LATBbits.LATB1 = (0x04 & leds) >> 2;
   LATBbits.LATB0 = (0x08 & leds) >> 3;

   LATAbits.LATA1 = (0x10 & leds) >> 4;
   LATAbits.LATA0 = (0x20 & leds) >> 5;

   LATBbits.LATB15 = (0x40 & leds) >> 6;
   LATBbits.LATB14 = 1;// (0x80 & leds) >> 7;

}

// use to clear buffer, fill solid, or some nice patter
void fill_buff(struct pix_buff *buff, unsigned char val)
{
    unsigned int i;
    unsigned int max = (buff->height>>3) * buff->width;
    for(i = 0; i < max; i++)
        buff->pixels[i] = val;
}

void fill_buff_area(struct coord loc,
                    unsigned char width,
                    unsigned char height,
                    unsigned char fill,
                    struct pix_buff *dest_buff)
{
    unsigned int i, j, total_el = (dest_buff->height >> 3) * dest_buff->width;

    unsigned char y_mod, y_pix, y_mod_end;
    unsigned int base_y, base_y_end;

    //should do other checks?
    if (loc.x > dest_buff->width || loc.y > dest_buff->height)
        return;

    //start at top left corder,
    //determine y for top horizontel line
    y_mod = loc.y >> 3; // determines byte element
    //y_pix = 1 << (loc.y - (y_mod << 3)); //determines bit within byte element
    y_pix = 0xff >> 8 - (loc.y - (y_mod << 3)); //determines bit within byte element
    base_y = y_mod * dest_buff->width; // start index

    y_mod_end = (loc.y + height - 1) >> 3;

    unsigned char y_pix_fill = 0xff << (loc.y - (y_mod << 3)); // get high bits for byte
    //draw top line
    for ( i = loc.x; i < loc.x + width; i++ )
    {
        //dest_buff->pixels[ base_y + i] |= y_pix;
        dest_buff->pixels[ base_y + i] |= y_pix_fill;
    }
    //do edges
    //do first, possible partial edge row

//    dest_buff->pixels[ base_y + loc.x ] |= y_pix_fill;
//    dest_buff->pixels[ base_y + loc.x + width] |= y_pix_fill;

    if(y_mod_end != y_mod)
    {
        y_pix_fill = 0xff >> 8 - (loc.y + height - (y_mod_end << 3));
        dest_buff->pixels[ y_mod_end  * dest_buff->width + loc.x ] |= y_pix_fill;
        dest_buff->pixels[ y_mod_end  * dest_buff->width + loc.x + width  - 1] |= y_pix_fill;
    }

    for(i = y_mod + 1; i < y_mod_end; i++)
    {
        base_y = i * dest_buff->width;

        for ( j = base_y; j < base_y + width; j++ )
        {
            dest_buff->pixels[ loc.x +  j ] |= 0xff; //y_pix_fill;
        }
    }

    //determine y for bottom horizontel line
    y_mod = (loc.y + height -1) >> 3; // determines byte element
    y_pix = 1 << ((loc.y + height -1) - (y_mod << 3)); //determines bit within byte element
    base_y = y_mod * dest_buff->width; // start index

    for ( i = loc.x + 1; i < loc.x + width ; i++ )
    {

        dest_buff->pixels[ base_y + i] |= y_pix_fill;
    }
}

//put a pixel on a one dimensional buffer
void putPix_to_buff(struct pix_buff *dest_buff, unsigned char x, unsigned char y)
{
    unsigned char i, j;

    unsigned char y_mod, y_pix, val;
    unsigned int base_y, base_y_end;
    
    //should do other checks?
    if (x > dest_buff->width || y > dest_buff->height)
        return;

    //start at top left corder,
    //determine y for top horizontel line
    y_mod = y >> 3; // determines byte element
    y_pix = 1 << (y - (y_mod << 3)); //determines bit within byte element
    val = 1 << y_pix;
    base_y = y_mod * dest_buff->width; // start index
    dest_buff->pixels[base_y + x] |= val;
}

void draw_square(struct pix_buff *dest_buff, struct coord loc,
                unsigned char width, unsigned char height)
{
    unsigned char i, j;

    unsigned char y_mod, y_pix, y_mod_end;
    unsigned int base_y, base_y_end;

    //should do other checks?
    if (loc.x > dest_buff->width || loc.y > dest_buff->height)
        return;

    //start at top left corder,
    //determine y for top horizontel line
    y_mod = loc.y >> 3; // determines byte element
    y_pix = 1 << (loc.y - (y_mod << 3)); //determines bit within byte element
    base_y = y_mod * dest_buff->width; // start index

    y_mod_end = (loc.y + height - 1) >> 3;
    //draw top line
    for ( i = loc.x; i < loc.x + width; i++ )
    {
        dest_buff->pixels[ base_y + i] |= y_pix;
    }

    //do edges
    //do first, possible partial edge row
    unsigned char y_pix_fill = 0xff << (loc.y - (y_mod << 3)); // get high bits for byte
    dest_buff->pixels[ base_y + loc.x ] |= y_pix_fill;
    dest_buff->pixels[ base_y + loc.x + width] |= y_pix_fill;

    //do last edge
    if(y_mod_end != y_mod)
    {
        y_pix_fill = 0xff >> 8 - (loc.y + height - (y_mod_end << 3));
        dest_buff->pixels[ y_mod_end  * dest_buff->width + loc.x ] |= y_pix_fill;
        dest_buff->pixels[ y_mod_end  * dest_buff->width + loc.x + width ] |= y_pix_fill;
    }

    for(i = y_mod + 1, j = 1; i < y_mod_end; i++, j++)
    {
        base_y = i * dest_buff->width;

        dest_buff->pixels[base_y + loc.x ] |= 0xff;
        dest_buff->pixels[base_y + loc.x + width ] |= 0xff;
    }

    //determine y for bottom horizontel line
    y_mod = (loc.y + height -1) >> 3; // determines byte element
    y_pix = 1 << ((loc.y + height -1) - (y_mod << 3)); //determines bit within byte element
    base_y = y_mod * dest_buff->width; // start index

    for ( i = loc.x + 1; i < loc.x + width ; i++ )
    {
        dest_buff->pixels[ base_y + i] |= y_pix;
    }
}

void b_strcpy(char* dest, const char* src)
{
    unsigned char offset = 0;
    // looking for null
    while(*(src + offset))
    {
        *dest = *(src + offset);
        dest++;
        offset++;
    }
    *dest = 0;
}

void intTime_to_charTime(char* c_time, unsigned int i_time)
{
    unsigned char hours = i_time/10000;
    unsigned char minutes = (i_time - (hours * 10000))/100 ;
    c_time[0] = 48 + (unsigned char) hours / 10;
    c_time[1] = 48 + (unsigned char) hours % 10;
    c_time[2] = ':';
    c_time[3] = 48 + (unsigned char) minutes / 10;
    c_time[4] = 48 + (unsigned char) minutes % 10;
    c_time[5] = 0;
}

// only supports 3 digit
//void itoa(unsigned char in_num, unsigned char *out_alpha)
//{
//    out_alpha[0] = 'L';
//    out_alpha[1] = 48 +  (unsigned char)in_num / 100;
//    out_alpha[2] = 48 + ((unsigned char)in_num % 100) / 10;
//    out_alpha[3] = 48 + ((unsigned char)in_num % 100) % 10;
//    out_alpha[4] = 32;
//    out_alpha[5] = 0;
//}