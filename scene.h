#include "global.h"
#include "charater.h"

enum window_
{
    MENU_WINDOW = 1,
    GAME_SCENE_WINDOW = 2,
    ABOUT_WINDOW = 3,
    SETTING_WINDOW = 4,
    EXIT_WINDOW = 5
};

void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void menu_destroy();



void back_draw(int color);

void about_init();
void about_process(ALLEGRO_EVENT event);
void about_draw();
void about_destroy();

void music_init();
void music_destroy();

void setting_init();
void setting_process(ALLEGRO_EVENT event);
void setting_draw();
void setting_destroy();

void volume_draw(int color);

void screen_set(int w,int h);

void game_scene_init();
void game_scene_draw();
void game_scene_destroy();
