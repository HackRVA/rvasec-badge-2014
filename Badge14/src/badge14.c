#include "badge_common.h"
#include "badge14.h"
#include "schedule.h"
//const char hextab[]={"0123456789ABCDEF"};
extern char *hextab;
extern char gContrast;
unsigned char pix[504] = {0};
//dont need both in prod, debugging now
unsigned char pix2[504] = {0};

struct pix_buff main_buff, bird_idle_buff;

unsigned char max_lower_left, max_lower_right,
        max_side_left, max_side_right;

void initTouchState(struct TouchState *t_state)
{
    t_state->lr_swipe = 0;
    t_state->bt_swipe = 0;
    t_state->lower_loc = 0;
    t_state->lower_slider_left = 0;
    t_state->lower_slider_right = 0;

    t_state->side_loc = 0;
    t_state->side_slider_left = 0;
    t_state->side_slider_right = 0;
}

void shiftTouchQueue(struct TouchQueue *queue)
{
    queue->back = queue->mid_b;
    queue->mid_b = queue->mid_f;
    queue->mid_f = queue->front;
    
    initTouchState(&queue->front);
}

void initBadgeState(struct BadgeState *b_state)
{
    //is zero still null on 32bit MCU?
    b_state->next_state = 0;
    b_state->state_handler = 0;
    b_state->slide_handler = autoSlide;

    //set touch to zero
    initTouchState(&b_state->slide_states.front);
    initTouchState(&b_state->slide_states.mid_f);
    initTouchState(&b_state->slide_states.mid_b);
    initTouchState(&b_state->slide_states.back);

    b_state->leds = 0;
    b_state->counter_1 = 0;
    b_state->counter_2 = 0;
    b_state->big_counter = 0;
    b_state->big_counter_1 = 0;
}

//initialize all the things
struct BadgeState start_state;

struct menu_entry *main_entries[3], games, schedule, settings, sketch, adventure;

//extra element for back button
struct menu_entry *game_entries[6], snake_e, bird_e, pong_e, more_games_e;
struct menu_entry *more_game_entries[2], images_e;

struct menu_entry *settings_entries[6], backlight, contrast, set_time, speaker,
                    more_settings_e;
struct menu_entry *more_settings_entries[2], screen_saver_e;
struct menu_entry back_to_main, back_to_games, back_to_settings;

struct menu_page *current_menu, main_page, games_page, settings_page, 
                  schedule_page, more_settings_page, more_games_page;

//main menu texts
const char game_txt[] = "DIVERSIONS",
           schedule_txt[] = "SCHEDULE",
           settings_txt[] = "SETTINGS";

//games menu texts
const char snake_txt[] = "SNAKE",
           adventure_txt[] = "ADVENTURE",
           sketch_txt[] = "SKETCH",
           bird_txt[] = "BADGY BIRD",
           pong_txt[] = "PONG",
           images_txt[] = "IMAGES";

//settings menu text
const char set_backlight[] = "BACKLIGHT",
           adjust_contrast[] = "CONTRAST",
           enable_speaker[] = "SPEAKER",
           set_time_txt[] = "SET TIME";

//
const char screen_saver_txt[] = "SCREEN SAVER" ,
           go_back[] = "<-[BACK]",
           more_txt[] = "[MORE]";

//main_page.entries;
struct BadgeState snake_state, sketch_state, manual_contrast_state,
                    bird_state, schedule_browse_state, set_time_state,
                    image_viewer_state, screen_saver_setup_state;

void initGFX(void)
{
    unsigned char i = 0;
    
    main_buff.pixels = pix2;
    main_buff.height = 48;
    main_buff.width = 84;

    bird_idle_buff.pixels = bird_idle;
    bird_idle_buff.height = 11;
    bird_idle_buff.width = 15;

    //the doge
    screen_images[i].name = doge_txt;
    screen_images[i].buff.pixels = doge;
    screen_images[i].buff.height = 48;
    screen_images[i].buff.width = 84;
    
    i++;

    //grumpy cat
    screen_images[i].name = grump_txt;
    screen_images[i].buff.pixels = grump;
    screen_images[i].buff.height = 48;
    screen_images[i].buff.width = 84;

    i++;

    //grumpy cat
    screen_images[i].name = stache_txt;
    screen_images[i].buff.pixels = stache;
    screen_images[i].buff.height = 48;
    screen_images[i].buff.width = 84;
}

void setupMenus(void)
{

    current_menu = &main_page;

    //-----------------------
    // setup MAIN
    main_page.num_entries = 3;
    main_page.selected = 0;
    main_page.entries = main_entries;
    main_page.extra_func = draw_main_ticker;
    
    main_entries[0] = &games;
        games.text = game_txt;
        games.menu_entry = &games_page;
        games.state_entry = 0;

    main_entries[1] = &schedule;
        schedule.text = schedule_txt;
        schedule.menu_entry = 0;
        schedule.state_entry = &schedule_browse_state;

    main_entries[2] = &settings;
        settings.text = settings_txt;
        settings.menu_entry = &settings_page;
        settings.state_entry = 0;
        
    //-----------------------
    // setup GAMES
    games_page.num_entries = 6;
    games_page.selected = 0;
    games_page.entries = game_entries;

    game_entries[0] = &snake_e;
        snake_e.text = snake_txt;
        snake_e.menu_entry = 0;
        snake_e.state_entry = &snake_state;

    game_entries[1] = &bird_e;
        bird_e.text = bird_txt;
        bird_e.menu_entry = 0;
        bird_e.state_entry = &bird_state;

    game_entries[2] = &pong_e;
        pong_e.text = pong_txt;
        pong_e.menu_entry = 0;
        pong_e.state_entry = 0;

    game_entries[3] = &sketch;
        sketch.text = sketch_txt;
        sketch.menu_entry = 0;
        sketch.state_entry = &sketch_state;

    game_entries[4] = &more_games_e;
        more_games_e.text = more_txt;
        more_games_e.menu_entry = &more_games_page;
        more_games_e.state_entry = 0;

    game_entries[5] = &back_to_main;

    //-----------------------
    // setup MORE GAMES
    more_games_page.num_entries = 2;
    more_games_page.selected = 0;
    more_games_page.entries = more_game_entries;

    more_game_entries[0] = &images_e;
        images_e.text = images_txt;
        images_e.menu_entry = 0;
        images_e.state_entry = &image_viewer_state;

    more_game_entries[1] = &back_to_games;
        back_to_games.text = go_back;
        back_to_games.menu_entry = &games_page;
        back_to_games.state_entry = 0;
        

    //-----------------------
    // setup SCHEDULE
    schedule_page.num_entries = 0;
    schedule_page.selected = 0;
    schedule_page.entries = 0;
    schedule_page.extra_func = draw_main_ticker;


    //-----------------------
    // setup SETTINGS
    settings_page.num_entries = 6;
    settings_page.selected = 0;
    settings_page.entries = settings_entries;

    settings_entries[0] = &backlight;
        backlight.text = set_backlight;
        backlight.menu_entry = 0;
        backlight.state_entry = 0;

    settings_entries[1] = &contrast;
        contrast.text = adjust_contrast;
        contrast.menu_entry = 0;
        contrast.state_entry = &manual_contrast_state;

    settings_entries[2] = &speaker;
        speaker.text = enable_speaker;
        speaker.menu_entry = 0;
        speaker.state_entry = 0;

    settings_entries[3] = &set_time;
        set_time.text = set_time_txt;
        set_time.menu_entry = 0;
        set_time.state_entry = &set_time_state;

    settings_entries[4] = &more_settings_e;
        more_settings_e.text = more_txt;
        more_settings_e.menu_entry = &more_settings_page;
        more_settings_e.state_entry = 0;

    settings_entries[5] = &back_to_main;
        back_to_main.text = go_back;
        back_to_main.menu_entry = &main_page;
        back_to_main.state_entry = 0;

    //-----------------------
    // setup MORE SETTINGS
    more_settings_page.num_entries = 2;
    more_settings_page.selected = 0;
    more_settings_page.entries = more_settings_entries;

    more_settings_entries[0] = &screen_saver_e;
        screen_saver_e.text = screen_saver_txt;
        screen_saver_e.menu_entry = 0;
        screen_saver_e.state_entry = &screen_saver_setup_state;

    more_settings_entries[1] = &back_to_settings;
        back_to_settings.text = go_back;
        back_to_settings.menu_entry = &settings_page;
        back_to_settings.state_entry = 0;

}

