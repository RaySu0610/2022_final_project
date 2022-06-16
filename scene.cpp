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
int dx = 10, dy = 0, scalar = 1, pos_x, pos_y;

bool start_inrange = false, about_inrange = false, setting_inrange = false, exit_inrange = false, back_inrange = false;

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
        pos_x = event.mouse.x;
        pos_y = event.mouse.y;
        if (pos_y >= (HEIGHT * 600 / 760) * scalar + dy && pos_y <= (HEIGHT * 655 / 760) * scalar + dy)
        {
            if (pos_x >= (WIDTH * 70 / 1024) * scalar + dx && pos_x <= (WIDTH * 230 / 1024) * scalar + dx)
                start_inrange = true;
            else if (pos_x >= (WIDTH * 290 / 1024) * scalar + dx && pos_x <= (WIDTH * 450 / 1024) * scalar + dx)
                about_inrange = true;
            else if (pos_x >= (WIDTH * 530 / 1024) * scalar + dx && pos_x <= (WIDTH * 730 / 1024) * scalar + dx)
                setting_inrange = true;
            else if (pos_x >= (WIDTH * 790 / 1024) * scalar + dx && pos_x <= (WIDTH * 920 / 1024) * scalar + dx)
                exit_inrange = true;
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
    al_draw_scaled_bitmap(background, 0, 0, 1024, 760, 0, 0, WIDTH, HEIGHT, 0);
    if (start_inrange)
    {
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH * 90 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "Start");
        al_draw_rectangle((WIDTH * 70 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, (WIDTH * 230 / 1024) * scalar + dx, (HEIGHT * 655 / 760) * scalar + dy, al_map_rgb(255, 100, 100), 0);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH * 90 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "Start");
        al_draw_rectangle((WIDTH * 70 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, (WIDTH * 230 / 1024) * scalar + dx, (HEIGHT * 655 / 760) * scalar + dy, al_map_rgb(255, 255, 255), 0);
    }
    if (about_inrange)
    {
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH * 310 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "About");
        al_draw_rectangle((WIDTH * 290 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, (WIDTH * 450 / 1024) * scalar + dx, (HEIGHT * 655 / 760) * scalar + dy, al_map_rgb(255, 100, 100), 0);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH * 310 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "About");
        al_draw_rectangle((WIDTH * 290 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, (WIDTH * 450 / 1024) * scalar + dx, (HEIGHT * 655 / 760) * scalar + dy, al_map_rgb(255, 255, 255), 0);
    }

    if (setting_inrange)
    {
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH * 550 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "Setting");
        al_draw_rectangle((WIDTH * 530 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, (WIDTH * 730 / 1024) * scalar + dx, (HEIGHT * 655 / 760) * scalar + dy, al_map_rgb(255, 100, 100), 0);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH * 550 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "Setting");
        al_draw_rectangle((WIDTH * 530 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, (WIDTH * 730 / 1024) * scalar + dx, (HEIGHT * 655 / 760) * scalar + dy, al_map_rgb(255, 255, 255), 0);
    }
    if (exit_inrange)
    {
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH * 810 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "Exit");
        al_draw_rectangle((WIDTH * 790 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, (WIDTH * 920 / 1024) * scalar + dx, (HEIGHT * 655 / 760) * scalar + dy, al_map_rgb(255, 100, 100), 0);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH * 810 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "Exit");
        al_draw_rectangle((WIDTH * 790 / 1024) * scalar + dx, (HEIGHT * 600 / 760) * scalar + dy, (WIDTH * 920 / 1024) * scalar + dx, (HEIGHT * 655 / 760) * scalar + dy, al_map_rgb(255, 255, 255), 0);
    }
}
void menu_destroy()
{
    al_destroy_font(font);
    al_destroy_bitmap(background);
}

