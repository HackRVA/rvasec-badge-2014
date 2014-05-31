#include "badge_common.h"
#include "badge14.h"
#include "schedule.h"

extern char gContrast;
unsigned char pix[504] = {0};
//dont need both in prod, debugging now
unsigned char pix2[504] = {0};

struct pix_buff main_buff, bird_idle_buff;



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
}

//initialize all the things
struct BadgeState start_state;

struct menu_entry *main_entries[2], games, settings, sketch, adventure;

//extra element for back button
struct menu_entry *game_entries[5], snake_e, bird_e, pong_e;
struct menu_entry *settings_entries[4], backlight, contrast, speaker;
struct menu_entry back_to_main;

struct menu_page *current_menu, main_page, games_page, settings_page;

//main menu texts
char game_txt[] = "DIVERSIONS",
        adventure_txt[] = "ADVENTURE",
        sketch_txt[] = "SKETCH",
        settings_txt[] = "SETTINGS";

//games menu texts
char snake_txt[] = "SNAKE",
        bird_txt[] = "BADGY BIRD",
        pong_txt[] = "PONG";

//settings menu text
char set_backlight[] = "BACKLIGHT",
        adjust_contrast[] = "CONTRAST",
        enable_speaker[] = "SPEAKER";

char go_back[] = "<-[BACK]";
//main_page.entries;
struct BadgeState snake_state, sketch_state, manual_contrast_state,
                    bird_state;

void initGFX(void)
{
    main_buff.pixels = pix2;
    main_buff.height = 48;
    main_buff.width = 84;

    bird_idle_buff.pixels = bird_idle;
    bird_idle_buff.height = 11;
    bird_idle_buff.width = 15;

}

void setupMenus(void)
{
    //setup states
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
        
    current_menu = &main_page;

    //-----------------------
    // setup MAIN
    main_page.num_entries = 2;
    main_page.selected = 0;
    main_page.entries = main_entries;
    main_page.extra_func = draw_schedule_ticker;
    
    main_entries[0] = &games;
        games.text = game_txt;
        games.menu_entry = &games_page;
        games.state_entry = 0;

//    main_entries[1] = &adventure;
//        adventure.text = adventure_txt;
//        adventure.menu_entry = 0;
//        adventure.state_entry = 0;

//    main_entries[2] = &sketch;
//        sketch.text = sketch_txt;
//        sketch.menu_entry = 0;
//        sketch.state_entry = &sketch_state;

    main_entries[1] = &settings;
        settings.text = settings_txt;
        settings.menu_entry = &settings_page;
        settings.state_entry = 0;
        
    //-----------------------
    // setup GAMES
    games_page.num_entries = 5;
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

    game_entries[4] = &back_to_main;


    //-----------------------
    // setup SETTINGS
    settings_page.num_entries = 4;
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

    settings_entries[3] = &back_to_main;
        back_to_main.text = go_back;
        back_to_main.menu_entry = &main_page;
        back_to_main.state_entry = 0;
}

struct BadgeState* Init_Game(void)
{
    //gContrast = 174;
    LCDInit();
    LCDClear();
    initGFX();
    //LCD_RVASec_Logo();
    //LCDLogo();
    //LCD backlight on
//    LATBbits.LATB7 = 1;
    button_pressed = button_cnt = button_used = 0;
    btm_size = side_size = 0;

    initBadgeState(&start_state);
    setupMenus();
    initConferenceEvents();
    //struct BadgeState *start_state = (struct BadgeState*)malloc(sizeof(struct BadgeState));

    //loooooooop
    start_state.next_state = &start_state;

    //start_state.state_handler = debugStage;
    start_state.state_handler = touchCalibrate;//main_menu;//tunnelFlight; // //

    start_state.slide_handler = autoSlide;


    return (struct BadgeState *)&start_state;
    //return &bird_state;
}