void setupStates(void)
{
    initBadgeState(&start_state);
        start_state.next_state = &start_state;
        start_state.state_handler = touchCalibrate;//main_menu;//tunnelFlight; // //
        start_state.slide_handler = autoSlide;
        
    initBadgeState(&sketch_state);
        sketch_state.state_handler = sliderPlay;
        sketch_state.next_state = &sketch_state;

    initBadgeState(&manual_contrast_state);
        manual_contrast_state.state_handler = manual_contrast;
        manual_contrast_state.next_state = &manual_contrast_state;

    initBadgeState(&snake_state);
        snake_state.state_handler = snake;
        snake_state.next_state = &snake_state;

    initBadgeState(&bird_state);
        bird_state.state_handler = badgy_bird;
        bird_state.next_state = &bird_state;
        bird_state.slide_handler = basicSlide;

    initBadgeState(&schedule_browse_state);
        schedule_browse_state.state_handler = browse_schedule;
        schedule_browse_state.next_state = &schedule_browse_state;

    initBadgeState(&set_time_state);
        set_time_state.state_handler = adjust_time;
        set_time_state.next_state = &set_time_state;

    initBadgeState(&image_viewer_state);
        image_viewer_state.state_handler = image_viewer;
        image_viewer_state.next_state = &image_viewer_state;

    initBadgeState(&screen_saver_setup_state);
        screen_saver_setup_state.state_handler = setup_screen_saver;
        screen_saver_setup_state.next_state = &screen_saver_setup_state;
}

struct BadgeState* Init_Game(void)
{
//    b_rtccTime tm;
//    b_rtccDate dt;

    LATBbits.LATB7 = 1;
    button_pressed = button_cnt = button_used = 0;
    btm_size = side_size = 0;

    LCDInit();
    LCDClear();
    initGFX();

    setupStates();
    setupMenus();
    initConferenceEvents();

    start_state.tm.l=0;
    start_state.tm.sec=0x00;
    start_state.tm.min=0x00;
    start_state.tm.hour=0x08;

    start_state.dt.wday=4;
    start_state.dt.mday=0x05;
    start_state.dt.mon=0x06;
    start_state.dt.year=0x14;

    setupRTCC();
    RtccSetTimeDate(start_state.tm.l, start_state.dt.l);
    return (struct BadgeState *)&start_state;
    //return &bird_state;
}

//update clock every T_UPDATE_DELTA iterations
#define T_UPDATE_DELTA 20000
void Run_Game(struct BadgeState **state)
{
    static unsigned int cnt = 0;
    *state = (*state)->next_state;

    //don't need to update too often
    if( cnt++ == T_UPDATE_DELTA)
    {
        cnt = 0;
        (*state)->tm.l = get_time();
    }

    //run the state
    (*state)->state_handler(*state);
}

//////////////////////////////
//PERIPH HANDLERS
//////////////////////////////
char G_lower_slider_left;
char G_lower_slider_right;

char G_side_slider_right;
char G_side_slider_left;

//how many ticks before taking another sample
#define SAMPLE_RATE 3500
unsigned int sample_counter;

void* basicSlide(struct TouchQueue *t_queue)
{
    //only check and set values if sampling
    if(sample_counter < SAMPLE_RATE)
    {
        //make sure no change happens
        t_queue->front.lr_swipe = 0;
        sample_counter++;
        return;
    }
    sample_counter = 0;

    //remove push old values back in queue, re-init front
    shiftTouchQueue(t_queue);
    
    struct TouchState *t_state = &t_queue->front;

    //assign the touch values
    t_state->lower_slider_left = G_lower_slider_left;
    t_state->lower_slider_right = G_lower_slider_right;

    //set to -1        
    t_state->lower_loc =  -1;
    t_state->side_loc = -1;

    char left_sum = t_queue->front.lower_slider_left
                    + t_queue->mid_f.lower_slider_left
                    + t_queue->mid_b.lower_slider_left
                    + t_queue->back.lower_slider_left;

   if (left_sum != t_queue->mid_f.lower_loc)
    {
        t_queue->bottom_hold_count++;
    }
   else
       t_queue->bottom_hold_count = 0;

    t_queue->front.lower_loc = left_sum;
    
    t_state->side_slider_left = 0;
    t_state->side_slider_right = 0;
}

void* autoSlide(struct TouchQueue *t_queue)
{
    //only check and set values if sampling
    if(sample_counter < SAMPLE_RATE)
    {
        //make sure no change happens
        t_queue->front.lr_swipe = 0;
        t_queue->front.bt_swipe = 0;
        sample_counter++;
        return;
    }
    sample_counter = 0;

    //remove push old values back in queue, re-init front
    shiftTouchQueue(t_queue);

    struct TouchState *t_state = &t_queue->front;
    t_state->lower_slider_left = G_lower_slider_left;
    t_state->lower_slider_right = G_lower_slider_right;
    t_state->side_slider_left = G_side_slider_left;
    t_state->side_slider_right = G_side_slider_right;

/////////////////////////////////
//----Bottom slider
/////////////////////////////////
    //set to -1                            vv this almost works
    t_state->lower_loc =  -1; //t_state->lower_slider_left - t_state->lower_slider_right;

    for(t_state->lower_loc = 1;
            t_state->lower_loc < btm_size
            && (G_lower_slider_right != bottom_right_pad[t_state->lower_loc]
            || G_lower_slider_left != bottom_left_pad[t_state->lower_loc]);
                t_state->lower_loc++);

    //hard code walues, need to have way to calibrate
    if (t_state->lower_loc == btm_size)
            t_state->lower_loc = -1;

    //if positive then swiping right, if negative then swiping right
    // magnitude indicates the amount of change (speed?)
    // don't bother updating if there has been no touch!
    if (t_queue->front.lower_loc != -1
        && t_queue->mid_f.lower_loc != -1
        && t_queue->mid_b.lower_loc != -1
        && t_queue->back.lower_loc != -1 )
    {
        //front two versus back two
        //t_queue->front.lr_swipe = ((t_queue->front.lower_loc + t_queue->mid_f.lower_loc)/2) - (( t_queue->mid_b.lower_loc + t_queue->back.lower_loc)/2) ;
        //new touch sense versus previous three
        t_queue->front.lr_swipe = ((t_queue->front.lower_loc)) - ((( t_queue->mid_f.lower_loc + t_queue->mid_b.lower_loc + t_queue->back.lower_loc)/3));

        char diff = (t_queue->front.lower_loc - t_queue->mid_f.lower_loc)
                    + (t_queue->mid_b.lower_loc - t_queue->back.lower_loc) ;
        //is button being held
       if (!diff)
            //== t_queue->mid_b.lower_loc)
            //== t_queue->back.lower_loc )
        {
            t_queue->bottom_hold_count++;
        }
       else
           t_queue->bottom_hold_count = 0;
    }
    else
        t_queue->front.lr_swipe = 0;

/////////////////////////////////
//----Side slider
/////////////////////////////////
    //set to -1                           
    t_state->side_loc =  -1; 

    for(t_state->side_loc = 1;
            t_state->side_loc < side_size
            && (G_side_slider_right != side_right_pad[t_state->side_loc]
            || G_side_slider_left != side_left_pad[t_state->side_loc]);
            t_state->side_loc++);

    //hard code walues, need to have way to calibrate
    if (t_state->side_loc == side_size)
            t_state->side_loc = -1;

    //if positive then swiping right, if negative then swiping right
    // magnitude indicates the amount of change (speed?)
    // don't bother updating if there has been no touch!
    if (t_queue->front.side_loc != -1
        && t_queue->mid_f.side_loc != -1
        && t_queue->mid_b.side_loc != -1
        && t_queue->back.side_loc != -1 )
    {
        //front two versus back two
        //t_queue->front.lr_swipe = ((t_queue->front.lower_loc + t_queue->mid_f.lower_loc)/2) - (( t_queue->mid_b.lower_loc + t_queue->back.lower_loc)/2) ;
        //new touch sense versus previous three
        t_queue->front.bt_swipe = ((t_queue->front.side_loc)) - ((( t_queue->mid_f.side_loc + t_queue->mid_b.side_loc + t_queue->back.side_loc)/3));

        char diff = (t_queue->front.side_loc - t_queue->mid_f.side_loc)
                    + (t_queue->mid_b.side_loc - t_queue->back.side_loc) ;
        //is button being held
       if (!diff)
            //== t_queue->mid_b.lower_loc)
            //== t_queue->back.lower_loc )
        {
            t_queue->side_hold_count++;
        }
       else
           t_queue->side_hold_count = 0;
    }
    else
        t_queue->front.bt_swipe = 0;
}