// back button func-----------------------------------------------------------------------------------------------
void back_draw(int color)
{

    al_draw_text(font, al_map_rgb(255, color, color), (WIDTH * 40 / 1024) * scalar + dx, (HEIGHT * 705 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "Back");
    al_draw_rectangle((WIDTH * 20 / 1024) * scalar + dx, (HEIGHT * 700 / 760) * scalar + dy, (WIDTH * 180 / 1024) * scalar + dx, (HEIGHT * 755 / 760) * scalar + dy, al_map_rgb(255, color, color), 0);
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
        pos_x = event.mouse.x;
        pos_y = event.mouse.y;
        if (pos_y >= (HEIGHT * 700 / 760) * scalar + dy && pos_y <= (HEIGHT * 755 / 760) * scalar + dy)
        {
            if (pos_x >= (WIDTH * 20 / 1024) * scalar + dx && pos_x <= (WIDTH * 180 / 1024) * scalar + dx)
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
    al_set_sample_instance_gain(sample_instance, (volume_value - 10) / 200);

    al_play_sample_instance(sample_instance);
}
void music_destroy()
{
    al_destroy_sample_instance(sample_instance);
    al_destroy_sample(song);
}

// setting func------------------------------------------------------------------------------------------------

bool Size_inrange[3] = {false};
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
        if (pos_y >= (HEIGHT * 260 / 760) * scalar + dy && pos_y <= (HEIGHT * 300 / 760) * scalar + dy)
        {
            if (pos_x >= (WIDTH * 250 / 1024) * scalar + dx && pos_x <= (WIDTH * (250 + 200) / 1024) * scalar + dx)
            {
                volume_value = pos_x - WIDTH * 250 / 1024;
                al_set_sample_instance_gain(sample_instance, (volume_value - 10) / 200);
            }
        }
        else if (pos_y >= (HEIGHT * 445 / 760) * scalar + dy && pos_y <= (HEIGHT * 495 / 760) * scalar + dy)
        {
            if (Size_inrange[0] && WIDTH != 1024)
                screen_set(1024, 760);
            else if (Size_inrange[1] && WIDTH != 1280)
                screen_set(1280, 720);
            else if (Size_inrange[2] && WIDTH != 1440)
                screen_set(1440, 900);
        }
        else
            Size_inrange[0] = false, Size_inrange[1] = false, Size_inrange[2] = false;

        // printf("%d %d\n",pos_x,pos_y);
    }
    if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        pos_x = event.mouse.x;
        pos_y = event.mouse.y;
        if (pos_y >= (HEIGHT * 700 / 760) * scalar + dy && pos_y <= (HEIGHT * 755 / 760) * scalar + dy)
        {
            if (pos_x >= (WIDTH * 20 / 1024) * scalar + dx && pos_x <= (WIDTH * 180 / 1024) * scalar + dx)
                back_inrange = true;
            else
                back_inrange = false;
        }
        else if (pos_y >= (HEIGHT * 445 / 760) * scalar + dy && pos_y <= (HEIGHT * 495 / 760) * scalar + dy)
        {
            if (pos_x >= (WIDTH * 40 / 1024) * scalar + dx && pos_x <= (WIDTH * (305) / 1024) * scalar + dx)
                Size_inrange[0] = true;
            else if (pos_x >= (WIDTH * 370 / 1024) * scalar + dx && pos_x <= (WIDTH * (635) / 1024) * scalar + dx)
                Size_inrange[1] = true;
            else if (pos_x >= (WIDTH * 700 / 1024) * scalar + dx && pos_x <= (WIDTH * (959) / 1024) * scalar + dx)
                Size_inrange[2] = true;
            else
                Size_inrange[0] = false, Size_inrange[1] = false, Size_inrange[2] = false;
        }
        else
            Size_inrange[0] = false, Size_inrange[1] = false, Size_inrange[2] = false, back_inrange = false;
    }
}
void setting_draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    if (back_inrange)
        back_draw(100);
    else
        back_draw(255);

    al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH * 40 / 1024) * scalar + dx, (HEIGHT * 250 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "Volume");
    al_draw_rectangle((WIDTH * 250 / 1024) * scalar + dx, (HEIGHT * 280 / 760) * scalar + dy, (WIDTH * 450 / 1024) * scalar + dx, (HEIGHT * 280 / 760) * scalar + dy, al_map_rgb(255, 255, 255), 0);
    al_draw_filled_rectangle((WIDTH * (240 + volume_value) / 1024) * scalar + dx, (HEIGHT * 260 / 760) * scalar + dy, (WIDTH * (250 + volume_value) / 1024) * scalar + dx, (HEIGHT * 300 / 760) * scalar + dy, al_map_rgb(255, 255, 255));

    al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH * 40 / 1024) * scalar + dx, (HEIGHT * 380 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "Size");
    if (Size_inrange[0])
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH * 40 / 1024) * scalar + dx, (HEIGHT * 450 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "1024 X 760");
    else
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH * 40 / 1024) * scalar + dx, (HEIGHT * 450 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "1024 X 760");
    if (Size_inrange[1])
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH * 370 / 1024) * scalar + dx, (HEIGHT * 450 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "1280 X 720");
    else
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH * 370 / 1024) * scalar + dx, (HEIGHT * 450 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "1280 X 720");
    if (Size_inrange[2])
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH * 700 / 1024) * scalar + dx, (HEIGHT * 450 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "1440 X 900");
    else
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH * 700 / 1024) * scalar + dx, (HEIGHT * 450 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "1440 X 900");
}
void setting_destroy()
{
    al_destroy_font(font);
}

