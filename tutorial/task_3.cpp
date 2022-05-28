/*

GOAL:
Create a event_queue and make close window by the up right corner cross possible.

*/

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define GAME_TERMINATE 666


#define AL_INIT_FAILED -1
#define DESPLAY_INIT_FAILED -2

ALLEGRO_DISPLAY* display = NULL;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;

bool key_state[ALLEGRO_KEY_MAX];

/*
 * TODO: Declare your event_queue and event.
 */

const int width = 800;
const int height = 600;

int pos_x=width/2;
int pos_y=height/2;

void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();

int keyboard_event();
int game_draw();
int game_update();

int main(int argc, char *argv[])
{
    int msg = 0;

    game_init();
    game_begin();
    printf("Hello world!!!\n");
    printf("Close window to terminate.\n");

    while ( msg != GAME_TERMINATE )
    {
        msg = game_run();
        if ( msg == GAME_TERMINATE )
        {
            printf("See you, world\n");
        }
    }
    game_destroy();
    return 0;
}

void show_err_msg(int msg)
{
    fprintf(stderr, "unexpected msg: %d", msg);
    game_destroy();
    exit(9);
}

void game_init()
{
    if ( !al_init() )
    {
        show_err_msg(AL_INIT_FAILED);
    }

    display = al_create_display(width, height);
    if ( display == NULL )
    {
        show_err_msg(DESPLAY_INIT_FAILED);
    }

    event_queue=al_create_event_queue();
    al_install_keyboard();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_init_primitives_addon();

    /*
     * TODO: initial display and event queue, and register specific event into event queue.
     */
}

void game_begin()
{
    al_clear_to_color(al_map_rgb(0,0,0));


    al_draw_rectangle(pos_x, pos_y, width, height, al_map_rgb(20, 30, 40), 3);

    al_flip_display();
}

int process_event()
{
    al_wait_for_event(event_queue,&event);

    keyboard_event();
    int error=game_update();
    game_draw();

    return error;

    /*
     * TODO: Get the earliest event from event_queue and judge whether it represents the closing of window.
     *       If so, return GAME_TERMINATE.
     * Hint: using event.type == ALLEGRO_EVENT_DISPLAY_CLOSE to judge whether the display is closed just now.
     */
}
int keyboard_event()
{
    if(event.type == ALLEGRO_EVENT_KEY_DOWN )
    {
        key_state[event.keyboard.keycode] =true;
    }
    else if( event.type == ALLEGRO_EVENT_KEY_UP )
    {
        key_state[event.keyboard.keycode] =false;
    }
    return 0;
}
int game_update()
{
    if( key_state[ALLEGRO_KEY_W])
    {
        //printf("w\n");
        pos_y -= 10;
    }
    else if( key_state[ALLEGRO_KEY_A])
    {
        pos_x -= 10;
    }
    else if( key_state[ALLEGRO_KEY_S])
    {
        pos_y += 10;
    }
    else if( key_state[ALLEGRO_KEY_D])
    {
        pos_x += 10;
    }
    else if(key_state[ALLEGRO_KEY_G])
    {
        return GAME_TERMINATE;
    }

    return 0;
}

int game_draw()
{
    al_draw_rectangle(pos_x, pos_y, width, height, al_map_rgb(20, 30, 40), 3);
    al_flip_display();
}

int game_run()
{
    int error=0;
    if(!al_is_event_queue_empty(event_queue))
    {
        error=process_event();
    }
    game_draw();
    return error;
    /*
     * TODO: Judge whether there's any event in the queue; if so, call process_event() to process it.
     */
}

void game_destroy()
{
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    /*
     * TODO: Destroy all thing you have created.
     */
}