void* superSlide(struct TouchQueue *t_queue)
{
    //only check and set values if sampling
    if(sample_counter < SAMPLE_RATE)
    {
        //make sure no change happens
        t_queue->front.lr_swipe = 0;
        t_queue->front.bt_swipe = 0;
        sample_counter++;
        return;
    }
    sample_counter = 0;

    //remove push old values back in queue, re-init front
    shiftTouchQueue(t_queue);

    struct TouchState *t_state = &t_queue->front;
    t_state->lower_slider_left = G_lower_slider_left;
    t_state->lower_slider_right = G_lower_slider_right;
    t_state->side_slider_left = G_side_slider_left;
    t_state->side_slider_right = G_side_slider_right;

/////////////////////////////////
//----Bottom slider
/////////////////////////////////
    //set to -1                            vv this almost works
    t_state->lower_loc =  -1; //t_state->lower_slider_left - t_state->lower_slider_right;
//
//    for(t_state->lower_loc = 1;
//            t_state->lower_loc < btm_size
//            && (G_lower_slider_right != bottom_right_pad[t_state->lower_loc]
//            || G_lower_slider_left != bottom_left_pad[t_state->lower_loc]);
//                t_state->lower_loc++);
    //left ratio
    //t_state->lower_loc =

    //hard code walues, need to have way to calibrate
    if (t_state->lower_loc == btm_size)
            t_state->lower_loc = -1;

    //if positive then swiping right, if negative then swiping right
    // magnitude indicates the amount of change (speed?)
    // don't bother updating if there has been no touch!
    if (t_queue->front.lower_loc != -1
        && t_queue->mid_f.lower_loc != -1
        && t_queue->mid_b.lower_loc != -1
        && t_queue->back.lower_loc != -1 )
    {
        //front two versus back two
        //t_queue->front.lr_swipe = ((t_queue->front.lower_loc + t_queue->mid_f.lower_loc)/2) - (( t_queue->mid_b.lower_loc + t_queue->back.lower_loc)/2) ;
        //new touch sense versus previous three
        t_queue->front.lr_swipe = ((t_queue->front.lower_loc)) - ((( t_queue->mid_f.lower_loc + t_queue->mid_b.lower_loc + t_queue->back.lower_loc)/3));

        char diff = (t_queue->front.lower_loc - t_queue->mid_f.lower_loc)
                    + (t_queue->mid_b.lower_loc - t_queue->back.lower_loc) ;
        //is button being held
       if (!diff)
            //== t_queue->mid_b.lower_loc)
            //== t_queue->back.lower_loc )
        {
            t_queue->bottom_hold_count++;
        }
       else
           t_queue->bottom_hold_count = 0;
    }
    else
        t_queue->front.lr_swipe = 0;

/////////////////////////////////
//----Side slider
/////////////////////////////////
    //set to -1
    t_state->side_loc =  -1;

    for(t_state->side_loc = 1;
            t_state->side_loc < side_size
            && (G_side_slider_right != side_right_pad[t_state->side_loc]
            || G_side_slider_left != side_left_pad[t_state->side_loc]);
            t_state->side_loc++);

    //hard code walues, need to have way to calibrate
    if (t_state->side_loc == side_size)
            t_state->side_loc = -1;

    //if positive then swiping right, if negative then swiping right
    // magnitude indicates the amount of change (speed?)
    // don't bother updating if there has been no touch!
    if (t_queue->front.side_loc != -1
        && t_queue->mid_f.side_loc != -1
        && t_queue->mid_b.side_loc != -1
        && t_queue->back.side_loc != -1 )
    {
        //front two versus back two
        //t_queue->front.lr_swipe = ((t_queue->front.lower_loc + t_queue->mid_f.lower_loc)/2) - (( t_queue->mid_b.lower_loc + t_queue->back.lower_loc)/2) ;
        //new touch sense versus previous three
        t_queue->front.bt_swipe = ((t_queue->front.side_loc)) - ((( t_queue->mid_f.side_loc + t_queue->mid_b.side_loc + t_queue->back.side_loc)/3));

        char diff = (t_queue->front.side_loc - t_queue->mid_f.side_loc)
                    + (t_queue->mid_b.side_loc - t_queue->back.side_loc) ;
        //is button being held
       if (!diff)
            //== t_queue->mid_b.lower_loc)
            //== t_queue->back.lower_loc )
        {
            t_queue->side_hold_count++;
        }
       else
           t_queue->side_hold_count = 0;
    }
    else
        t_queue->front.bt_swipe = 0;
}

//////////////////////////////
// STATE HANDLERS
//////////////////////////////
void* touchCalibrate2(struct BadgeState *b_state)
{  
    if(!b_state->big_counter)
    {
        b_state->big_counter += calibrateBottom2(b_state);
        //this prevents holding the button from incrementing more than
        //once
        if(button_pressed == 5 )
        {
            //button_pressed = 0;
            b_state->counter_1 = 0;
            b_state->counter_2 = 0;
            b_state->big_counter = 1;
        }
    }
    else if(b_state->big_counter == 1)
    {
        if(!++b_state->counter_1)
        {
            if(!++b_state->counter_2)
                b_state->big_counter = 2;

            LCDClear();
            unsigned char str[btm_size*5 + 1];//*str = "DONE!";
            unsigned char j, k;
            for(j = 0; j < btm_size; j++)
            {
                k = 5*j;
                str[k] = '[';
                str[k+1] = 48 +  (unsigned char)bottom_left_pad[j];
                str[k+2] = ',';
                str[k+3] = 48 +  (unsigned char)bottom_right_pad[j];
                str[k+4] = ']';
            }
            str[k+5] = 0;
            LCDString(str);
        }
        
        if(button_pressed == 5 )
        {
            //button_pressed = 0;
            b_state->big_counter = 2;
            b_state->counter_2 = 0;
            b_state->counter_1 = 0;
        }

    }
    else if (b_state->big_counter == 2)
    {
        b_state->big_counter += calibrateSide2(b_state);
        if(button_pressed == 5 )
        {
           //button_pressed = 0;
           b_state->counter_1 = 0;
           b_state->counter_2 = 0;
           b_state->big_counter = 3;
        }
    }
    else if (b_state->big_counter == 3)
    {
        if(!++b_state->counter_1)
        {
            if(!++b_state->counter_2)
                b_state->big_counter = 4;


            LCDClear();
            unsigned char str[side_size*5 + 1];//*str = "DONE!";
            unsigned char j, k;
            for(j = 0; j < side_size; j++)
            {
                k = 5*j;
                str[k] = '(';
                str[k+1] = 48 +  (unsigned char)side_left_pad[j];
                str[k+2] = ',';
                str[k+3] = 48 +  (unsigned char)side_right_pad[j];
                str[k+4] = ')';
            }
            str[k+5 ] = 0;
            LCDString(str);
        }
        if(button_pressed == 5 )
            b_state->big_counter = 4;
    }
    else
    {
        LCDClear();
        LCDLogo();

        b_state->big_counter
            = b_state->counter_1
            = b_state->counter_2 = 0;
        b_state->state_handler = menu_maker;//main_menu;//welcome;
    }
}

//max_lower_btm, max_lower_top,
//        max_side_left, max_side_right;
unsigned char calibrateBottom2(struct BadgeState *b_state)
{
    //only sample occasionally
    if(!b_state->counter_1++)
    {
        max_lower_left = G_lower_slider_left;
        max_lower_right = G_lower_slider_right;
        // check if buffered filled...should also have time out
//        if(btm_size == MAX_SIZE)
//        {
//            b_state->counter_1 = 0;
//            b_state->counter_2 = 0;
//            return 1;
//        }
//        else
//        {
//            //first, search values and make sure it's not duplicate
//            //  start search from beginning, stop where left off
//            unsigned char i, j, k, found = 0;
//            for(i = 0; i < btm_size && !found; i++)
//            {
//                //check if at least one doesn't match
//                if (bottom_left_pad[i] == G_lower_slider_left
//                   && bottom_right_pad[i] == G_lower_slider_right)
//                {
//                    found = 1;
//                }
//            }
//
//            //this sample is original and not 00
//            if(!found && G_lower_slider_left && G_lower_slider_right)
//            {
//                bottom_left_pad[btm_size] = G_lower_slider_left;
//                bottom_right_pad[btm_size] = G_lower_slider_right;
//                btm_size++;
//            }
            LCDClear();
            char *out = "  Calibrate\n   Bottom:\n";
            LCDString(out);
            printTouchVals(1, 0);
//        }

    }
    return 0;
}