// volume func----------------------------------------------------------------------------------------------------------------------------------------
/*void volume_draw(int color)
{

    al_draw_text(font, al_map_rgb(255, color, color), (WIDTH * 40 / 1024) * scalar + dx, (HEIGHT * 250 / 760) * scalar + dy, ALLEGRO_ALIGN_LEFT, "Volume");
    al_draw_rectangle((WIDTH * 250 / 1024) * scalar + dx, (HEIGHT * 280 / 760) * scalar + dy, (WIDTH * 450 / 1024) * scalar + dx, (HEIGHT * 280 / 760) * scalar + dy, al_map_rgb(255, color, color), 0);
    al_draw_filled_rectangle((WIDTH * (240 + volume_value) / 1024) * scalar + dx, (HEIGHT * 260 / 760) * scalar + dy, (WIDTH * (250 + volume_value) / 1024) * scalar + dx, (HEIGHT * 300 / 760) * scalar + dy, al_map_rgb(255, color, color));
}*/

// size reset func------------------------------------------------------------------------------------------------------------
void screen_set(int w, int h)
{
    if (al_acknowledge_resize(display))
        printf("resize call is approved\n");
    else
        printf("resize call is rejected\n");

    if (al_resize_display(display, w, h))
    {
        printf("resize success!!(%d, %d)\n", w, h);
        WIDTH = w, HEIGHT = h;
    }
    else
    {
        printf("resize failed\n");
    }
}

// function of game_scene------------------------------------------------------------------------------------------------------
bool game_button[4] = {false};
enum
{
    game_button_fight = 0,
    game_button_act = 1,
    game_button_item = 2,
    game_button_mercy = 3
};
int game_scene_mode1 = 0;
// 0=>初始狀態 1=>fight 2=>act 3=>item 4=>mercy 5=>boss_term
int game_scene_mode2 = 0;
// 依照game_scene_mode1的不同，定義不同
int game_scene_counter = 0;

void game_scene_init()
{
    font = al_load_ttf_font("./font/UndertaleSans.ttf", 50, 0);
    character_init();

    // background = al_load_bitmap("./image/menu.jpg");
    // background = al_load_bitmap("./image/stage.jpg");

    // song = al_load_sample("./sound/UNDERTALE Ruins.mp3");
    // al_reserve_samples(20);
    // sample_instance = al_create_sample_instance(song);
    // // al_set_sample_instance_gain(sample_instance ,1);
    // //  Loop the song until the display closes
    // al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    // al_restore_default_mixer();
    // al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    // // set the volume of instance
    // al_set_sample_instance_gain(sample_instance, (volume_value-10)/200);

    // al_play_sample_instance(sample_instance);

    srand(time(NULL));
}
void game_scene_process(ALLEGRO_EVENT event)
{
    charater_process(event);

    if (game_scene_mode1 == 0)
    {
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (game_button[game_button_fight])
            {
                game_scene_mode1 = 1;
            }
            else if (game_button[game_button_act])
            {
                game_scene_mode1 = 2;
            }
            else if (game_button[game_button_item])
            {
                game_scene_mode1 = 3;
            }
            else if (game_button[game_button_mercy])
            {
                game_scene_mode1 = 4;
            }
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            pos_x = event.mouse.x;
            pos_y = event.mouse.y;
            if (pos_y >= (HEIGHT * 660 / HEIGHT) * scalar + dy && pos_y <= (HEIGHT * 715 / HEIGHT) * scalar + dy)
            {
                if (pos_x >= (WIDTH * 70 / WIDTH) * scalar + dx && pos_x <= (WIDTH * 230 / WIDTH) * scalar + dx)
                    game_button[game_button_fight] = true;
                else if (pos_x >= (WIDTH * 290 / WIDTH) * scalar + dx && pos_x <= (WIDTH * 450 / WIDTH) * scalar + dx)
                    game_button[game_button_act] = true;
                else if (pos_x >= (WIDTH * 530 / WIDTH) * scalar + dx && pos_x <= (WIDTH * 730 / WIDTH) * scalar + dx)
                    game_button[game_button_item] = true;
                else if (pos_x >= (WIDTH * 790 / WIDTH) * scalar + dx && pos_x <= (WIDTH * 920 / WIDTH) * scalar + dx)
                    game_button[game_button_mercy] = true;
                else
                    game_button[game_button_fight] = false, game_button[game_button_act] = false, game_button[game_button_item] = false, game_button[game_button_mercy] = false;
            }
            else
                game_button[game_button_fight] = false, game_button[game_button_act] = false, game_button[game_button_item] = false, game_button[game_button_mercy] = false;
        }
    }
    else if (game_scene_mode1 == 1) // fight
    {
    }
    else if (game_scene_mode1 == 2) // act
    {
    }
    else if (game_scene_mode1 == 3) // item
    {
    }
    else if (game_scene_mode1 == 4) // mercy
    {
    }
}

