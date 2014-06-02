/* 
 * File:   badge_common.h
 * Author: morgan
 *
 * Created on March 28, 2014, 9:28 PM
 */

#ifndef BADGE_COMMON_H
#define	BADGE_COMMON_H
//#include "GenericTypeDefs.h"
//#include "Compiler.h"
//#include "HardwareProfile.h"

//#define byte unsigned char
enum BLIT_STYLE {ZERO_ERASES, ZERO_ALPHA};
struct pix_buff
{
    // not sure how pic handles dynamic memory,
    // so leaving this 1d for now
    unsigned char *pixels;

    unsigned char height, width;
    //BLIT_STYLE blit_method;
};

struct coord
{
    unsigned char x, y;
};

typedef struct coreVars {
   unsigned char mtimerL;
   unsigned char mtimerH;
   unsigned char mtimerH2;
} coreVars ;

typedef struct coreBlock {
   unsigned char block[16];
} coreBlock ;

typedef union coreMemory {
   coreVars cV;
   coreBlock cB;
} coreMemory;
coreMemory core;



void b_strcpy(char* dest, const char* src);
void intTime_to_charTime(char* c_time, unsigned int i_time);

char do_BTM_CapTouch_Left();
char do_BTM_CapTouch_Right();
void set_leds(unsigned char leds);
void putPix_to_buff(struct pix_buff *dest_buff, unsigned char x, unsigned char y);
void fill_buff_area(struct coord loc,
                    unsigned char width,
                    unsigned char height,
                    unsigned char fill,
                    struct pix_buff *dest_buff);
void draw_square(struct pix_buff *dest_buff, struct coord loc,
                unsigned char width, unsigned char height);

unsigned char check_buffer_collisions(struct pix_buff *src_buff,
                                     struct pix_buff *detect_buff,
                                     unsigned char x, unsigned char y);
void getTouchUL();
void getTouchUR();
void LCDClear(void) ;
void LCDInit(void) ;
void LCDLogo();
//void printTouchVals(void);
//void itoa(unsigned char in_num,
//          unsigned char *out_alpha);
#endif	/* BADGE_COMMON_H */