void Run_Game(struct BadgeState **state)
{
    *state = (*state)->next_state;
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
    t_state->lower_slider_left = G_lower_slider_left;
    t_state->lower_slider_right = G_lower_slider_right;

    //set to -1                            vv this almost works
    t_state->lower_loc =  -1; //t_state->lower_slider_left - t_state->lower_slider_right;

    //location will be higher if farther right (kinda)
    //(most left) left=6, Righ=5
    //L=5, R=5
    //L=5, R=4
    //L=6, R=4
    //L=6, R=3
    //L=7, R=3
    
    //hard code walues, need to have way to calibrate
    if(G_lower_slider_left == 6 && G_lower_slider_right >=5)
        t_state->lower_loc = 0;
    else if(G_lower_slider_left == 5 && G_lower_slider_right ==5)
        t_state->lower_loc = 1;
    else if(G_lower_slider_left == 5 && G_lower_slider_right == 4)
        t_state->lower_loc = 2;
    else if(G_lower_slider_left == 6 && G_lower_slider_right == 4)
        t_state->lower_loc = 3;
    else if(G_lower_slider_left == 6 && G_lower_slider_right == 3)
        t_state->lower_loc = 4;
    else if(G_lower_slider_left == 7 && G_lower_slider_right <= 3)
        t_state->lower_loc = 5;
    

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

    //t_state->side_slider_left = 0;
    //t_state->side_slider_right = 0;
}