int game_button_draw()
{
    al_draw_text(
        font,
        game_button[game_button_fight] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 90 / 1024) * scalar + dx,
        (HEIGHT * 660 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "fight");
    al_draw_rectangle(
        (WIDTH * 70 / 1024) * scalar + dx,
        (HEIGHT * 660 / 760) * scalar + dy,
        (WIDTH * 230 / 1024) * scalar + dx,
        (HEIGHT * 715 / 760) * scalar + dy,
        game_button[game_button_fight] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        0);

    al_draw_text(
        font,
        game_button[game_button_act] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 340 / 1024) * scalar + dx,
        (HEIGHT * 660 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "act");
    al_draw_rectangle(
        (WIDTH * 320 / 1024) * scalar + dx,
        (HEIGHT * 660 / 760) * scalar + dy,
        (WIDTH * 424 / 1024) * scalar + dx,
        (HEIGHT * 715 / 760) * scalar + dy,
        game_button[game_button_act] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        0);

    al_draw_text(
        font,
        game_button[game_button_item] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 560 / 1024) * scalar + dx,
        (HEIGHT * 660 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "item");
    al_draw_rectangle(
        (WIDTH * 540 / 1024) * scalar + dx,
        (HEIGHT * 660 / 760) * scalar + dy,
        (WIDTH * 676 / 1024) * scalar + dx,
        (HEIGHT * 715 / 760) * scalar + dy,
        game_button[game_button_item] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        0);

    al_draw_text(
        font,
        game_button[game_button_mercy] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 810 / 1024) * scalar + dx,
        (HEIGHT * 660 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "mercy");

    al_draw_rectangle(
        (WIDTH * 790 / 1024) * scalar + dx,
        (HEIGHT * 660 / 760) * scalar + dy,
        (WIDTH * 950 / 1024) * scalar + dx,
        (HEIGHT * 715 / 760) * scalar + dy,
        game_button[game_button_mercy] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        0);
}
void game_scene_draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));

    game_button_draw();
    if (game_scene_mode1 == 0)
    {
        al_draw_rectangle( //邊框
            (bound_left)*scalar + dx,
            (bound_top)*scalar + dy,
            (bound_right)*scalar + dx,
            (bound_bottom)*scalar + dy,
            al_map_rgb(255, 255, 255),
            0);

        al_draw_text(
            font,
            al_map_rgb(255, 255, 255),
            (bound_left)*scalar + dx,
            (bound_top + (bound_bottom - bound_top) * 1 / 3) * scalar + dy,
            ALLEGRO_ALIGN_LEFT,
            "* Vegetoid came out of the earth!");

        al_draw_text(
            font,
            al_map_rgb(255, 255, 255),
            (bound_left)*scalar + dx,
            (600) * scalar + dy,
            ALLEGRO_ALIGN_LEFT,
            "Player name");

        al_draw_text(
            font,
            al_map_rgb(255, 255, 255),
            (bound_left * 4) * scalar + dx,
            (600) * scalar + dy,
            ALLEGRO_ALIGN_LEFT,
            "LV.1");
        al_draw_text(
            font,
            al_map_rgb(255, 255, 255),
            (bound_left * 6) * scalar + dx,
            (600) * scalar + dy,
            ALLEGRO_ALIGN_LEFT,
            "HP : ");
    }
    else if (game_scene_mode1 == 1)
    {
        al_draw_rectangle( //邊框
            (bound_left)*scalar + dx,
            (bound_top)*scalar + dy,
            (bound_right)*scalar + dx,
            (bound_bottom)*scalar + dy,
            al_map_rgb(255, 255, 255),
            0);

        al_draw_text(
            font,
            al_map_rgb(255, 255, 255),
            (bound_left)*scalar + dx,
            (bound_top + (bound_bottom - bound_top) * 1 / 3) * scalar + dy,
            ALLEGRO_ALIGN_LEFT,
            "* You attack the Vegetoid.");
        al_draw_text(
            font,
            al_map_rgb(255, 255, 255),
            (bound_left)*scalar + dx,
            (bound_top + (bound_bottom - bound_top) * 2 / 3) * scalar + dy,
            ALLEGRO_ALIGN_LEFT,
            "* Vegetoid HP 12 -> HP 8."); //要給實際參數值

        game_scene_counter++;
        if (game_scene_counter == 150)
        {
            game_scene_counter = 0;
            game_scene_mode1 = 5;
            game_scene_mode2 = 2;

            monster_attack_init2();
        }
    }
    else if (game_scene_mode1 == 2)
    {
    }
    else if (game_scene_mode1 == 3)
    {
    }
    else if (game_scene_mode1 == 4)
    {
    }
    else if (game_scene_mode1 == 5)
    {
        game_button[0] = false;
        game_button[1] = false;
        game_button[2] = false;
        game_button[3] = false;

        character_draw();

        al_draw_rectangle( //邊框
            (bound_left1)*scalar + dx,
            (bound_top)*scalar + dy,
            (bound_right1)*scalar + dx,
            (bound_bottom)*scalar + dy,
            al_map_rgb(255, 255, 255),
            0);

        if (game_scene_mode2 == 1)
        {
        }
        else if (game_scene_mode2 == 2)
        {
            monster_attack2();

            game_scene_counter++;
            if (game_scene_counter == 500)
            {
                game_scene_counter = 0;
                game_scene_mode1 = 0;
                game_scene_mode2 = 0;
            }
        }
    }

    // al_draw_scaled_bitmap(background, 0, 0, WIDTH, 720, 0, 0, WIDTH, HEIGHT, 0);
}

