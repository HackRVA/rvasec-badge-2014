/* 
 * File:   badge14.h
 * Author: morgan
 *
 * Created on March 28, 2014, 8:24 PM
 */

#ifndef BADGE14_H
#define	BADGE14_H
#include "nokia.h"
#include "badge_common.h"
//size of buffers hold possible cap touch vals
#define SIZE 7
#define MAX_SIZE 7
unsigned char btm_size, side_size;

unsigned char bottom_left_pad[SIZE];
unsigned char bottom_right_pad[SIZE];

unsigned char side_left_pad[SIZE];
unsigned char side_right_pad[SIZE];

unsigned char button_pressed, button_cnt, button_used;

// touch states
struct TouchState
{
    char lr_swipe;
    char bt_swipe;

    //lower values are physicallly lefter
    char lower_loc;

    unsigned char lower_slider_left;
    unsigned char lower_slider_right;

    //lower values are...(physically) lower
    char side_loc;

    unsigned char side_slider_left;
    unsigned char side_slider_right;
};

//small queue, it would be nice to make this a linked list, but wtf do I know
struct Queue
{
    //if we want to simulate OO...i guess
    //void *(update)(Queue, void *item);
    void *front;
    void *mid;
    void *back;

};

struct CoOrd
{
    unsigned char x, y;
};

//movement vector
struct Velocity
{
    unsigned char xV, yV;
};

//snake linked list
struct SnakeSeg
{
    struct CoOrd location;
    struct Velocity direction;
    struct SnakeSeg *next;
    
};

//would be nice to make this more easily resizeable
struct TouchQueue
{
    //if this reaches good debounce, consider pressed, look at front for loc
    char bottom_hold_count, side_hold_count;

    // pointer-fy?
    struct TouchState front;
    struct TouchState mid_f;
    struct TouchState mid_b;
    struct TouchState back;
};

//b_rtccTime tm;
//b_rtccDate dt;

struct BadgeState
{
    b_rtccTime tm;
    b_rtccDate dt;

    //create a linked list type structure, should allow use to build some
    //complex sequences with limited global var use
    struct BadgeState *next_state;

    //what function should be handed this state
    void* (*state_handler)(struct BadgeState* b_state);

    //what function should be handed this state
    void* (*next_state_handler)(struct BadgeState* b_state);

    //states may have different uses for the sliders
    void* (*slide_handler)(struct TouchQueue *t_queue);
    //void* (*slide_handler)(struct TouchState *t_state);

    struct TouchQueue slide_states;
   // struct Queue slide_states;

    struct pix_buff buff;

    unsigned char leds;

    unsigned char counter_1;
    unsigned char counter_2;
    unsigned int big_counter;
    unsigned int big_counter_1;
};

struct menu_entry
{
    char *text;
    struct BadgeState *state_entry;// = 0;
    struct menu_page *menu_entry;// = 0;
};

struct menu_page
{
    unsigned char num_entries;
    unsigned char selected;
    struct menu_entry **entries;
    void* (*extra_func)(struct BadgeState *b_state);
};

//returns an initial state sequence
struct BadgeState* Init_Game(void);

//runs the handler in the first state sequence
void Run_Game(struct BadgeState **state);

void initQueue(struct Queue *queue);
void updateQueue(struct Queue queue, void *item );
void initGFX(void);
void setupMenus(void);
void setupStates(void);

void initTouchState(struct TouchState *t_state);
void initBadgeState(struct BadgeState *b_state);


//////////////////////////////
//PERIPH HANDLERS
//////////////////////////////
void* basicSlide(struct TouchQueue *t_queue);
void* autoSlide(struct TouchQueue *t_queue);
void* superSlide(struct TouchQueue *t_queue);
//////////////////////////////
// STATE HANDLERS
//////////////////////////////
void* touchCalibrate(struct BadgeState *b_state);
void* touchCalibrate2(struct BadgeState *b_state);

unsigned char calibrateBottom(struct BadgeState *b_state);
unsigned char calibrateBottom2(struct BadgeState *b_state);