unsigned char calibrateSide2(struct BadgeState *b_state)
{
    //only sample occasionally
    if(!b_state->counter_1++)
    {
        max_side_left = G_side_slider_left;
        max_side_right = G_side_slider_right;
        // check if buffered filled...should also have time out
//        if(side_size == MAX_SIZE )
//        {
//            b_state->counter_1 = 0;
//            b_state->counter_2 = 0;
//            return 1;
//        }
//        else
//        {
//            //first, search values and make sure it's not duplicate
//            unsigned char i, j, k, found = 0;
//            for(i = 0; i < side_size && !found; i++)
//            {
//                //check if at least one doesn't match
//                if (side_left_pad[i] == G_side_slider_left
//                   && side_right_pad[i] == G_side_slider_right)
//                {
//                    found = 1;
//                }
//            }
//
//            //this sample is original
//            if(!found && G_side_slider_left && G_side_slider_right)
//            {
//                side_left_pad[side_size] = G_side_slider_left;
//                side_right_pad[side_size] = G_side_slider_right;
//                side_size++;
//            }

            LCDClear();
            char *out = "  Calibrate\n    Side:\n";
            LCDString(out);
            printTouchVals(0,1);
    }
    return 0;
}


void* touchCalibrate(struct BadgeState *b_state)
{  
    if(!b_state->big_counter)
    {
        b_state->big_counter += calibrateBottom(b_state);
        //this prevents holding the button from incrementing more than
        //once
        if(button_pressed == 5 )
        {
            //button_pressed = 0;
            b_state->counter_1 = 0;
            b_state->counter_2 = 0;
            b_state->big_counter = 1;
        }
    }
    else if(b_state->big_counter == 1)
    {
        if(!++b_state->counter_1)
        {
            if(!++b_state->counter_2)
                b_state->big_counter = 2;

            LCDClear();
            unsigned char str[btm_size*5 + 1];//*str = "DONE!";
            unsigned char j, k;
            for(j = 0; j < btm_size; j++)
            {
                k = 5*j;
                str[k] = '[';
                str[k+1] = 48 +  (unsigned char)bottom_left_pad[j];
                str[k+2] = ',';
                str[k+3] = 48 +  (unsigned char)bottom_right_pad[j];
                str[k+4] = ']';
            }
            str[k+5] = 0;
            LCDString(str);
        }
        
        if(button_pressed == 5 )
        {
            //button_pressed = 0;
            b_state->big_counter = 2;
            b_state->counter_2 = 0;
            b_state->counter_1 = 0;
        }

    }
    else if (b_state->big_counter == 2)
    {
        b_state->big_counter += calibrateSide(b_state);
        if(button_pressed == 5 )
        {
           //button_pressed = 0;
           b_state->counter_1 = 0;
           b_state->counter_2 = 0;
           b_state->big_counter = 3;
        }
    }
    else if (b_state->big_counter == 3)
    {
        if(!++b_state->counter_1)
        {
            if(!++b_state->counter_2)
                b_state->big_counter = 4;


            LCDClear();
            unsigned char str[side_size*5 + 1];//*str = "DONE!";
            unsigned char j, k;
            for(j = 0; j < side_size; j++)
            {
                k = 5*j;
                str[k] = '(';
                str[k+1] = 48 +  (unsigned char)side_left_pad[j];
                str[k+2] = ',';
                str[k+3] = 48 +  (unsigned char)side_right_pad[j];
                str[k+4] = ')';
            }
            str[k+5 ] = 0;
            LCDString(str);
        }
        if(button_pressed == 5 )
            b_state->big_counter = 4;
    }
    else
    {
//        LCDClear();
//        LCDLogo();

        b_state->big_counter
            = b_state->counter_1
            = b_state->counter_2 = 0;
        b_state->state_handler = menu_maker;//main_menu;//welcome;
    }
}

unsigned char calibrateBottom(struct BadgeState *b_state)
{
    //only sample occasionally
    if(!b_state->counter_1++)
    {
        // check if buffered filled...should also have time out
        if(btm_size == MAX_SIZE)
        {
            b_state->counter_1 = 0;
            b_state->counter_2 = 0;
            return 1;
        }
        else
        {
            //first, search values and make sure it's not duplicate
            //  start search from beginning, stop where left off
            unsigned char i, j, k, found = 0;
            for(i = 0; i < btm_size && !found; i++)
            {
                //check if at least one doesn't match
                if (bottom_left_pad[i] == G_lower_slider_left
                   && bottom_right_pad[i] == G_lower_slider_right)
                {
                    found = 1;
                }
            }

            //this sample is original and not 00
            if(!found && G_lower_slider_left && G_lower_slider_right)
            {
                bottom_left_pad[btm_size] = G_lower_slider_left;
                bottom_right_pad[btm_size] = G_lower_slider_right;
                btm_size++;
            }
            LCDClear();
            char *out = "  Calibrate\n   Bottom:\n";
            LCDString(out);
            printTouchVals(1, 0);
        }

    }
    return 0;
}

unsigned char calibrateSide(struct BadgeState *b_state)
{
    //only sample occasionally
    if(!b_state->counter_1++)
    {
        // check if buffered filled...should also have time out
        if(side_size == MAX_SIZE )
        {
            b_state->counter_1 = 0;
            b_state->counter_2 = 0;
            return 1;
        }
        else
        {
            //first, search values and make sure it's not duplicate
            unsigned char i, j, k, found = 0;
            for(i = 0; i < side_size && !found; i++)
            {
                //check if at least one doesn't match
                if (side_left_pad[i] == G_side_slider_left
                   && side_right_pad[i] == G_side_slider_right)
                {
                    found = 1;
                }
            }

            //this sample is original
            if(!found && G_side_slider_left && G_side_slider_right)
            {
                side_left_pad[side_size] = G_side_slider_left;
                side_right_pad[side_size] = G_side_slider_right;
                side_size++;
            }

            LCDClear();
            char *out = "  Calibrate\n    Side:\n";
            LCDString(out);
            printTouchVals(0,1);
        }
    }
    return 0;
}

void* welcome(struct BadgeState *b_state)
{

    if(!++b_state->counter_1)
        b_state->big_counter++;

    if(b_state->big_counter < 20)
        b_state->leds = 0x18;
    
    else if (b_state->big_counter < 40)
        b_state->leds = 0x3C;

    else if (b_state->big_counter < 60)
        b_state->leds = 0x7E;

    else if (b_state->big_counter < 80)
        b_state->leds = 0xFF;

    else
    {
        if(b_state->counter_2 == 15)
        {
            LCDClear();
            LCD_RVASec_Logo();
        }
        
        b_state->big_counter = 0;
        b_state->counter_2++;
        
    }
    set_leds(b_state->leds);

    if(b_state->counter_2 == 30 || button_pressed == 250)
    {
        //LCDLogo();
        LCDClear();
        LCDInit();
        b_state->big_counter = 0;
        b_state->counter_2 = 0;
        b_state->counter_1 = 0;
        b_state->state_handler = sliderPlay;

    }
    return 0;
}

void* tunnelFlight(struct BadgeState *b_state)
{
    static struct pix_buff buff;
    static struct coord loc;
                    loc.x = 0;
                    loc.y = 0;

    if(b_state->counter_1 == 0)
    {
        unsigned char pix_t[9] = { 0xFF,
                                 0x01,
                                 0xFF,
                                 0xFF,
                                 0x00,
                                 0xFF,
                                 0xFF,
                                 0x80,
                                 0xFF};
        b_state->counter_1++;
        LCDClear();
        //LCDLogo();
        buff.height = 48;
        buff.width = 84;

        buff.pixels = pix;
//        draw_square(&buff, loc, 83, 40);
//        draw_square(&buff, loc, 40, 40);
//        draw_square(&buff, loc, 32, 32);
//        draw_square(&buff, loc, 24, 24);
//        draw_square(&buff, loc, 16, 16);
//        loc.x = 1;
//        draw_square(&buff, loc, 8, 8);
        loc.x = 1;
        loc.y = 0;
        unsigned char height = 1;
        //bottom part of pipe
        for(loc.x = 1; loc.x < 70; loc.x += 3, height++)
        {
            fill_buff_area(loc, 8, height,
                                0xff, &main_buff);
        }
        //unsigned char base = 50;

        // LCDLogo();
        //             x,  y,  w,  h
        //invertBuffArea(1, 1, 81, 6, &buff);
        //invertBuffArea(1, 8, 81, 6, &buff);
        invertBuffArea(1, 16, 81, 6, &buff);
        //invertBuffArea(1, 22, 81, 6, &buff);
        blitBuff_opt(&main_buff, 0, 0);


        //blitBuff(&buff, 9, 11);
    }
                    
//    if(++b_state->big_counter > 15000)
//    {
//        b_state->big_counter = 0;
//        set_leds(b_state->counter_2++);
//        //unsigned char dim = (b_state->counter_2<<3) % 48;
//        unsigned char t_x, t_y;
//        //clear buff;
//        fill_buff(&buff, 0x00);
//
//        if (!(b_state->counter_2 % 2))
//        {
//            for(t_x = 2, t_y = 2;
//                    t_x < 84 && t_y < 48;
//                        t_x += 8, t_y += 6)
//            {
//                loc.x = 42 - (t_x>>1);
//                loc.y = 24 - (t_y>>1);
//                draw_square(&buff, loc, t_x, t_y);
//            }
//        }
//        else
//        {
//            for(t_x = 5, t_y = 5;
//                    t_x < 84 && t_y < 48;
//                        t_x += 8, t_y += 6)
//            {
//                loc.x = 42 - (t_x>>1);
//                loc.y = 24 - (t_y>>1);
//                draw_square(&buff, loc, t_x, t_y);
//            }
//        }
//
//        blitBuff(&buff, 0, 0);
//
//    }
}

