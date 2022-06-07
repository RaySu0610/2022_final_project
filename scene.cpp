#include "scene.h"

ALLEGRO_BITMAP *background = NULL;
ALLEGRO_FONT *font = NULL;
ALLEGRO_SAMPLE *song = NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;

// function of menu----------------------------------------------------------------------------------------------------------

void menu_init()
{
    font = al_load_ttf_font("./font/UndertaleSans.ttf", 50, 0);
    background = al_load_bitmap("./image/menu.jpg");
}
int dx = 10, dy = 0;
bool start_inrange = false, about_inrange = false, setting_inrange = false, exit_inrange = false, back_inrange = false;
;
void menu_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (start_inrange)
        {
            judge_next_window = GAME_SCENE_WINDOW;
            start_inrange = false;
        }
        else if (about_inrange)
        {
            judge_next_window = ABOUT_WINDOW;
            about_inrange = false;
        }
        else if (setting_inrange)
        {
            judge_next_window = SETTING_WINDOW;
            setting_inrange = false;
        }
        else if (exit_inrange)
        {
            judge_next_window = EXIT_WINDOW;
            setting_inrange = false;
        }
    }
    if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        if (event.mouse.y >= 600 + dy && event.mouse.y <= 655 + dy)
        {
            if (event.mouse.x >= 70 + dx && event.mouse.x <= 230 + dx)
                start_inrange = true, about_inrange = false, setting_inrange = false, exit_inrange = false;
            else if (event.mouse.x >= 290 + dx && event.mouse.x <= 450 + dx)
                start_inrange = false, about_inrange = true, setting_inrange = false, exit_inrange = false;
            else if (event.mouse.x >= 530 + dx && event.mouse.x <= 730 + dx)
                start_inrange = false, about_inrange = false, setting_inrange = true, exit_inrange = false;
            else if (event.mouse.x >= 790 + dx && event.mouse.x <= 920 + dx)
                start_inrange = false, about_inrange = false, setting_inrange = false, exit_inrange = true;
            else
                start_inrange = false, about_inrange = false, setting_inrange = false, exit_inrange = false;
        }
        else
            start_inrange = false, about_inrange = false, setting_inrange = false, exit_inrange = false;
    }
}
void menu_draw()
{
    // al_clear_to_color(al_map_rgb(100,100,100));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(background, 0, 0, 0);
    if (start_inrange)
    {
        al_draw_text(font, al_map_rgb(255, 100, 100), 90 + dx, HEIGHT / 2 + 220 + dy, ALLEGRO_ALIGN_LEFT, "Start");
        al_draw_rectangle(70 + dx, 600 + dy, 230 + dx, 655 + dy, al_map_rgb(255, 100, 100), 0);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), 90 + dx, HEIGHT / 2 + 220 + dy, ALLEGRO_ALIGN_LEFT, "Start");
        al_draw_rectangle(70 + dx, 600 + dy, 230 + dx, 655 + dy, al_map_rgb(255, 255, 255), 0);
    }
    if (about_inrange)
    {
        al_draw_text(font, al_map_rgb(255, 100, 100), 310 + dx, HEIGHT / 2 + 220 + dy, ALLEGRO_ALIGN_LEFT, "About");
        al_draw_rectangle(290 + dx, 600 + dy, 450 + dx, 655 + dy, al_map_rgb(255, 100, 100), 0);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), 310 + dx, HEIGHT / 2 + 220 + dy, ALLEGRO_ALIGN_LEFT, "About");
        al_draw_rectangle(290 + dx, 600 + dy, 450 + dx, 655 + dy, al_map_rgb(255, 255, 255), 0);
    }

    if (setting_inrange)
    {
        al_draw_text(font, al_map_rgb(255, 100, 100), 550 + dx, HEIGHT / 2 + 220, ALLEGRO_ALIGN_LEFT, "Setting");
        al_draw_rectangle(530 + dx, 600 + dy, 730 + dx, 655 + dy, al_map_rgb(255, 100, 100), 0);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), 550 + dx, HEIGHT / 2 + 220, ALLEGRO_ALIGN_LEFT, "Setting");
        al_draw_rectangle(530 + dx, 600 + dy, 730 + dx, 655 + dy, al_map_rgb(255, 255, 255), 0);
    }
    if (exit_inrange)
    {
        al_draw_text(font, al_map_rgb(255, 100, 100), 810 + dx, HEIGHT / 2 + 220 + dy, ALLEGRO_ALIGN_LEFT, "Exit");
        al_draw_rectangle(790 + dx, 600 + dy, 920 + dx, 655 + dy, al_map_rgb(255, 100, 100), 0);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), 810 + dx, HEIGHT / 2 + 220 + dy, ALLEGRO_ALIGN_LEFT, "Exit");
        al_draw_rectangle(790 + dx, 600 + dy, 920 + dx, 655 + dy, al_map_rgb(255, 255, 255), 0);
    }
}
void menu_destroy()
{
    al_destroy_font(font);
    al_destroy_bitmap(background);
}