unsigned char calibrateSide(struct BadgeState *b_state);
unsigned char calibrateSide2(struct BadgeState *b_state);

//don't use as a standalone state
void* draw_main_ticker(struct BadgeState *b_state);
void* browse_schedule(struct BadgeState *b_state);

void* welcome(struct BadgeState *b_state);
void* main_menu(struct BadgeState *b_state);
void* menu_maker(struct BadgeState *b_state);
void* manual_contrast(struct BadgeState *b_state);
void* adjust_time(struct BadgeState *b_state);

void* sliderPlay(struct BadgeState *b_state);
void* snake(struct BadgeState *b_state);
void* badgy_bird(struct BadgeState *b_state);
void* tunnelFlight(struct BadgeState *b_state);

void* debugStage(struct BadgeState *b_state);
void printTouchVals(unsigned char btm, unsigned char side);

static byte  bird_idle[] = {
  /* width, height/8 */
  //15,11/8,

  /* rows 0-7 */
  0x38,  /* col =  0 00111000 */
  0xc4,  /* col =  1 11000100 */
  0x84,  /* col =  2 10000100 */
  0x86,  /* col =  3 10000110 */
  0x8a,  /* col =  4 10001010 */
  0x71,  /* col =  5 01110001 */
  0x01,  /* col =  6 00000001 */
  0x8f,  /* col =  7 10001111 */
  0x51,  /* col =  8 01010001 */
  0xa1,  /* col =  9 10100001 */
  0xad,  /* col = 10 10101101 */
  0xa2,  /* col = 11 10100010 */
  0xbc,  /* col = 12 10111100 */
  0xa0,  /* col = 13 10100000 */
  0x40,  /* col = 14 01000000 */

  /* rows 8-15 */
  0x00,  /* col =  0 00000000 */
  0x00,  /* col =  1 00000000 */
  0x01,  /* col =  2 00000001 */
  0x02,  /* col =  3 00000010 */
  0x04,  /* col =  4 00000100 */
  0x04,  /* col =  5 00000100 */
  0x04,  /* col =  6 00000100 */
  0x04,  /* col =  7 00000100 */
  0x05,  /* col =  8 00000101 */
  0x02,  /* col =  9 00000010 */
  0x02,  /* col = 10 00000010 */
  0x02,  /* col = 11 00000010 */
  0x02,  /* col = 12 00000010 */
  0x01,  /* col = 13 00000001 */
  0x00,  /* col = 14 00000000 */

};

static byte bird_flap[] = {
  /* width, height/8 */
  //15,11/8,

  /* rows 0-7 */
  0x38,  /* col =  0 00111000 */
  0xc4,  /* col =  1 11000100 */
  0x44,  /* col =  2 01000100 */
  0x46,  /* col =  3 01000110 */
  0x42,  /* col =  4 01000010 */
  0x81,  /* col =  5 10000001 */
  0x01,  /* col =  6 00000001 */
  0x8f,  /* col =  7 10001111 */
  0x51,  /* col =  8 01010001 */
  0xa1,  /* col =  9 10100001 */
  0xa5,  /* col = 10 10100101 */
  0xa2,  /* col = 11 10100010 */
  0xbc,  /* col = 12 10111100 */
  0xa0,  /* col = 13 10100000 */
  0x40,  /* col = 14 01000000 */

  /* rows 8-15 */
  0x03,  /* col =  0 00000011 */
  0x04,  /* col =  1 00000100 */
  0x04,  /* col =  2 00000100 */
  0x04,  /* col =  3 00000100 */
  0x04,  /* col =  4 00000100 */
  0x03,  /* col =  5 00000011 */
  0x04,  /* col =  6 00000100 */
  0x04,  /* col =  7 00000100 */
  0x05,  /* col =  8 00000101 */
  0x02,  /* col =  9 00000010 */
  0x02,  /* col = 10 00000010 */
  0x02,  /* col = 11 00000010 */
  0x02,  /* col = 12 00000010 */
  0x01,  /* col = 13 00000001 */
  0x00,  /* col = 14 00000000 */

};


#endif	/* BADGE14_H */