void* menu_maker(struct BadgeState *b_state)
{
    //static struct pix_buff buff;
    static struct coord loc;
                    loc.x = 40;
                    loc.y = 20;
    static unsigned char leds = 0xff, redraw = 0;

    b_state->slide_handler(&b_state->slide_states);

    char lr_swipe = b_state->slide_states.front.lr_swipe;
    char bt_swipe = b_state->slide_states.front.bt_swipe;

    if(bt_swipe < 0
            && (current_menu->selected < (current_menu->num_entries - 1)))
    {
        current_menu->selected += 1;
        redraw = 1;
    }

    if(bt_swipe > 0 && (current_menu->selected > 0))
    {
        current_menu->selected -= 1;
        redraw = 1;
    }
    
    set_leds(current_menu->selected + 1);

    if ( button_pressed == 250 && current_menu->entries)
    {
        LCDClear();
        fill_buff(&main_buff, 0x00);
        redraw = 1;
        button_pressed++;

        if( current_menu->entries[current_menu->selected]->menu_entry )
        {
            current_menu
                    = current_menu->entries[current_menu->selected]->menu_entry;
            return;
        }
        else if ( current_menu->entries[current_menu->selected]->state_entry )
        {
            b_state->next_state
                    = current_menu->entries[current_menu->selected]->state_entry;
            return;
        }
    }

    if(b_state->counter_1 == 0 || redraw)
    {
        b_state->counter_1 = 0;
        redraw = 0;
        unsigned char i = 0, t_x = 83, t_y = 8;
        char selected[] = ">", unselected[] = "";

        fill_buff(&main_buff, 0x00);

        gotoXY(0,0);

        // extra func should set counter_1 to > 1 if it doesn't need
        // constant servicing. Set counter_1 to 0 to have the screen redrawn.
        if(current_menu->extra_func)// && b_state->counter_1 == 1 )
        {
            current_menu->extra_func(b_state);
        }

        for(i = 0; i < current_menu->num_entries; i++)
        {
            loc.x = 0 ;

            loc.y = i*t_y;

            loc.y -= i;

            draw_square(&main_buff, loc, t_x, t_y);

            buffString(loc.x +2, loc.y + 2,
                        current_menu->entries[i]->text,
                        &main_buff);

            if(i == current_menu->selected
                    && current_menu->entries[i]->menu_entry )
            {
                buffString(loc.x + 71, loc.y + 2,
                            selected,
                            &main_buff);

                invertBuffArea(loc.x + 1 ,
                                loc.y + 1,
                                 t_x - 1,
                                 t_y - 2,
                                 &main_buff);
            }
            else if(i == current_menu->selected)
                invertBuffArea(loc.x + 1 ,
                                loc.y + 1,
                                 t_x - 3,
                                 t_y - 2,
                                 &main_buff);
        }

        blitBuff_opt(&main_buff, 0, 0);
        b_state->counter_1 = 1;
    }

    if(current_menu->extra_func && b_state->counter_1 == 1 )
    {
        current_menu->extra_func(b_state);
    }

}

void* manual_contrast(struct BadgeState *b_state)
{
    static struct pix_buff buff;

    static unsigned char leds = 0xff, x = 40, y  = 35, redraw = 0;

    //if(!b_state->counter_2++)
    {
        b_state->slide_handler(&b_state->slide_states);

        //set_leds(b_state->slide_states.front.lower_loc);
        char lr_swipe = b_state->slide_states.front.lr_swipe;
        char bt_swipe = b_state->slide_states.front.bt_swipe;
        //set_leds(leds += bt_swipe);

        if(lr_swipe < 0 && x > 10)
                //&& (current_menu->selected < (current_menu->num_entries - 1)))
        {
            //current_menu->selected += 1;
            x--;
            gContrast--;
            LCDInit();
            redraw = 1;
        }

        if(lr_swipe > 0 && x < 70)//&& (current_menu->selected > 0))
        {
            //current_menu->selected -= 1;
            x++;
            gContrast++;
            LCDInit();
            redraw = 1;
        }
    }
    if ( button_pressed == 250 )
    {
       // if(current_menu->selected == 2)
        {
            LCDClear();
            fill_buff(&buff, 0x00);

            current_menu = &settings_page;
            start_state.next_state = &start_state;
            b_state->next_state = &start_state;
            redraw = 1;
            button_pressed++;
            return;
        }
    }

    if(b_state->counter_1 == 0 || redraw)
    {
        struct coord loc;
                loc.x = 0;
                loc.y = y - 1;
        LCDClear();
        //fill_buff(&buff, 0x00);
        b_state->counter_1 = 1;
        redraw = 0;
        buff.height = 48;
        buff.width = 84;
        char msg[] = "Press BTN\nwhen finished";
        buff.pixels = pix;
        fill_buff(&buff, 0x00);
        buffString(0, 0,
                    msg,
                    &buff);
        draw_square(&buff, loc, 83, 7);
        invertBuffArea(x,
                       y,
                       7,
                       3,
                       &buff);

        blitBuff_opt(&buff, 0, 0);
    }
}

#define DEBOUNCE 15
void* sliderPlay(struct BadgeState *b_state)
{
    static unsigned char x = 20, y = 20;
    static unsigned char leds = 0b00011000;
    static unsigned char xor = 0x00;

    char putPix = 0;
    b_state->slide_handler(&b_state->slide_states);

    //set_leds(b_state->slide_states.front.lower_loc);
    char lr_swipe = b_state->slide_states.front.lr_swipe;
    char bt_swipe = b_state->slide_states.front.bt_swipe;

    if(lr_swipe > 0)
    {
        struct pix_buff buff;
        buff.height = 4;
        buff.width = 4;
        unsigned char pix[4] = {0x00, 0x00, 0x00, 0x00};
        buff.pixels = pix;

        struct coord loc;
        loc.x = 0;
        loc.y = 0;

        //draw_square(&buff, loc, 4, 4);

        if(leds != 0x03)
        {
            leds >>= 1;
            b_state->counter_1 = 0;
        }
        
//        if(xor)
//            blitBuff(&buff, x, y);
        //    putPixel(x,y,0);
        x += 1;

        putPix = 1;
    }
    else if (lr_swipe < 0)
    {
        if(leds != 0xC0)
        {
            leds <<= 1;

            b_state->counter_1 = 0;
        }
        if(xor)
            putPixel(x,y,0);
        x -= 1;
        putPix = 1;
    }

    if(bt_swipe > 0)
    {
        if(leds != 0x03)
        {
            leds >>= 1;
            b_state->counter_1 = 0;
        }
        if(xor)
            putPixel(x,y,0);
        y -= 1;
        putPix = 1;
    }
    else if (bt_swipe < 0)
    {
        if(leds != 0xC0)
        {
            leds <<= 1;

            b_state->counter_1 = 0;
        }
        if(xor)
            putPixel(x,y,0);
        y += 1;
        putPix = 1;
    }

    if(putPix)
        putPixel(x, y, 1);
    
    else if ( button_pressed == 250 )
    {
        LCDClear();
    }
    
    if(b_state->slide_states.bottom_hold_count > DEBOUNCE)
    {
        xor = ~xor;
        b_state->slide_states.bottom_hold_count = 0;
    }

    set_leds(leds ^ xor);
    return 0;
}