// function of game_scene------------------------------------------------------------------------------------------------------
void game_scene_init()
{
    character_init();
    background = al_load_bitmap("./image/stage.jpg");

    song = al_load_sample("./sound/UNDERTALE Ruins.mp3");
    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);
    // al_set_sample_instance_gain(sample_instance ,1);
    //  Loop the song until the display closes
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(sample_instance, 0.1);

    al_play_sample_instance(sample_instance);
}
void game_scene_draw()
{
    al_draw_bitmap(background, 0, 0, 0);
    character_draw();
}
void game_scene_destroy()
{
    al_destroy_bitmap(background);
    character_destory();
}

// back button func-----------------------------------------------------------------------------------------------
void back_draw(int color)
{

    al_draw_text(font, al_map_rgb(255, color, color), 40 + dx, 705 + dy, ALLEGRO_ALIGN_LEFT, "Back");
    al_draw_rectangle(20 + dx, 700 + dy, 180 + dx, 755 + dy, al_map_rgb(255, color, color), 0);
}

// about func-----------------------------------------------------------------------------------------------------------

void about_init()
{
    font = al_load_ttf_font("./font/UndertaleSans.ttf", 50, 0);
}
void about_process(ALLEGRO_EVENT event)
{

    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (back_inrange)
        {
            judge_next_window = MENU_WINDOW;
            back_inrange = false;
        }
    }
    if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        if (event.mouse.y >= 700 + dy && event.mouse.y <= 755 + dy)
        {
            if (event.mouse.x >= 20 + dx && event.mouse.x <= 180 + dx)
                back_inrange = true;
            else
                back_inrange = false;
        }
        else
            back_inrange = false;
    }
}
void about_draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    if (back_inrange)
        back_draw(100);
    else
        back_draw(255);
}
void about_destroy()
{
    al_destroy_font(font);
}

// music func -----------------------------------------------------------------------------------------------------
void music_init()
{
    song = al_load_sample("./sound/UNDERTALE Start Menu.mp3");
    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);
    // al_set_sample_instance_gain(sample_instance ,1);
    //  Loop the song until the display closes
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(sample_instance, 0.1);

    al_play_sample_instance(sample_instance);
}
void music_destroy()
{
    al_destroy_sample_instance(sample_instance);
    al_destroy_sample(song);
}

// setting func------------------------------------------------------------------------------------------------

void setting_init()
{
    font = al_load_ttf_font("./font/UndertaleSans.ttf", 50, 0);
}
void setting_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (back_inrange)
        {
            judge_next_window = MENU_WINDOW;
            back_inrange = false;
        }
    }
    if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        if (event.mouse.y >= 700 + dy && event.mouse.y <= 755 + dy)
        {
            if (event.mouse.x >= 20 + dx && event.mouse.x <= 180 + dx)
                back_inrange = true;
            else
                back_inrange = false;
        }
        else
            back_inrange = false;
    }
}
void setting_draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    if (back_inrange)
        back_draw(100);
    else
        back_draw(255);
}
void setting_destroy()
{
    al_destroy_font(font);
}