//////////////////////////////
// STATE HANDLERS
//////////////////////////////
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
        LCDClear();
        LCDLogo();

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
        draw_square(&buff, loc, 83, 40);
        draw_square(&buff, loc, 40, 40);
        draw_square(&buff, loc, 32, 32);
        draw_square(&buff, loc, 24, 24);
        draw_square(&buff, loc, 16, 16);
        loc.x = 1;
        draw_square(&buff, loc, 8, 8);
        //unsigned char base = 50;

        // LCDLogo();
        //             x,  y,  w,  h
        //invertBuffArea(1, 1, 81, 6, &buff);
        //invertBuffArea(1, 8, 81, 6, &buff);
        invertBuffArea(1, 16, 81, 6, &buff);
        //invertBuffArea(1, 22, 81, 6, &buff);
        blitBuff_opt(&buff, 0, 0);


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
    static struct pix_buff buff;
    static struct coord loc;
                    loc.x = 40;
                    loc.y = 20;
    static unsigned char leds = 0xff, redraw = 0;

    b_state->slide_handler(&b_state->slide_states);

    //set_leds(b_state->slide_states.front.lower_loc);
    char lr_swipe = b_state->slide_states.front.lr_swipe;
    char bt_swipe = b_state->slide_states.front.bt_swipe;
    set_leds(leds += bt_swipe);

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

    if ( button_pressed == 250 )
    {
        LCDClear();
        fill_buff(&buff, 0x00);
        if( current_menu->entries[current_menu->selected]->menu_entry )
        {
            current_menu
                    = current_menu->entries[current_menu->selected]->menu_entry;
        }
        else if ( current_menu->entries[current_menu->selected]->state_entry )
        {
            b_state->next_state
                    = current_menu->entries[current_menu->selected]->state_entry;
        }
        redraw = 1;
        button_pressed++;
        return;
    }

    if(b_state->counter_1 == 0 || redraw)
    {
        LCDClear();
        //fill_buff(&buff, 0x00);
        b_state->counter_1 = 1;
        redraw = 0;
        unsigned char i = 0, t_x = 83, t_y = 8;
        char selected[] = ">", unselected[] = "";

        buff.height = 48;
        buff.width = 84;

        buff.pixels = pix;
        fill_buff(&buff, 0x00);

        gotoXY(0,0);

        for(i = 0; i < current_menu->num_entries; i++)
        {
            loc.x = 0 ;//- (t_x>>1);

            loc.y = i*t_y;// - (t_y>>1);

            loc.y -= i;

            draw_square(&buff, loc, t_x, t_y);

            buffString(loc.x +2, loc.y + 2,
                        current_menu->entries[i]->text,
                        &buff);

            if(i == current_menu->selected
                    && current_menu->entries[i]->menu_entry )
            {
                buffString(loc.x + 71, loc.y + 2,
                            selected,
                            &buff);

                invertBuffArea(loc.x + 1 ,
                                loc.y + 1,
                                 t_x - 1,
                                 t_y - 2,
                                 &buff);
            }
            else if(i == current_menu->selected)

            {
                invertBuffArea(loc.x + 1 ,
                                loc.y + 1,
                                 t_x - 3,
                                 t_y - 2,
                                 &buff);
            }
        }
        if(current_menu->extra_func)
        {
            current_menu->extra_func(b_state);
        }

        blitBuff_opt(&buff, 0, 0);
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
        set_leds(leds += bt_swipe);

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

#define SNAKE_RATE 15000
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

#define BIRD_RATE 5000
#define G_ACC 1
//y is inverted, so to minimize extra calcs, so is accel sign
void* badgy_bird(struct BadgeState *b_state)
{
    static unsigned char bird_y = 20;
    static char bird_y_vel = 0, y_acc_length = 0, y_acc_mag = -1;
    struct coord loc;


    b_state->slide_handler(&b_state->slide_states);

    //set_leds(b_state->slide_states.front.lower_loc);
    char lr_swipe = b_state->slide_states.front.lr_swipe;
    char bt_swipe = b_state->slide_states.front.bt_swipe;

    if(!b_state->counter_2)
    {
        LCDClear();
        b_state->next_state = b_state;

        main_buff.pixels = pix;
        main_buff.width = 84;
        main_buff.height = 48;

        b_state->counter_2 = 1;

        //force update
        b_state->big_counter = BIRD_RATE;

        loc.x = 0;
        loc.y = 0;
        fill_buff(&main_buff, 0x00);

        draw_square(&main_buff, loc, 83, 47);
        b_state->counter_1 = 0;

    }
    if ( button_pressed == 250 )
    {
        button_pressed++;
        y_acc_mag = -7;
        y_acc_length = 7;
        b_state->counter_1 = 0;
    }
    
     if(b_state->big_counter++ > BIRD_RATE)
     {
        clear_screen_buff();
        //draw_square(&main_buff, loc, 83, 47);
        blitBuff_opt(&main_buff, 0, 0);
        blitBuff_opt(&bird_idle_buff, 20, (unsigned char) bird_y, ALPHA);
     
        if( y_acc_length && y_acc_mag)
        {
            y_acc_length--;
            y_acc_mag++;
            bird_y_vel = (G_ACC + y_acc_mag + b_state->counter_1);
            
            bird_idle_buff.pixels = bird_flap;
        }
        else
        {
            bird_idle_buff.pixels = bird_idle;
            bird_y_vel += (G_ACC + b_state->counter_1);
        }

        bird_y += bird_y_vel;
        
        if(bird_y_vel>0)
            bird_idle_buff.pixels = bird_idle;
        else
            bird_idle_buff.pixels = bird_flap;

        if(bird_y >= 35)
        {
            bird_y_vel = 0;
            b_state->counter_1 = 0;
            bird_y = 35;
        }

        b_state->big_counter = 0;
        b_state->counter_1++;
    }
}

void* draw_schedule_ticker(struct BadgeState *b_state)
{
    b_state->buff.pixels = pix;
    b_state->buff.height = 48;
    b_state->buff.width = 84;
    struct coord loc;
    loc.x = 0;
    loc.y = 36;
    char test[] = "Welcome Test";
    char start_time[5], end_time[5];

    intTime_to_charTime(start_time, conf_events[b_state->counter_2].start_time);
    intTime_to_charTime(end_time, conf_events[b_state->counter_2].end_time);
    draw_square(&b_state->buff, loc, 83, 11);
    buffString(1, 39,
        start_time,
                &b_state->buff);

    buffString(48, 39,
        end_time,
                &b_state->buff);

    buffString(0, 28,
        conf_events[b_state->counter_2].title,
                &b_state->buff);
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