#define SNAKE_RATE 6000
#define SNAKE_START_SIZE 5
struct SnakeSeg snake_ll[200];
void* snake(struct BadgeState *b_state)
{
    static struct CoOrd food;
    static struct SnakeSeg head;
    static struct pix_buff buff;

    b_state->slide_handler(&b_state->slide_states);

    //set_leds(b_state->slide_states.front.lower_loc);
    char lr_swipe = b_state->slide_states.front.lr_swipe;
    char bt_swipe = b_state->slide_states.front.bt_swipe;
    
    if ( button_pressed == 250)
    {
        fill_buff(&main_buff, 0x00);
        start_state.next_state = &start_state;
        b_state->next_state = &start_state;
        b_state->counter_2 = 0;
        b_state->counter_1 = 0;
        b_state->big_counter = 0;
        return;
    }

    if(bt_swipe < 0 && !snake_ll[0].direction.yV)
    {
        snake_ll[0].direction.yV = 1;
        snake_ll[0].direction.xV = 0;
        //current_menu->selected += 1;
    }
    if(bt_swipe > 0 && !snake_ll[0].direction.yV )
    {
        snake_ll[0].direction.yV = -1;
        snake_ll[0].direction.xV = 0;
        //current_menu->selected -= 1;
    }
    if(lr_swipe > 0 && !snake_ll[0].direction.xV)
    {
        snake_ll[0].direction.yV = 0;
        snake_ll[0].direction.xV = 1;
    }
    if(lr_swipe < 0 && !snake_ll[0].direction.xV)
    {
        snake_ll[0].direction.yV = 0;
        snake_ll[0].direction.xV = -1;
    }
    unsigned char i = 0, j = 0;
    if(!b_state->counter_2)
    {
        LCDClear();
        b_state->next_state = b_state;

        main_buff.pixels = pix;
        main_buff.width = 84;
        main_buff.height = 48;
        
        b_state->counter_2 = 1;

        //need to do random init here instead
        food.x = 40;
        food.y = 20;

        snake_ll[0].location.x = 35;
        snake_ll[0].location.y = 20;
        snake_ll[0].direction.xV = 1;
        snake_ll[0].direction.yV = 0;

        for(i = 1; i < SNAKE_START_SIZE; i ++)
        {
            snake_ll[i].location = snake_ll[i-1].location;
            snake_ll[i].location.x--;
        }
        b_state->counter_1 = i;
    }

    //only update sometimes, game gets faster as snake gets bigger
    if(b_state->big_counter++ > (SNAKE_RATE - (b_state->counter_1 << 7) ))
    {
        LCDClear();

        struct coord loc;

        loc.x = 0;
        loc.y = 0;
        fill_buff(&main_buff, 0x00);

        draw_square(&main_buff, loc, 83, 47);
        
        loc.x = 62;
        loc.y = 0;
        draw_square(&main_buff, loc, 21, 8);

        char score[] = "999";
        score[0] = 48 + (b_state->counter_1 - SNAKE_START_SIZE) / 100;
        score[1] = 48 + (b_state->counter_1 - SNAKE_START_SIZE) % 100 / 10;
        score[2] = 48 + (b_state->counter_1 - SNAKE_START_SIZE) % 100 % 10;
        buffString(loc.x+2, loc.y + 2,
            score,
            &main_buff);

        b_state->big_counter = 0;

        putPixel_toBuff(&main_buff,
                        food.x,
                        food.y,
                        1);

        if(snake_ll[0].location.x == food.x
                 && snake_ll[0].location.y == food.y)
        {
            srand(food.x);

            food.x = (food.x + 5) %62;
            food.y = (food.y + 5) %38 + 10;
//            food.x = rand()%81 + 2;
//            food.y = rand()%45 + 2;
            b_state->counter_1++;
            for(i = 0; i < b_state->counter_1; i++)
            {
                if(snake_ll[i].location.x == food.x
                  && snake_ll[i].location.y == food.y)
                {
                    //re init x and y
                    food.x = (food.x + 5) %62;
                    food.y = (food.y + 5) %38 + 10;
//                    food.x = rand()%81 + 2;
//                    food.y = rand()%45 + 2;
                }
            }
        }

        for(i = b_state->counter_1 - 1; i > 0; i--)
        {
            snake_ll[i].location = snake_ll[i - 1].location;

            putPixel_toBuff(&main_buff,
                            snake_ll[i].location.x,
                            snake_ll[i].location.y,
                            1);
        }

        putPixel_toBuff(&main_buff,
                        snake_ll[0].location.x += snake_ll[0].direction.xV,
                        snake_ll[0].location.y += snake_ll[0].direction.yV,
                            1);

        //check for boundry bust
        if(snake_ll[0].location.x >= 83 || snake_ll[0].location.y >=46
           || snake_ll[0].location.x < 1  || snake_ll[0].location.y < 1 )
        {
            start_state.next_state = &start_state;
            b_state->next_state = &start_state;
            b_state->counter_2 = 0;
        }

        for(i = 1; i < b_state->counter_1; i++)
        {
            if(snake_ll[i].location.x == snake_ll[0].location.x
              && snake_ll[i].location.y == snake_ll[0].location.y)
            {
                start_state.next_state = &start_state;
                b_state->next_state = &start_state;
                b_state->counter_2 = 0;
            }
        }
        blitBuff_opt(&main_buff, 0, 0);
    }
}

#define BIRD_RATE 3000
#define BIRD_ST_HIEGHT 20
#define BIRD_X 20
#define PIPE_RATE 50
#define SHORTEST_PIPE_D 30
#define PIPE_X_B4_ADD 84 - SHORTEST_PIPE_D
#define G_ACC 1
#define PIPE_W 5    //width of the pipes
#define PIPE_H 25   //height of openings
#define MAX_PIPES 2
struct coord pipe_locs[MAX_PIPES];
unsigned char bird_y = BIRD_ST_HIEGHT,
                         collision = 0, b_rand = 0;
