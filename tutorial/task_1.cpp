/*

GOAL:
Create a display window.

*/
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_FONT *font;
ALLEGRO_BITMAP *img;
/*
    TODO: Declare display variable.
*/

const int width = 800;
const int height = 600;

void show_err_msg(int msg);
void game_init();
void game_begin();
void game_destroy();

int main(int argc, char *argv[])
{
    int msg = 0;

    printf("Hello world!!!\n");

    game_init();

    al_rest(2);

    game_begin();

    al_rest(2);
    printf("See you, world!!\n");

    game_destroy();
    return 0;
}

void show_err_msg(int msg)
{
    fprintf(stderr, "unexpected msg: %d", msg);
    game_destroy();
    exit(9);
}
/*
    The function above aims to show the error message and terminate the game.
    You may use it in any function need to deal with some error message.
    The program would not get any error if you don't utilize it,
    But you may get a tough debugging time when some mistakes happen.
    You can modify it to fit for your habit.
*/

void game_init()
{
    if (!al_init())
    {
        show_err_msg(-1);
    }

    al_init();
    display = al_create_display(width, height);
    al_set_window_position(display, 0, 0);

    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    /*
        TODO: Create your display variable.
    */
}

void game_begin()
{
    al_clear_to_color(al_map_rgb(255, 100, 30));

    font = al_load_ttf_font("./font/pirulen.ttf", 50, 0);
    al_draw_text(font, al_map_rgb(100, 100, 100), width / 2, height / 2, 0, "test");
    al_draw_rectangle(width - 200, height - 50, width, height, al_map_rgb(20, 30, 40), 3);

    img = al_load_bitmap("./htchen.jpg");
    al_draw_bitmap(img, 0, 0, 0);

    al_flip_display();

    /*
        TODO: Fill the whole window with an arbitrary color, and show the window
    */
}
void game_destroy()
{
    al_destroy_bitmap(img);
    al_destroy_display(display);
    /*
        TODO: Destroy everything you have initialized or created.
    */
}
