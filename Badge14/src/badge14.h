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
#include "gfx_assets.h"

//size of buffers hold possible cap touch vals
#define SIZE 7
#define MAX_SIZE 7
unsigned char btm_size, side_size;

unsigned char bottom_left_pad[SIZE];
unsigned char bottom_right_pad[SIZE];

unsigned char side_left_pad[SIZE];
unsigned char side_right_pad[SIZE];

unsigned char button_pressed, button_cnt, button_used;

struct image screen_images[NUM_IMAGE_ASSETS];

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
void* image_viewer(struct BadgeState *b_state);


void* debugStage(struct BadgeState *b_state);
void printTouchVals(unsigned char btm, unsigned char side);

#endif	/* BADGE14_H */