char bird_y_vel = 0, y_acc_length = 0, y_acc_mag = -1, draw_pipe = 0;
// y is inverted, so to minimize extra calcs, so is accel sign
// Really ugly as one big function, may take time to separate out later....
void* badgy_bird(struct BadgeState *b_state)
{
    unsigned char i = 0, j = 0;
    unsigned char opening_height = 27;
    static unsigned char pipes_cleared = 0, last_cleared = 99;
    unsigned char score[] = "999";
    //static unsigned int pipe_rate_cnt = 0;
    struct coord loc;
    //static struct coord pipe_locs[MAX_PIPES];

    b_state->slide_handler(&b_state->slide_states);

    //set_leds(b_state->slide_states.front.lower_loc);
    char lr_swipe = b_state->slide_states.front.lr_swipe;
    char bt_swipe = b_state->slide_states.front.bt_swipe;

    //initialize things
    if(!b_state->counter_2)
    {
        //unsigned char i, j;
        char badgy_txt[] = "Badgy", bird_txt[] = "Bird";
        LCDClear();
        b_state->next_state = b_state;
        collision = 0;
        pipes_cleared = 0;
        last_cleared = 99;

        main_buff.pixels = pix;
        main_buff.width = 84;
        main_buff.height = 48;

        b_state->counter_2 = 1;

        //force update
        b_state->big_counter = BIRD_RATE;
        draw_pipe = 1;

        loc.x = 0;
        loc.y = 0;

        //init all pipes
        for(i = 0; i < MAX_PIPES; i++)
        {
            //255 will == not it use yet
            pipe_locs[i].x = 0xff;
            pipe_locs[i].y = 0xff;
        }

        b_state->counter_1 = 0;
        bird_y = BIRD_ST_HIEGHT;
        clear_screen_buff();
        fill_buff(&main_buff, 0x00);
        draw_square(&main_buff, loc, 83, 48);
        buffString(31, 2,
            badgy_txt,
            &main_buff);
        buffString(41, 10,
                    bird_txt,
                    &main_buff);
        bird_idle_buff.pixels = bird_flap;

        //setup paused screen
        blitBuff_toBuff(&bird_idle_buff, &main_buff,
                        20, (unsigned char) bird_y,
                        ALPHA );
        
        blitBuff_opt(&main_buff, 0, 0);

    }
    // paused start screen
    else if(b_state->counter_2 == 1)
    {
        if ( button_pressed == 250)// || b_state->slide_states.bottom_hold_count > 2)
        {
            b_state->counter_2++;
            button_pressed++;
            y_acc_mag = -8;
            y_acc_length = 7;
            b_state->counter_1 = 0;
        }
    }
    // game playing
    else
    {
        if ( button_pressed == 250)// || b_state->slide_states.bottom_hold_count > 2)
        {
            button_pressed++;
            y_acc_mag = -8;
            y_acc_length = 7;
            b_state->counter_1 = 0;

            //gen random from time between btn presses
            b_rand ^= ReadCoreTimer() & 0xff;
        }

         if(b_state->big_counter++ > BIRD_RATE)
         {
             //clean things up
             clear_screen_buff();
             fill_buff(&main_buff, 0x00);

             //hit floor or pipe, enter start screen after this draw
             if(collision)
             {
                b_state->counter_2 = 0;
                b_state->counter_1 = 0;
                b_state->big_counter = 0;     
             }

            //flapping bird, apply flap accel
            if( y_acc_length && y_acc_mag)
            {
                y_acc_length--;
                y_acc_mag++;
                bird_y_vel = (G_ACC + y_acc_mag + b_state->counter_1);
            }
            //falling bird
            else
            {
                bird_y_vel += (G_ACC + b_state->counter_1);
            }

            //apply velocity
            bird_y += bird_y_vel;

            if(bird_y_vel>0)
                bird_idle_buff.pixels = bird_idle;
            else
                bird_idle_buff.pixels = bird_flap;

            if(bird_y >= 35)
            {
                collision |= 1;
                bird_y_vel = 0;
            }
            else
                b_state->counter_1++;

            b_state->big_counter = 0;

            for(i = 0; i < MAX_PIPES; i++)
            {
                // reset pipe
                if(pipe_locs[i].x == 0)
                {
                    pipe_locs[i].x = 0xff;
                    pipe_locs[i].y = 0xff;
                }
                // pipe not in play, check if it can be and
                // randomly put it into play
                else if(pipe_locs[i].x == 0xff)
                {
                    // j is  index of pipe in front of i pipe
                    //j = (i == 0) ?  MAX_PIPES - 1: i -1;
                    if(!i)
                        j = MAX_PIPES - 1;
                    else
                        j = i - 1;

                    if(pipe_locs[j].x != 0xff || pipe_locs[j].x < PIPE_X_B4_ADD)
                    {
                        //random is div 3
                        if(pipe_locs[j].x < PIPE_X_B4_ADD && !(b_rand % 3))
                        {
                            pipe_locs[i].x = 83 - PIPE_W - 1;
                            pipe_locs[i].y = opening_height + (b_rand % 15);
                        }
                    }
                    else if( !i )
                    {
                        pipe_locs[i].x = 83 - PIPE_W - 1;
                        pipe_locs[i].y = opening_height + (b_rand % 15);
                    }
                }
                //pipe needs drawing
                if(pipe_locs[i].x != 0 && pipe_locs[i].x != 0xff)// && !collision)
                {
                    unsigned char h = pipe_locs[i].y;
                    pipe_locs[i].y = 0;

                    //draw top part of pipe
                    fill_buff_area(pipe_locs[i], PIPE_W, h - PIPE_H,
                                       0xff, &main_buff);

                    pipe_locs[i].y = h;
                    //bottom part of pipe
                    fill_buff_area(pipe_locs[i], PIPE_W, 48 - pipe_locs[i].y - 1,
                                        0xff, &main_buff);

                    pipe_locs[i].x -= 2;
                    if(pipe_locs[i].x < (BIRD_X - PIPE_W - 1) && (i != last_cleared))
                    {
                        last_cleared = i;
                        pipes_cleared++;
                    }
                }
            }
            draw_square(&main_buff, loc, 83, 48);
            collision |= blitBuff_toBuff_collision(&bird_idle_buff, &main_buff,
                                                BIRD_X, (unsigned char) bird_y, ALPHA );

            score[0] = 48 + (pipes_cleared) / 100;
            score[1] = 48 + (pipes_cleared) % 100 / 10;
            score[2] = 48 + (pipes_cleared) % 100 % 10;

            buffString(64, 2,
                        score,
                        &main_buff);

            blitBuff_opt(&main_buff, 0, 0);
        }
    }
}

#define MAIN_TICKER_RATE 60000
void* draw_main_ticker(struct BadgeState *b_state)
{
    //static unsigned char ticker_i = 0, cnt;
    
    b_state->big_counter_1++;

    if(b_state->big_counter_1 == MAIN_TICKER_RATE)
    {
        // tell menu maker to redraw
        b_state->counter_1 = 0;

        //reset counter
        b_state->big_counter_1 = 0;

        //scroll through events
        if(b_state->counter_2 < NUM_EVENTS - 1)
            b_state->counter_2++;
        else
            b_state->counter_2 = 0;
    }

    //may result in duplicate redraws... w/e
    if(!b_state->counter_1)
    {
        b_rtccTime current_time;
        struct coord loc;
        loc.x = 0;
        loc.y = 36;
        char start_time[5], end_time[5], now_time[] = "11:11";

        //current_time.l = get_time();
        //current_time.l = 0x21140000;
        intTime_to_charTime(start_time, conf_events_d1[b_state->counter_2].start_time);
        intTime_to_charTime(end_time, conf_events_d1[b_state->counter_2].end_time);

//        draw_square(&main_buff, loc, 83, 11);
        draw_square(&main_buff, loc, 34, 11);
        buffString(1, 39,
            start_time,
                    &main_buff);

//        buffString(48, 39,
//            end_time,
//                    &main_buff);

//        now_time[0] = hextab[((current_time.hour >>  4) & 0xF)];
//        now_time[1] = hextab[(current_time.hour      ) & 0xF];
//        now_time[2] = ':';
//        now_time[3] = hextab[(current_time.min >>  4) & 0xF];
//        now_time[4] = hextab[(current_time.min      ) & 0xF];
//        now_time[5] = '.';
//        now_time[6] = hextab[(current_time.sec >>  4) & 0xF];
//        now_time[7] = hextab[(current_time.sec      ) & 0xF];

//        now_time[0] = 48 + ((current_time.hour >>  4) & 0xF);
//        now_time[1] = 48 + ((current_time.hour      ) & 0xF);
//        now_time[2] = ':';
//        now_time[3] = 48 + ((current_time.min >>  4) & 0xF);
//        now_time[4] = 48 + ((current_time.min      ) & 0xF);

        setTimeString(b_state->tm, now_time);
//        now_time[0] = 48 + ((b_state->tm.hour >>  4) & 0xF);
//        now_time[1] = 48 + ((b_state->tm.hour      ) & 0xF);
//        now_time[2] = ':';
//        now_time[3] = 48 + ((b_state->tm.min >>  4) & 0xF);
//        now_time[4] = 48 + ((b_state->tm.min      ) & 0xF);


//        now_time[5] = '.';
//        now_time[6] = 48 + ((current_time.sec >>  4) & 0xF);
//        now_time[7] = 48 + ((current_time.sec      ) & 0xF);

        buffString(48, 39,
                    now_time,
                    &main_buff);

        invertBuffArea(47 ,
                        36,
                         33,
                         11,
                         &main_buff);

        buffString_trunc(0, 28,
                        conf_events_d1[b_state->counter_2].title,
                        14,
                        11,
                        "...",
                    &main_buff);
    }
}

void printTouchVals(unsigned char btm, unsigned char side)
{
    char val[3];
     val[0] = ' ';
     val[1] = ' ';
     val[2] = 0;
     LCDString(val);
     LCDString(val);

    if(btm)
    {
        utoa(val, (unsigned) G_lower_slider_left, 10);

        LCDString(val);

        val[0] = ' ';
        val[1] = ' ';
        val[2] = 0;
        LCDString(val);

        utoa(val, (unsigned) G_lower_slider_right, 10);
        LCDString(val);
    }

    if(btm && side)
    {
        //spacers
        val[0] = '-';
        val[1] = '-';
        val[2] = 0;
        LCDString(val);
    }

    //LCDClear();
    if (side)
    {
        utoa(val, (unsigned) G_side_slider_left, 10);

        //side left
        LCDString(val);

        //seperator
        val[0] = ' ';
        val[1] = ' ';
        val[2] = 0;
        LCDString(val);

        //side right
        utoa(val, (unsigned) G_side_slider_right, 10);
        LCDString(val);
    }
}