//一般攻擊2
int attack_sum2 = 8;
int attack_pos2[8][2];
int attack_direc2[8][2];
int attack_v2 = 3;

void monster_attack_init2()
{
    game_button[0] = false;
    game_button[1] = false;
    game_button[2] = false;
    game_button[3] = false;

    for (int i = 0; i < attack_sum2; i++)
    {
        int x = rand();
        double x_ = ((x % 5) + 5) * 1.0 / 10 * attack_v2;
        int y = rand();
        double y_ = ((y % 5) + 5) * 1.0 / 10 * attack_v2;

        attack_direc2[i][0] = x_;
        attack_direc2[i][1] = y_;

        attack_pos2[i][0] = bound_left1 + (bound_right1 - bound_left1) * i / attack_sum2;
        attack_pos2[i][1] = bound_top;
    }
}
void monster_attack2()
{
    for (int i = 0; i < attack_sum2; i++)
    {
        if (attack_pos2[i][0] <= bound_left1)
        {
            attack_direc2[i][0] = abs(attack_direc2[i][0]);
            attack_pos2[i][0] = bound_left1;
        }
        else if (attack_pos2[i][0] >= bound_right1)
        {
            attack_direc2[i][0] = -1 * abs(attack_direc2[i][0]);
            attack_pos2[i][0] = bound_right1;
        }

        if (attack_pos2[i][1] <= bound_top)
        {
            attack_direc2[i][1] = abs(attack_direc2[i][1]);
            attack_pos2[i][1] = bound_top;
        }
        else if (attack_pos2[i][1] >= bound_bottom)
        {
            attack_direc2[i][1] = -1 * abs(attack_direc2[i][1]);
            attack_pos2[i][1] = bound_bottom;
        }

        attack_pos2[i][0] += attack_direc2[i][0];
        attack_pos2[i][1] += attack_direc2[i][1];

        al_draw_circle(attack_pos2[i][0], attack_pos2[i][1], 3, al_map_rgb(255, 255, 255), 5.0);

        character_attack_check2(attack_pos2, attack_sum2);
    }
}

void game_scene_destroy()
{
    al_destroy_font(font);
    // al_destroy_bitmap(background);
    character_destory();
}
