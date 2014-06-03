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
   LATBbits.LATB14 = (0x80 & leds) >> 7;

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

    if(y_mod == y_mod_end)
        y_pix_fill &= 0xff >> 8 - (loc.y + height - (y_mod_end << 3));

    //draw top section
    for ( i = loc.x; i < loc.x + width; i++ )
    {
        //dest_buff->pixels[ base_y + i] |= y_pix;
        dest_buff->pixels[ base_y + i] |= y_pix_fill;
    }

    if(y_mod_end != y_mod)
    {
        y_pix_fill = 0xff >> 8 - (loc.y + height - (y_mod_end << 3));
        dest_buff->pixels[ y_mod_end  * dest_buff->width + loc.x ] |= y_pix_fill;
        dest_buff->pixels[ y_mod_end  * dest_buff->width + loc.x + width  - 1] |= y_pix_fill;
    

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

        for ( i = loc.x + 1; i < loc.x + width - 1; i++ )
        {
            dest_buff->pixels[ base_y + i] |= y_pix_fill;
        }
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

unsigned char check_buffer_collisions(struct pix_buff *src_buff,
                                     struct pix_buff *detect_buff,
                                     unsigned char x, unsigned char y)
{
    //like blit buff to buff, but && the two buffs overlapping pixels
    unsigned char src_y_mod_start, src_y_pix_start, src_y_mod_end, src_y_pix_end;
    unsigned char dest_y_mod_start, dest_y_pix_start, dest_y_mod_end, dest_y_pix_end;
    //unsigned char y_mod_start, y_pix_start, y_mod_end, y_pix_end;
    unsigned int src_base_y_start, src_base_y_end, src_sw_buff_i = 0;
    unsigned int dest_base_y_start, dest_base_y_end, dest_sw_buff_i = 0;

    // how many byte rows are in the source buffer
    unsigned char buff_mods = (src_buff->height >> 3) + 1;

    unsigned char found = 0;

    //do checks
    if( detect_buff->height < (src_buff->height + y)
        || detect_buff->width < src_buff->width + x)
        return found;



    // determines starting byte row
    dest_y_mod_start = y >> 3;
    //determines bit within starting byte element
    dest_y_pix_start = 1 << (y - (dest_y_mod_start << 3));
    // start index of destination given x and y
    dest_base_y_start = dest_y_mod_start * detect_buff->width;
    // end byte row of destination given x and by and src height
    dest_y_mod_end = (y + src_buff->height) >> 3;
    // where last pixel is in end byte row
    dest_y_pix_end = 1 << ( (y + src_buff->height ) - (dest_y_mod_end << 3));

    //need this?
    dest_base_y_end = dest_y_mod_end * detect_buff->width;

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
               dest_sw_buff_i = (j * detect_buff->width) + x;
               j++;
               src_sw_buff_i = i * src_buff->width;
               i++;
           }

           if(detect_buff->pixels[dest_sw_buff_i] & src_buff->pixels[src_sw_buff_i])
               found = 1;
        }
    }

    else
    {
        src_sw_buff_i = 0;//buff->width;
        dest_sw_buff_i = dest_y_mod_start * detect_buff->width + x;

        //set LCD cursor to the right row
        //gotoXY(x, i);
        //reset x
        temp_x = x;

        // go through the first row in the buffer, it has to be split
        // given the y value
        for(j = src_sw_buff_i; j < src_sw_buff_i + src_buff->width; j++, dest_sw_buff_i++)
        {
            if( detect_buff->pixels[dest_sw_buff_i] & (src_buff->pixels[j] << shift_down) )
                found = 1;
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
            dest_sw_buff_i = k * detect_buff->width + x;
            temp_x = x;

            // go through the first row in the buffer
            for(j = src_sw_buff_i , k = src_sw_buff_i + src_buff->width;
                        j < src_sw_buff_i + src_buff->width; j++, k++, dest_sw_buff_i++)
            {

                if (detect_buff->pixels[dest_sw_buff_i] &
                        ((src_buff->pixels[j] >> 8 -shift_down)
                       |src_buff->pixels[k] << (shift_down)) )
                    found = 1;
            }

            src_sw_buff_i += src_buff->width;
        }

        //blit last row byte
        if(src_y_mod_start != src_y_mod_end)
        {
            //reset to the last row in the buffer
            src_sw_buff_i = ((src_buff->height >> 3 )) * src_buff->width;
            dest_sw_buff_i = ( (src_buff->height + y) >> 3 ) * detect_buff->width + x;
            i = src_y_mod_end;
            //should check if this cursor set is needed
            //gotoXY(x, i);
            temp_x = x;

            // go through the first row in the buffer
            for(j = src_sw_buff_i , k = src_sw_buff_i + src_buff->width;
                        j < src_sw_buff_i + src_buff->width; j++, k++, dest_sw_buff_i++)
            {

                if( detect_buff->pixels[dest_sw_buff_i] & (src_buff->pixels[j] >> 8 -shift_down) )
                    found = 1;
            }
        }
    }
    return found;
}

void setTimeString(b_rtccTime time, char *t_string)
{
//    t_string[0] = 48 + ((time.hour >>  4) & 0xF);
//    t_string[1] = 48 + ((time.hour      ) & 0xF);
    setBase10String(time.hour, t_string);
    t_string[2] = ':';
    setBase10String(time.min, &t_string[3]);
//    t_string[3] = 48 + ((time.min >>  4) & 0xF);
//    t_string[4] = 48 + ((time.min      ) & 0xF);
}


void setBase10String(unsigned char num, char *t_string)
{
    t_string[0] = 48 + ((num >>  4) & 0xF);
    t_string[1] = 48 + ((num) & 0xF);
}

void bcdDecrement(unsigned char *num)
{
    //not wrapping around
    if( (*num &0xF) != 0)
    {
        //don't touch top bits, but subtract from bottom
        *num = (*num & 0xf0) | ((*num-1) & 0xf);
    }
    else
    {
        //shift down and subtract one, don't want carry, shift back
        *num = (((*num >> 4) - 1) & 0xf) << 4;
        *num |= 0x9;
    }
}

void bcdIncrement(unsigned char *num)
{
    //not wrapping around
    if( (*num &0xF) != 9)
    {
        *num = (*num & 0xf0) | ((*num+1) & 0xf);
    }
    else
    {
        //shift down and add one, don't want carry, shift back
        *num = (((*num >> 4) + 1) & 0xf) << 4;
    }
}