void* browse_schedule(struct BadgeState *b_state)
{
    unsigned char redraw = 0;
    b_state->slide_handler(&b_state->slide_states);

    char lr_swipe = b_state->slide_states.front.lr_swipe;
    char bt_swipe = b_state->slide_states.front.bt_swipe;
    if(!b_state->counter_1)
    {
        redraw = 1;
        b_state->counter_1++;
        b_state->next_state = b_state;
    }

    if(bt_swipe < 0 && b_state->counter_2 < NUM_EVENTS - 1)
    {
        b_state->counter_2++;
        redraw = 1;
    }

    if(bt_swipe > 0 && b_state->counter_2 > 0)
    {
        b_state->counter_2--;
        redraw = 1;
    }
    if ( button_pressed == 250)
    {
        button_pressed++;
        fill_buff(&main_buff, 0x00);
        start_state.next_state = &start_state;
        b_state->next_state = &start_state;
        b_state->counter_1 = 0;

    }
    if(redraw)
    {
        struct coord loc;
        loc.x = 0;
        loc.y = 0;
        char start_time[5], end_time[5];
        fill_buff(&main_buff, 0x00);
        intTime_to_charTime(start_time, conf_events_d1[b_state->counter_2].start_time);
        intTime_to_charTime(end_time, conf_events_d1[b_state->counter_2].end_time);

        draw_square(&main_buff, loc, 83, 11);

        buffString(1, 2,
                    start_time,
                    &main_buff);

        buffString(48, 2,
                    end_time,
                    &main_buff);

        buffString(0, 14,
            conf_events_d1[b_state->counter_2].title,
                    &main_buff);

        blitBuff_opt(&main_buff, 0, 0);
    }
}

void* adjust_time(struct BadgeState *b_state)
{
    unsigned char redraw = 0;
    static unsigned char hour = 0x08, min = 0x00;
    b_state->slide_handler(&b_state->slide_states);

    char lr_swipe = b_state->slide_states.front.lr_swipe;
    char bt_swipe = b_state->slide_states.front.bt_swipe;
    
    if(!b_state->counter_1)
    {
        redraw = 1;
        b_state->counter_1++;
        b_state->next_state = b_state;
    }

    if(bt_swipe < 0)// && b_state->counter_2 < NUM_EVENTS - 1)
    {
        if(b_state->counter_1 ==  1 && hour < 24)
            //hour++;
            bcdIncrement(&hour);
        else if (b_state->counter_1 ==  2 && min < 60)
            //min++;
            bcdIncrement(&min);
        //b_state->counter_2++;
        redraw = 1;
    }

    if(bt_swipe > 0)// && b_state->counter_2 > 0)
    {
        if(b_state->counter_1 ==  1 && hour > 0)
            //hour--;
            bcdDecrement(&hour);
        else if (b_state->counter_1 ==  2 && min > 0)
            //min--;
            bcdDecrement(&min);
        //b_state->counter_2--;
        redraw = 1;
    }

    if(lr_swipe > 0)
    {
        if(b_state->counter_1 == 1)
            b_state->counter_1 = 2;
        redraw = 1;
    }

    if(lr_swipe < 0)
    {
        if(b_state->counter_1 == 2)
            b_state->counter_1 = 1;
        redraw = 1;
    }

    if ( button_pressed == 250)
    {
        b_state->tm.hour = hour;
        b_state->tm.min = min;
        RtccSetTimeDate(b_state->tm.l, b_state->dt.l);
        button_pressed++;
        fill_buff(&main_buff, 0x00);
        start_state.next_state = &start_state;
        b_state->next_state = &start_state;
        b_state->counter_1 = 0;
    }
    if(redraw)
    {
        struct coord loc;
        loc.x = 0;
        loc.y = 0;
        unsigned char inv_x, inv_y = 2;
        char hours[] = "99", minutes[] = "99";
        fill_buff(&main_buff, 0x00);

        setBase10String(hour, hours);
        setBase10String(min, minutes);

        draw_square(&main_buff, loc, 83, 11);

        buffString(24, 2,
                    hours,
                    &main_buff);

        buffString(48, 2,
                    minutes,
                    &main_buff);

        //hour selected
        if(b_state->counter_1 == 1)
        {
            inv_x = 23;
        }
        else if (b_state->counter_1 == 2)
        {
            inv_x = 47;
        }

        invertBuffArea(inv_x ,
                        inv_y,
                         13,
                         6,
                         &main_buff);
        
        blitBuff_opt(&main_buff, 0, 0);
    }
}

void* image_viewer(struct BadgeState *b_state)
{
    unsigned char redraw = 0;
    b_state->slide_handler(&b_state->slide_states);

    char lr_swipe = b_state->slide_states.front.lr_swipe;
    char bt_swipe = b_state->slide_states.front.bt_swipe;

    if(!b_state->counter_1)
    {
        redraw = 1;
        b_state->counter_1++;
        b_state->next_state = b_state;
    }

    if(bt_swipe < 0 && b_state->counter_2 < NUM_IMAGE_ASSETS - 1)
    {
        b_state->counter_2++;
        redraw = 1;
    }

    if(bt_swipe > 0 && b_state->counter_2 > 0)
    {
        b_state->counter_2--;
        redraw = 1;
    }
    if ( button_pressed == 250)
    {
        button_pressed++;
        fill_buff(&main_buff, 0x00);
        start_state.next_state = &start_state;
        b_state->next_state = &start_state;
        b_state->counter_1 = 0;

    }
    if(redraw)
    {
        blitBuff_opt(&screen_images[b_state->counter_2].buff, 0, 0);
    }
}

#define DELAY_INTERVAL 50000
void* setup_screen_saver(struct BadgeState *b_state)
{
    static unsigned char num_images = 0, selecting = 0, cnt = 0;
    unsigned char redraw = 0;
    b_state->slide_handler(&b_state->slide_states);

    char lr_swipe = b_state->slide_states.front.lr_swipe;
    char bt_swipe = b_state->slide_states.front.bt_swipe;

    if( b_state->big_counter)
    {
        b_state->big_counter--;
        if(!b_state->big_counter)
            redraw = 1;
    }

    if(!b_state->counter_1)
    {
        b_state->big_counter_1 = 0;
        //selecting = 0;
        redraw = 1;
        b_state->counter_1++;
        //b_state->big_counter_1 = 0;
        b_state->next_state = b_state;

        if(!b_state->counter_2)
            b_state->counter_2++;
    }

    if(bt_swipe < 0 && b_state->counter_2 < NUM_IMAGE_ASSETS)
    {
        b_state->counter_2++;
        redraw = 1;
    }

    if(bt_swipe > 0 && b_state->counter_2 > 0)
    {
        b_state->counter_2--;
        redraw = 1;
    }
    if ( button_pressed == 250)
    {
        button_pressed++;

        //go to next step in the setup
        if(b_state->big_counter_1 == 0)
        {
            fill_buff(&main_buff, 0x00);
            b_state->big_counter_1 = 1;
            char num_images_str[] = "99";

            setBase10String(num_saver_imgs, num_images_str);
            buffString(10, 9,
                        "SELECTED:",
                        &main_buff);

            buffString(68, 9,
                        num_images_str,
                        &main_buff);
            b_state->big_counter = DELAY_INTERVAL;
            b_state->counter_2 = 0;
            redraw = 1;
            selecting = 0;
        }
        else if(b_state->big_counter_1 == 1)
        {
            screen_saver_imgs[selecting] = &screen_images[b_state->counter_2];
            selecting++;
            if(selecting > (num_saver_imgs - 1))
            {
                //b_state->big_counter_1++;
                b_state->big_counter_1 = 0;
                fill_buff(&main_buff, 0x00);
                start_state.next_state = &start_state;
                b_state->next_state = &start_state;
                b_state->counter_1 = 0;
                return;
            }
        }
    }
    
    if(redraw)
    {
        if(b_state->big_counter_1 == 0)
        {
            //b_state->counter_2 = 0;
            fill_buff(&main_buff, 0x00);

            if(b_state->counter_2 == 0)
                b_state->counter_2++;

            num_saver_imgs = b_state->counter_2;
            char num_images_str[] = "99";

            setBase10String(num_saver_imgs, num_images_str);
            buffString(17, 9,
                        "HOW MANY",
                        &main_buff);

            buffString(21, 16,
                        "IMAGES",
                        &main_buff);
            
            buffString(37, 29,
                        num_images_str,
                        &main_buff);
            blitBuff_opt(&main_buff, 0, 0);
        }
        else if(b_state->big_counter_1 == 1 && !b_state->big_counter)
        {

            if(b_state->counter_2 > NUM_IMAGE_ASSETS - 1)
                b_state->counter_2 = NUM_IMAGE_ASSETS - 1;

             //shit, this call seems to overrun and whipe out num_images
//            blitBuff_toBuff(&screen_images[b_state->counter_2].buff,
//                            &main_buff,
//                            0, 0, OPAQUE);
            blitBuff_opt(&screen_images[b_state->counter_2].buff, 0, 0);
            b_state->big_counter_1 = 1;            
        }
        
    }
}