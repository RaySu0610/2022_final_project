#include "math.h"
#include "scene.h"

ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *attack_img[2];
ALLEGRO_FONT *font = NULL;
ALLEGRO_SAMPLE *song = NULL;
ALLEGRO_SAMPLE *attack_reflect = NULL;
ALLEGRO_SAMPLE_INSTANCE *reflect_instance[8];
ALLEGRO_SAMPLE_INSTANCE *sample_instance;

// function of menu----------------------------------------------------------------------------------------------------------

void menu_init()
{
    font = al_load_ttf_font("./font/UndertaleSans.ttf", 50, 0);
    background = al_load_bitmap("./image/menu.jpg");

    // cheating_mode = false;
    // win = false, kill = false;
    // game_scene_mode1 = 0;
    // game_scene_mode2 = 0;
    // game_scene_mode2_ = 0;
    // monster_hp = 12;
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

    al_draw_text(
        font,
        start_inrange ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 90 / 1024) * scalar + dx,
        (HEIGHT * 600 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "Start");

    al_draw_rectangle(
        (WIDTH * 70 / 1024) * scalar + dx,
        (HEIGHT * 600 / 760) * scalar + dy,
        (WIDTH * 230 / 1024) * scalar + dx,
        (HEIGHT * 655 / 760) * scalar + dy,
        start_inrange ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        0);

    al_draw_text(
        font,
        about_inrange ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 310 / 1024) * scalar + dx,
        (HEIGHT * 600 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "About");

    al_draw_rectangle(
        (WIDTH * 290 / 1024) * scalar + dx,
        (HEIGHT * 600 / 760) * scalar + dy,
        (WIDTH * 450 / 1024) * scalar + dx,
        (HEIGHT * 655 / 760) * scalar + dy,
        about_inrange ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        0);

    al_draw_text(
        font,
        setting_inrange ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 550 / 1024) * scalar + dx,
        (HEIGHT * 600 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "Setting");

    al_draw_rectangle(
        (WIDTH * 530 / 1024) * scalar + dx,
        (HEIGHT * 600 / 760) * scalar + dy,
        (WIDTH * 730 / 1024) * scalar + dx,
        (HEIGHT * 655 / 760) * scalar + dy,
        setting_inrange ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        0);

    al_draw_text(
        font,
        exit_inrange ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 810 / 1024) * scalar + dx,
        (HEIGHT * 600 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "Exit");

    al_draw_rectangle(
        (WIDTH * 790 / 1024) * scalar + dx,
        (HEIGHT * 600 / 760) * scalar + dy,
        (WIDTH * 920 / 1024) * scalar + dx,
        (HEIGHT * 655 / 760) * scalar + dy,
        exit_inrange ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        0);
}
void menu_destroy()
{
    al_destroy_font(font);
    al_destroy_bitmap(background);
}

// back button func-----------------------------------------------------------------------------------------------
void back_draw(int color)
{

    al_draw_text(
        font,
        al_map_rgb(255, color, color),
        (WIDTH * 40 / 1024) * scalar + dx,
        (HEIGHT * 705 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "Back");

    al_draw_rectangle(
        (WIDTH * 20 / 1024) * scalar + dx,
        (HEIGHT * 700 / 760) * scalar + dy,
        (WIDTH * 180 / 1024) * scalar + dx,
        (HEIGHT * 755 / 760) * scalar + dy,
        al_map_rgb(255, color, color),
        0);
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

    al_draw_text(
        font,
        al_map_rgb(255, 255, 255),
        (WIDTH * 40 / 1024) * scalar + dx,
        (HEIGHT * 250 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "Volume");

    al_draw_rectangle(
        (WIDTH * 250 / 1024) * scalar + dx,
        (HEIGHT * 280 / 760) * scalar + dy,
        (WIDTH * 450 / 1024) * scalar + dx,
        (HEIGHT * 280 / 760) * scalar + dy,
        al_map_rgb(255, 255, 255),
        0);

    al_draw_filled_rectangle(
        (WIDTH * (240 + volume_value) / 1024) * scalar + dx,
        (HEIGHT * 260 / 760) * scalar + dy,
        (WIDTH * (250 + volume_value) / 1024) * scalar + dx,
        (HEIGHT * 300 / 760) * scalar + dy,
        al_map_rgb(255, 255, 255));

    al_draw_text(
        font,
        al_map_rgb(255, 255, 255),
        (WIDTH * 40 / 1024) * scalar + dx,
        (HEIGHT * 380 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "Size");

    al_draw_text(
        font,
        Size_inrange[0] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 40 / 1024) * scalar + dx,
        (HEIGHT * 450 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "1024 X 760");

    al_draw_text(
        font,
        Size_inrange[1] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 370 / 1024) * scalar + dx,
        (HEIGHT * 450 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "1280 X 720");

    al_draw_text(
        font,
        Size_inrange[2] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 700 / 1024) * scalar + dx,
        (HEIGHT * 450 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "1440 X 900");
}
void setting_destroy()
{
    al_destroy_font(font);
}

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
/*
The format of the position is HEIGHT/WEIGHT * bound_top/bottom/left/right * scalar + dx/dy
                        or   (WIDTH/HEIGHT) * 70 / (1024/760)

*/
bool game_button[4] = {false};
bool cheating_keyword[10] = {false}; // to check each keyword was pressed
bool game_scene2_button[4] = {false};
bool game_scene4_button[2] = {false};

bool snowpiece_button = false;
bool keywords_check = false; // to check if the cheating word is pressing
int keywords_count = 0;      // to count the keyword was pressed
bool cheating_mode = false;

bool win = false, kill = false;
enum
{
    game_button_fight = 0,
    game_button_act = 1,
    game_button_item = 2,
    game_button_mercy = 3
};
int game_scene_mode1 = 0;
// 0=>初始狀態 1=>fight 2=>act 3=>item 4=>mercy

int game_scene_mode2 = 0;
// 依照game_scene_mode1的不同，定義不同
int game_scene_mode2_ = 0;
// 依照game_scene_mode2的不同，定義不同

int game_scene_counter = 0;
int game_scene_counter_end = 150;

int monster_hp = 12;

void game_scene_init()
{
    font = al_load_ttf_font("./font/UndertaleSans.ttf", 50, 0);
    character_init();

    attack_img[0] = al_load_bitmap("./image/attack01.png");
    attack_img[1] = al_load_bitmap("./image/attack02.png");
    // al_convert_mask_to_alpha(attack_img[0], al_map_rgb(255, 255, 255));
    // al_convert_mask_to_alpha(attack_img[1], al_map_rgb(255, 255, 255));

    // background = al_load_bitmap("./image/menu.jpg");
    // background = al_load_bitmap("./image/stage.jpg");

    song = al_load_sample("./sound/stronger monster.mp3");
    attack_reflect = al_load_sample("./sound/attack_reflect.wav");
    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);

    for (int num = 0; num < 8; num++) // to give each attach bullet independent sample instance
    {
        reflect_instance[num] = al_create_sample_instance(attack_reflect);
        al_set_sample_instance_playmode(reflect_instance[num], ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(reflect_instance[num], al_get_default_mixer());
        al_set_sample_instance_gain(reflect_instance[num], (volume_value) / 200);
    }
    al_restore_default_mixer();

    // //  Loop the song until the display closes

    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);

    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());

    // // set the volume of instance
    al_set_sample_instance_gain(sample_instance, (volume_value - 10) / 200);
    // al_play_sample_instance(reflect_instance);
    al_play_sample_instance(sample_instance);

    srand(time(NULL));
}
void game_scene_process(ALLEGRO_EVENT event)
{
    charater_process(event);

    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        printf("%d %d\n", pos_x, pos_y);
        if (game_button[game_button_fight] && game_scene_mode1 != 1)
        {
            game_scene_mode1 = 1;
            game_scene_mode2 = 1;
            monster_hp -= 4;
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
        if (pos_y >= (HEIGHT * 660 / 760) * scalar + dy && pos_y <= (HEIGHT * 715 / 760) * scalar + dy)
        {
            if (pos_x >= (WIDTH * 70 / 1024) * scalar + dx && pos_x <= (WIDTH * 230 / 1024) * scalar + dx)
                game_button[game_button_fight] = true;
            else if (pos_x >= (WIDTH * 320 / 1024) * scalar + dx && pos_x <= (WIDTH * 424 / 1024) * scalar + dx)
                game_button[game_button_act] = true;
            else if (pos_x >= (WIDTH * 540 / 1024) * scalar + dx && pos_x <= (WIDTH * 675 / 1024) * scalar + dx)
                game_button[game_button_item] = true;
            else if (pos_x >= (WIDTH * 790 / 1024) * scalar + dx && pos_x <= (WIDTH * 950 / 1024) * scalar + dx)
                game_button[game_button_mercy] = (true && mercy_usabled);
            else
                game_button[game_button_fight] = false, game_button[game_button_act] = false, game_button[game_button_item] = false, game_button[game_button_mercy] = false;
        }
        else
            game_button[game_button_fight] = false, game_button[game_button_act] = false, game_button[game_button_item] = false, game_button[game_button_mercy] = false;
    }

    if (game_scene_mode1 == 0)
    {
    }
    else if (game_scene_mode1 == 1) // fight
    {
        if (win || lose)
        {
            al_rest(3);
            judge_next_window = ENDING1_WINDOW;
        }
    }
    else if (game_scene_mode1 == 2) // act
    {
        if (game_scene_mode2 == 0)
        {
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                if (game_scene2_button[0])
                {
                    game_scene_mode2 = 1;
                    game_scene_mode2_ = 0;
                }
                else if (game_scene2_button[1])
                {
                    game_scene_mode2 = 2;
                    game_scene_mode2_ = 0;
                }
                else if (game_scene2_button[2])
                {
                    game_scene_mode2 = 3;
                    game_scene_mode2_ = 0;
                }
                else if (game_scene2_button[3])
                {
                    game_scene_mode2 = 4;
                    game_scene_mode2_ = 0;
                }
            }
            if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                pos_x = event.mouse.x;
                pos_y = event.mouse.y;
                if (pos_y >= (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 5) * scalar + dy && pos_y <= (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 2.5 / 5) * scalar + dy)
                {
                    if (pos_x >= (WIDTH * bound_left) * scalar + dx && pos_x <= (WIDTH * bound_left + 28 * 7) * scalar + dx)
                        game_scene2_button[0] = true; // check
                    else if (pos_x >= (WIDTH * bound_left * 5) * scalar + dx && pos_x <= (WIDTH * bound_left * 5 + 28 * 6) * scalar + dx)
                        game_scene2_button[2] = true; // talk
                    else
                    {
                        game_scene2_button[0] = false, game_scene2_button[1] = false, game_scene2_button[2] = false, game_scene2_button[3] = false;
                    }
                }
                else if (pos_y > (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 3 / 5) * scalar + dy && pos_y <= (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 4.5 / 5) * scalar + dy)
                {
                    if (pos_x >= (WIDTH * bound_left) * scalar + dx && pos_x <= (WIDTH * bound_left + 28 * 7) * scalar + dx)
                        game_scene2_button[1] = true; // devour
                    else if (pos_x >= (WIDTH * bound_left * 5) * scalar + dx && pos_x <= (WIDTH * bound_left * 5 + 28 * 7) * scalar + dx)
                        game_scene2_button[3] = true; // dinner
                    else
                    {
                        game_scene2_button[0] = false, game_scene2_button[1] = false, game_scene2_button[2] = false, game_scene2_button[3] = false;
                    }
                }
                else
                {
                    game_scene2_button[0] = false, game_scene2_button[1] = false, game_scene2_button[2] = false, game_scene2_button[3] = false;
                }
            }
        }
        else if (game_scene_mode2 == 1 || game_scene_mode2 == 4)
        {
            if (win || lose)
            {
                al_rest(3);
                judge_next_window = ENDING1_WINDOW;
            }
        }
    }
    else if (game_scene_mode1 == 3) // item
    {
        if (!cheating_mode) // if the cheating mode is off,then detect the keyboard
        {
            if (event.type == ALLEGRO_EVENT_KEY_DOWN && !keywords_check) // keywords_check is to prevent the continuous pressing on keyboard
            {
                key_state[event.keyboard.keycode] = true;
                if (keywords_count == 0 || keywords_count == 1)
                {
                    if (key_state[ALLEGRO_KEY_UP])
                    {
                        cheating_keyword[keywords_count] = true;
                        keywords_check = true;
                        keywords_count++;
                    }
                    else
                    {
                        memset(cheating_keyword, false, sizeof(bool) * 10);
                        keywords_check = true;
                        keywords_count = 0;
                    }
                }
                else if (keywords_count == 2 || keywords_count == 3)
                {
                    if (key_state[ALLEGRO_KEY_DOWN])
                    {
                        cheating_keyword[keywords_count] = true;
                        keywords_check = true;
                        keywords_count++;
                    }
                    else
                    {
                        memset(cheating_keyword, false, sizeof(bool) * 10);
                        keywords_check = true;
                        keywords_count = 0;
                    }
                }
                else if (keywords_count == 4 || keywords_count == 6)
                {
                    if (key_state[ALLEGRO_KEY_LEFT])
                    {
                        cheating_keyword[keywords_count] = true;
                        keywords_check = true;
                        keywords_count++;
                    }
                    else
                    {
                        memset(cheating_keyword, false, sizeof(bool) * 10);
                        keywords_check = true;
                        keywords_count = 0;
                    }
                }
                else if (keywords_count == 5 || keywords_count == 7)
                {
                    if (key_state[ALLEGRO_KEY_RIGHT])
                    {
                        cheating_keyword[keywords_count] = true;
                        keywords_check = true;
                        keywords_count++;
                    }
                    else
                    {
                        memset(cheating_keyword, false, sizeof(bool) * 10);
                        keywords_check = true;
                        keywords_count = 0;
                    }
                }
                else if (keywords_count == 8)
                {
                    if (key_state[ALLEGRO_KEY_A])
                    {
                        cheating_keyword[keywords_count] = true;
                        keywords_check = true;
                        keywords_count++;
                    }
                    else
                    {
                        memset(cheating_keyword, false, sizeof(bool) * 10);
                        keywords_check = true;
                        keywords_count = 0;
                    }
                }
                else if (keywords_count == 9)
                {
                    if (key_state[ALLEGRO_KEY_B])
                    {
                        cheating_keyword[keywords_count] = true;
                        keywords_check = true;
                        cheating_mode = true;
                        cheating_init();
                    }
                    else
                    {
                        memset(cheating_keyword, false, sizeof(bool) * 10);
                        keywords_check = true;
                        keywords_count = 0;
                    }
                }
            }
            else if (event.type == ALLEGRO_EVENT_KEY_UP)
            {
                key_state[event.keyboard.keycode] = false;
                keywords_check = false;
            }

            // chara.anime = 0;
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (snowpiece_button)
                recover(10);
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            pos_x = event.mouse.x;
            pos_y = event.mouse.y;

            if (pos_x >= (WIDTH * bound_left) * scalar + dx && pos_x <= (WIDTH * bound_left + 28 * 14) * scalar + dx)
            {
                if (pos_y >= (HEIGHT * 570 / 1024) * scalar + dy && pos_y <= (HEIGHT * 650 / 1024) * scalar + dy)
                    snowpiece_button = true;
                else
                    snowpiece_button = false;
            }
            else
                snowpiece_button = false;
        }
    }
    else if (game_scene_mode1 == 4) // mercy
    {
        if (game_scene_mode2 == 0)
        {
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                if (game_scene4_button[0])
                {
                    game_scene_mode2 = 1;
                }
                else if (game_scene4_button[1])
                {
                    game_scene_mode2 = 2;
                }
            }
            if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                pos_x = event.mouse.x;
                pos_y = event.mouse.y;
                if (pos_y >= (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 5) * scalar + dy && pos_y <= (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 2.5 / 5) * scalar + dy)
                {
                    if (pos_x >= (WIDTH * bound_left) * scalar + dx && pos_x <= (WIDTH * bound_left + 28 * 5) * scalar + dx)
                        game_scene4_button[0] = true; // spare
                    else
                    {
                        game_scene4_button[0] = false, game_scene4_button[1] = false;
                    }
                }
                else if (pos_y > (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 3 / 5) * scalar + dy && pos_y <= (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 4.5 / 5) * scalar + dy)
                {
                    if (pos_x >= (WIDTH * bound_left) * scalar + dx && pos_x <= (WIDTH * bound_left + 28 * 6) * scalar + dx)
                        game_scene4_button[1] = true; // escape
                    else
                    {
                        game_scene4_button[0] = false, game_scene4_button[1] = false;
                    }
                }
                else
                {
                    game_scene4_button[0] = false, game_scene4_button[1] = false;
                }
            }
        }
        else if (game_scene_mode2 == 1)
        {
            if (win)
            {
                al_rest(3);
                judge_next_window = ENDING1_WINDOW;
            }
        }
        else if (game_scene_mode2 == 2)
        {
            al_rest(3);
            judge_next_window = MENU_WINDOW;
        }
    }
}

int character_infor_draw()
{
    al_draw_text(
        font,
        al_map_rgb(255, 255, 255),
        (WIDTH * 102 / 1024) * scalar + dx,
        (HEIGHT * 600 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "Player name");

    al_draw_text(
        font,
        al_map_rgb(255, 255, 255),
        (WIDTH * 439 / 1024) * scalar + dx,
        (HEIGHT * 600 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "LV.1");

    int character_hp = get_character_hp();
    char str[50];
    sprintf(str, "HP : %d", character_hp);
    al_draw_text(
        font,
        al_map_rgb(255, 255, 255),
        (WIDTH * 714 / 1024) * scalar + dx,
        (HEIGHT * 600 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        str);
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
int hurt_time = 0;
void game_scene_draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    if (hurt_time < 3 || monster_hp >= 0)
        monster_draw();
    game_button_draw();

    if (game_scene_mode1 == 0)
    {
        al_draw_rectangle( //邊框
            (WIDTH * bound_left) * scalar + dx,
            (HEIGHT * bound_top) * scalar + dy,
            (WIDTH * bound_right) * scalar + dx,
            (HEIGHT * bound_bottom) * scalar + dy,
            al_map_rgb(255, 255, 255),
            0);

        al_draw_text(
            font,
            al_map_rgb(255, 255, 255),
            (WIDTH * bound_left + 3) * scalar + dx,
            (HEIGHT * bound_top + HEIGHT * 70 / 760) * scalar + dy,
            ALLEGRO_ALIGN_LEFT,
            "  Vegetoid came out of the earth!");

        character_infor_draw();
    }
    else if (game_scene_mode1 == 1) //----------------------------------------------------------------------------------------fight page
    {
        if (game_scene_mode2 == 1)
        {
            monster_hurt = 1;
            if (game_scene_counter == 0)
            {
                monster_anime = 0;
                printf("*");
            }
            character_infor_draw();

            al_draw_rectangle( //邊框
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * bound_top) * scalar + dy,
                (WIDTH * bound_right) * scalar + dx,
                (HEIGHT * bound_bottom) * scalar + dy,
                al_map_rgb(255, 255, 255),
                0);

            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + 10) * scalar + dx,
                (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 5) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "* You attack the Vegetoid.");

            char str[50];
            sprintf(str, "* Vegetoid HP %d -> HP %d.", monster_hp + 4, monster_hp);

            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + 10) * scalar + dx,
                (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 3 / 5) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                str); //要給實際參數值

            game_scene_counter++;
            if (game_scene_counter >= game_scene_counter_end / 2)
                monster_hurt = 2;
            if (game_scene_counter == game_scene_counter_end)
            {
                hurt_time++;
                printf("hurt_time=%d\n", hurt_time);
                monster_hurt = 0;
                game_scene_counter = 0;
                if (monster_hp > 0)
                {
                    game_scene_mode1 = 1;
                    game_scene_mode2 = 3;

                    monster_attack_init2();
                }
                else
                {
                    game_scene_mode1 = 1;
                    game_scene_mode2 = 2;
                }
            }
        }
        else if (game_scene_mode2 == 2)
        {
            character_infor_draw();

            al_draw_rectangle( //邊框
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * bound_top) * scalar + dy,
                (WIDTH * bound_right) * scalar + dx,
                (HEIGHT * bound_bottom) * scalar + dy,
                al_map_rgb(255, 255, 255),
                0);
            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 3) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "* You WIN!");
            win = true;
            kill = true;
        }
        else if (game_scene_mode2 == 3)
        {
            character_draw();
            character_infor_draw();

            al_draw_rectangle( //邊框
                (WIDTH * bound_left1) * scalar + dx,
                (HEIGHT * bound_top) * scalar + dy,
                (WIDTH * bound_right1) * scalar + dx,
                (HEIGHT * bound_bottom) * scalar + dy,
                al_map_rgb(255, 255, 255),
                0);

            monster_attack2();
            if (lose)
            {
                failed_draw();
                al_rest(3);
            }
            game_scene_counter++;
            if (game_scene_counter == 500)
            {
                game_scene_counter = 0;
                game_scene_mode1 = 0;
                game_scene_mode2 = 0;
            }
        }
    }
    else if (game_scene_mode1 == 2) //---------------------------------------------------------------------------------act page
    {
        if (game_scene_mode2 == 0)
        {
            character_infor_draw();

            al_draw_rectangle( //邊框
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * bound_top) * scalar + dy,
                (WIDTH * bound_right) * scalar + dx,
                (HEIGHT * bound_bottom) * scalar + dy,
                al_map_rgb(255, 255, 255),
                0);

            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + 10) * scalar + dx,
                (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 5) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "* Check.");
            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + 10) * scalar + dx,
                (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 3 / 5) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "* Devour.");
            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                (WIDTH * bound_left * 5) * scalar + dx,
                (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 5) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "* Talk.");
            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                (WIDTH * bound_left * 5) * scalar + dx,
                (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 3 / 5) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "* Dinner.");

            if (game_scene2_button[0]) // check
            {
                al_draw_filled_rectangle(
                    (WIDTH * bound_left + 28 * 1.5) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 2 / 5 + 3) * scalar + dy,
                    (WIDTH * bound_left + 28 * 6.5) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 2 / 5 + 5) * scalar + dy,
                    al_map_rgb(255, 255, 255));
            }
            else if (game_scene2_button[1]) // devour
            {
                al_draw_filled_rectangle(
                    (WIDTH * bound_left + 28 * 1.5) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 4 / 5 + 3) * scalar + dy,
                    (WIDTH * bound_left + 28 * 7.5) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 4 / 5 + 5) * scalar + dy,
                    al_map_rgb(255, 255, 255));
            }
            else if (game_scene2_button[2]) // talk
            {
                al_draw_filled_rectangle(
                    (WIDTH * bound_left * 5 + 28 * 1.5) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 2 / 5 + 3) * scalar + dy,
                    (WIDTH * bound_left * 5 + 28 * 5.5) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 2 / 5 + 5) * scalar + dy,
                    al_map_rgb(255, 255, 255));
            }
            else if (game_scene2_button[3]) // dinner
            {
                al_draw_filled_rectangle(
                    (WIDTH * bound_left * 5 + 28 * 1.5) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 4 / 5 + 3) * scalar + dy,
                    (WIDTH * bound_left * 5 + 28 * 7.0) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 4 / 5 + 5) * scalar + dy,
                    al_map_rgb(255, 255, 255));
            }
        }
        else if (game_scene_mode2 == 1) // check
        {
            game_scene2_button[0] = false;
            character_infor_draw();

            if (game_scene_mode2_ == 0)
            {
                al_draw_rectangle( //邊框
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top) * scalar + dy,
                    (WIDTH * bound_right) * scalar + dx,
                    (HEIGHT * bound_bottom) * scalar + dy,
                    al_map_rgb(255, 255, 255),
                    0);

                char str[50];
                sprintf(str, "* Vegetoid -ATK 3 -HP%d.", monster_hp);

                al_draw_text(
                    font,
                    al_map_rgb(255, 255, 255),
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 5) * scalar + dy,
                    ALLEGRO_ALIGN_LEFT,
                    str);

                game_scene_counter++;
                if (game_scene_counter == game_scene_counter_end)
                {
                    game_scene_counter = 0;

                    game_scene_mode1 = 2;
                    game_scene_mode2 = 1;
                    game_scene_mode2_ = 1;
                    monster_attack_init1();
                }
            }
            else if (game_scene_mode2_ == 1)
            {
                character_draw();
                character_infor_draw();

                al_draw_rectangle( //邊框
                    (WIDTH * bound_left1) * scalar + dx,
                    (HEIGHT * bound_top) * scalar + dy,
                    (WIDTH * bound_right1) * scalar + dx,
                    (HEIGHT * bound_bottom) * scalar + dy,
                    al_map_rgb(255, 255, 255),
                    0);

                monster_attack1();
                if (lose)
                {
                    failed_draw();
                    al_rest(3);
                }
                game_scene_counter++;
                if (game_scene_counter == 500)
                {
                    game_scene_counter = 0;
                    game_scene_mode1 = 2;
                    game_scene_mode2 = 1;
                    game_scene_mode2_ = 2;
                }
            }
            else if (game_scene_mode2_ == 2)
            {
                al_draw_rectangle( //邊框
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top) * scalar + dy,
                    (WIDTH * bound_right) * scalar + dx,
                    (HEIGHT * bound_bottom) * scalar + dy,
                    al_map_rgb(255, 255, 255),
                    0);

                al_draw_text(
                    font,
                    al_map_rgb(255, 255, 255),
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 5) * scalar + dy,
                    ALLEGRO_ALIGN_LEFT,
                    "* Vegetoid gave a mysterious");
                al_draw_text(
                    font,
                    al_map_rgb(255, 255, 255),
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 3 / 5) * scalar + dy,
                    ALLEGRO_ALIGN_LEFT,
                    "  smile");

                game_scene_counter++;
                if (game_scene_counter == game_scene_counter_end)
                {
                    game_scene_counter = 0;

                    game_scene_mode1 = 0;
                    game_scene_mode2 = 0;
                    game_scene_mode2_ = 0;
                }
            }
        }
        else if (game_scene_mode2 == 2) // devour
        {
            if (game_scene_mode2_ == 0)
            {
                al_draw_rectangle( //邊框
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top) * scalar + dy,
                    (WIDTH * bound_right) * scalar + dx,
                    (HEIGHT * bound_bottom) * scalar + dy,
                    al_map_rgb(255, 255, 255),
                    0);

                al_draw_text(
                    font,
                    al_map_rgb(255, 255, 255),
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 5) * scalar + dy,
                    ALLEGRO_ALIGN_LEFT,
                    "* You tried to eat Vegetoid");
                al_draw_text(
                    font,
                    al_map_rgb(255, 255, 255),
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 3 / 5) * scalar + dy,
                    ALLEGRO_ALIGN_LEFT,
                    "  but it wasn't weakened enough.");

                game_scene_counter++;
                if (game_scene_counter == game_scene_counter_end)
                {
                    game_scene_counter = 0;

                    game_scene_mode1 = 2;
                    game_scene_mode2 = 2;
                    game_scene_mode2_ = 1;
                    monster_attack_init2();
                }
            }
            else if (game_scene_mode2_ == 1)
            {
                character_draw();
                character_infor_draw();

                al_draw_rectangle( //邊框
                    (WIDTH * bound_left1) * scalar + dx,
                    (HEIGHT * bound_top) * scalar + dy,
                    (WIDTH * bound_right1) * scalar + dx,
                    (HEIGHT * bound_bottom) * scalar + dy,
                    al_map_rgb(255, 255, 255),
                    0);

                monster_attack2();
                if (lose)
                {
                    failed_draw();
                    al_rest(3);
                }
                game_scene_counter++;
                if (game_scene_counter == 500)
                {
                    game_scene_counter = 0;
                    game_scene_mode1 = 2;
                    game_scene_mode2 = 2;
                    game_scene_mode2_ = 2;
                }
            }
            else if (game_scene_mode2_ == 2)
            {
                al_draw_rectangle( //邊框
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top) * scalar + dy,
                    (WIDTH * bound_right) * scalar + dx,
                    (HEIGHT * bound_bottom) * scalar + dy,
                    al_map_rgb(255, 255, 255),
                    0);

                al_draw_text(
                    font,
                    al_map_rgb(255, 255, 255),
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 5) * scalar + dy,
                    ALLEGRO_ALIGN_LEFT,
                    "* It smells like steamed");
                al_draw_text(
                    font,
                    al_map_rgb(255, 255, 255),
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 3 / 5) * scalar + dy,
                    ALLEGRO_ALIGN_LEFT,
                    "  carrots and peas.");

                game_scene_counter++;
                if (game_scene_counter == game_scene_counter_end)
                {
                    game_scene_counter = 0;

                    game_scene_mode1 = 0;
                    game_scene_mode2 = 0;
                    game_scene_mode2_ = 0;
                }
            }
        }
        else if (game_scene_mode2 == 3) // talk
        {
        }
        else if (game_scene_mode2 == 4) // dinner
        {
            game_scene2_button[3] = false;
            character_infor_draw();

            if (game_scene_mode2_ == 0)
            {
                al_draw_rectangle( //邊框
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top) * scalar + dy,
                    (WIDTH * bound_right) * scalar + dx,
                    (HEIGHT * bound_bottom) * scalar + dy,
                    al_map_rgb(255, 255, 255),
                    0);

                al_draw_text(
                    font,
                    al_map_rgb(255, 255, 255),
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 5) * scalar + dy,
                    ALLEGRO_ALIGN_LEFT,
                    "* You pat your stomach");
                al_draw_text(
                    font,
                    al_map_rgb(255, 255, 255),
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 3 / 5) * scalar + dy,
                    ALLEGRO_ALIGN_LEFT,
                    "* Vegetoid offers a healthy meal");

                game_scene_counter++;
                if (game_scene_counter == game_scene_counter_end)
                {
                    game_scene_counter = 0;

                    game_scene_mode1 = 2;
                    game_scene_mode2 = 4;
                    game_scene_mode2_ = 1;
                    monster_attack_init3();
                }
            }
            else if (game_scene_mode2_ == 1)
            {
                character_draw();
                character_infor_draw();

                al_draw_rectangle( //邊框
                    (WIDTH * bound_left1) * scalar + dx,
                    (HEIGHT * bound_top) * scalar + dy,
                    (WIDTH * bound_right1) * scalar + dx,
                    (HEIGHT * bound_bottom) * scalar + dy,
                    al_map_rgb(255, 255, 255),
                    0);

                monster_attack3();
                if (lose)
                {
                    failed_draw();
                    al_rest(3);
                }
                game_scene_counter++;
                if (game_scene_counter == 500)
                {
                    game_scene_counter = 0;
                    game_scene_mode1 = 2;
                    game_scene_mode2 = 4;
                    game_scene_mode2_ = 2;
                }
            }
            else if (game_scene_mode2_ == 2)
            {
                al_draw_rectangle( //邊框
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top) * scalar + dy,
                    (WIDTH * bound_right) * scalar + dx,
                    (HEIGHT * bound_bottom) * scalar + dy,
                    al_map_rgb(255, 255, 255),
                    0);

                al_draw_text(
                    font,
                    al_map_rgb(255, 255, 255),
                    (WIDTH * bound_left) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 5) * scalar + dy,
                    ALLEGRO_ALIGN_LEFT,
                    "* Vegetoid's here for your health");

                game_scene_counter++;
                if (game_scene_counter == game_scene_counter_end)
                {
                    game_scene_counter = 0;

                    game_scene_mode1 = 0;
                    game_scene_mode2 = 0;
                    game_scene_mode2_ = 0;
                }
            }
        }
    }
    else if (game_scene_mode1 == 3) //----------------------------------------------------------------------------------item page
    {
        if (game_scene_mode2 == 0)
        {
            character_infor_draw();
            al_draw_rectangle( //邊框
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * bound_top) * scalar + dy,
                (WIDTH * bound_right) * scalar + dx,
                (HEIGHT * bound_bottom) * scalar + dy,
                al_map_rgb(255, 255, 255),
                0);
            al_draw_text(
                font,
                snowpiece_button ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * 570 / 1024) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                " * Snowman piece");
            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + WIDTH * 10 / 1024) * scalar + dx,
                (HEIGHT * 670 / 1024) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "cheating : ");
            al_draw_text(
                font,
                cheating_keyword[0] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + WIDTH * (28 * 9 - 4) / 1024) * scalar + dx,
                (HEIGHT * 670 / 1024) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "U");
            al_draw_text(
                font,
                cheating_keyword[1] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + WIDTH * (28 * 10 - 2) / 1024) * scalar + dx,
                (HEIGHT * 670 / 1024) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "U");
            al_draw_text(
                font,
                cheating_keyword[2] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + WIDTH * (28 * 11) / 1024) * scalar + dx,
                (HEIGHT * 670 / 1024) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "D");
            al_draw_text(
                font,
                cheating_keyword[3] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + WIDTH * (28 * 12) / 1024) * scalar + dx,
                (HEIGHT * 670 / 1024) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "D");
            al_draw_text(
                font,
                cheating_keyword[4] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + WIDTH * (28 * 13) / 1024) * scalar + dx,
                (HEIGHT * 670 / 1024) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "L");
            al_draw_text(
                font,
                cheating_keyword[5] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + WIDTH * (28 * 14 - 2) / 1024) * scalar + dx,
                (HEIGHT * 670 / 1024) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "R");
            al_draw_text(
                font,
                cheating_keyword[6] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + WIDTH * (28 * 15 - 2) / 1024) * scalar + dx,
                (HEIGHT * 670 / 1024) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "L");
            al_draw_text(
                font,
                cheating_keyword[7] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + WIDTH * (28 * 16 - 3) / 1024) * scalar + dx,
                (HEIGHT * 670 / 1024) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "R");
            al_draw_text(
                font,
                cheating_keyword[8] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + WIDTH * (28 * 17 - 5) / 1024) * scalar + dx,
                (HEIGHT * 670 / 1024) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "A");
            al_draw_text(
                font,
                cheating_keyword[9] ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
                (WIDTH * bound_left + WIDTH * (28 * 18 - 2) / 1024) * scalar + dx,
                (HEIGHT * 670 / 1024) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "B");
        }
    }
    else if (game_scene_mode1 == 4) //----------------------------------------------------------------------------------mercy page
    {
        if (game_scene_mode2 == 0)
        {
            character_infor_draw();

            al_draw_rectangle( //邊框
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * bound_top) * scalar + dy,
                (WIDTH * bound_right) * scalar + dx,
                (HEIGHT * bound_bottom) * scalar + dy,
                al_map_rgb(255, 255, 255),
                0);

            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 5) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "* Spare.");
            // printf("spare show\n");
            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 3 / 5) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "* Escape.");
            // printf("escape show\n");
            if (game_scene4_button[0]) // Spare
            {
                al_draw_filled_rectangle(
                    (WIDTH * bound_left + 28 * 1.5) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 2 / 5 + 3) * scalar + dy,
                    (WIDTH * bound_left + 28 * 6.5) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 2 / 5 + 5) * scalar + dy,
                    al_map_rgb(255, 255, 255));
                // printf("cursor on spare\n");
            }
            else if (game_scene4_button[1]) // Escape
            {
                al_draw_filled_rectangle(
                    (WIDTH * bound_left + 28 * 1.5) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 4 / 5 + 3) * scalar + dy,
                    (WIDTH * bound_left + 28 * 7.5) * scalar + dx,
                    (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 4 / 5 + 5) * scalar + dy,
                    al_map_rgb(255, 255, 255));
                // printf("cursor on escape\n");
            }
        }
        else if (game_scene_mode2 == 1)
        {
            character_infor_draw();

            al_draw_rectangle( //邊框
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * bound_top) * scalar + dy,
                (WIDTH * bound_right) * scalar + dx,
                (HEIGHT * bound_bottom) * scalar + dy,
                al_map_rgb(255, 255, 255),
                0);
            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 3) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "* You WIN!");
            win = true;
        }
        else if (game_scene_mode2 == 2)
        {
            character_infor_draw();

            al_draw_rectangle( //邊框
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * bound_top) * scalar + dy,
                (WIDTH * bound_right) * scalar + dx,
                (HEIGHT * bound_bottom) * scalar + dy,
                al_map_rgb(255, 255, 255),
                0);
            al_draw_text(
                font,
                al_map_rgb(255, 255, 255),
                (WIDTH * bound_left) * scalar + dx,
                (HEIGHT * bound_top + HEIGHT * (bound_bottom - bound_top) * 1 / 3) * scalar + dy,
                ALLEGRO_ALIGN_LEFT,
                "* You escaped...");
        }
    }

    // al_draw_scaled_bitmap(background, 0, 0, WIDTH, 720, 0, 0, WIDTH, HEIGHT, 0);
}

void failed_draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    character_draw();
    al_stop_sample_instance(sample_instance);
}

//一般攻擊1
int attack_sum1 = 8;
int attack_pos1[8][2];
int attack_direc1[8][2];
int attack_v1 = 3;
void monster_attack_init1()
{
    for (int i = 0; i < attack_sum1; i++)
    {
        int x = rand();
        double x_ = WIDTH * bound_left1 + ((x % 301)) * 1.0 / 300 * WIDTH * (bound_right1 - bound_left1);
        // int y = rand();
        // double y_ = ((y % 11) + 10) * 1.0 / 20 * attack_v1;
        int y_ = ((i + 1) * 1.0 / 2);
        if (y_ == 0)
        {
            y_ = 1;
        }

        // attack_direc1[i][0] = x_;
        attack_direc1[i][1] = y_;

        attack_pos1[i][0] = x_;
        attack_pos1[i][1] = HEIGHT * bound_top - attack_direc1[i][1] * 5;
    }
}
void monster_attack1()
{
    for (int i = 0; i < attack_sum1; i++)
    {
        attack_pos1[i][1] += attack_direc1[i][1];
        if (attack_pos1[i][1] >= HEIGHT * bound_bottom * scalar + dy - 3)
        {
            int x = rand();
            double x_ = WIDTH * bound_left1 + 3 + ((x % 301)) * 1.0 / 300 * WIDTH * (bound_right1 - bound_left1);
            attack_pos1[i][0] = x_ + dx;
            attack_pos1[i][1] = HEIGHT * bound_top; //+ attack_direc1[i][1] * 5
        }

        int r = 3;
        // al_draw_circle(attack_pos1[i][0], attack_pos1[i][1], r, al_map_rgb(255, 255, 255), 5.0);
        al_draw_scaled_bitmap(attack_img[0], 0, 0, 1024, 760, attack_pos1[i][0], attack_pos1[i][1], attack_pos1[i][0] + r, attack_pos1[i][1] + r, 0);

        character_attack_check1(attack_pos1, attack_sum1);
    }
}

//一般攻擊2
int attack_sum2 = 8;
int attack_pos2[8][2];
int attack_direc2[8][2];
int attack_v2 = 3;

void monster_attack_init2()
{
    for (int i = 0; i < attack_sum2; i++)
    {
        int x = rand();
        double x_ = ((x % 6) + 5) * 1.0 / 10 * attack_v2;
        int y = rand();
        double y_ = ((y % 6) + 5) * 1.0 / 10 * attack_v2;

        attack_direc2[i][0] = x_;
        attack_direc2[i][1] = y_;

        attack_pos2[i][0] = WIDTH * bound_left1 + WIDTH * (bound_right1 - bound_left1) * i / attack_sum2;
        attack_pos2[i][1] = HEIGHT * bound_top;
    }
}
void monster_attack2()
{
    for (int i = 0; i < attack_sum2; i++)
    {
        attack_pos2[i][0] += attack_direc2[i][0];
        attack_pos2[i][1] += attack_direc2[i][1];

        if (attack_pos2[i][0] <= WIDTH * bound_left1 * scalar + dx) // 3 is the radius of attack
        {
            attack_direc2[i][0] = -(attack_direc2[i][0]);
            // printf("%d\n",attack_direc2[i][0]);
            attack_pos2[i][0] = WIDTH * bound_left1 * scalar + dx;
            al_play_sample_instance(reflect_instance[i]);
        }
        else if (attack_pos2[i][0] >= WIDTH * bound_right1 * scalar + dx - 30)
        {
            attack_direc2[i][0] = -(attack_direc2[i][0]);
            // printf("%d\n",attack_direc2[i][0]);
            attack_pos2[i][0] = WIDTH * bound_right1 * scalar + dx - 30;
            al_play_sample_instance(reflect_instance[i]);
        }

        if (attack_pos2[i][1] <= HEIGHT * bound_top * scalar + dy)
        {
            attack_direc2[i][1] = abs(attack_direc2[i][1]);
            attack_pos2[i][1] = HEIGHT * bound_top * scalar + dy;
            al_play_sample_instance(reflect_instance[i]);
        }
        else if (attack_pos2[i][1] >= HEIGHT * bound_bottom * scalar + dy - 45)
        {
            attack_direc2[i][1] = -1 * abs(attack_direc2[i][1]);
            attack_pos2[i][1] = HEIGHT * bound_bottom * scalar + dy - 45;
            al_play_sample_instance(reflect_instance[i]);
        }

        int r = 3;
        // al_draw_circle(attack_pos2[i][0], attack_pos2[i][1], r, al_map_rgb(255, 255, 255), 5.0);
        // al_draw_circle(attack_pos2[i][0], attack_pos2[i][1], 3, al_map_rgb(255, 255, 255), 5.0);

        // al_draw_scaled_bitmap(attack_img[0], 0, 0, 1024, 760, attack_pos2[i][0], attack_pos2[i][1], attack_pos2[i][0] + r, attack_pos2[i][1] + r, 0);
        // al_draw_rotated_bitmap(attack_img[0], 0, 0, attack_pos2[i][0] + r, attack_pos2[i][1] + r, acos(1.0 * attack_pos2[i][0] / attack_pos2[i][1]), 0);

        // al_draw_rotated_bitmap(attack_img[0], 0, 0, attack_pos2[i][0], attack_pos2[i][1], 0, 0);

        al_draw_scaled_bitmap(attack_img[0], 0, 0, 1024, 760, attack_pos2[i][0], attack_pos2[i][1], attack_pos2[i][0] + r, attack_pos2[i][1] + r, 0);

        character_attack_check2(attack_pos2, attack_sum2);
    }
}

//一般攻擊3
int attack_sum3 = 8;
int attack_pos3[8][2];
int attack_direc3[8][2];
int attack_v3 = 3;

void monster_attack_init3()
{
    for (int i = 0; i < attack_sum3; i++)
    {
        int x = rand();
        double x_ = ((x % 6) + 5) * 1.0 / 10 * attack_v3;
        int y = rand();
        double y_ = ((y % 6) + 5) * 1.0 / 10 * attack_v3;

        attack_direc3[i][0] = x_;
        attack_direc3[i][1] = y_;

        attack_pos3[i][0] = WIDTH * bound_left1 + WIDTH * (bound_right1 - bound_left1) * i / attack_sum3;
        attack_pos3[i][1] = HEIGHT * bound_top;
    }
}
void monster_attack3()
{
    for (int i = 0; i < attack_sum3; i++)
    {
        attack_pos3[i][0] += attack_direc3[i][0];
        attack_pos3[i][1] += attack_direc3[i][1];

        if (attack_pos3[i][0] <= WIDTH * bound_left1 * scalar + dx) // 3 is the radius of attack
        {
            attack_direc3[i][0] = -(attack_direc3[i][0]);
            // printf("%d\n",attack_direc3[i][0]);
            attack_pos3[i][0] = WIDTH * bound_left1 * scalar + dx;
            al_play_sample_instance(reflect_instance[i]);
        }
        else if (attack_pos3[i][0] >= WIDTH * bound_right1 * scalar + dx - 30)
        {
            attack_direc3[i][0] = -(attack_direc3[i][0]);
            // printf("%d\n",attack_direc3[i][0]);
            attack_pos3[i][0] = WIDTH * bound_right1 * scalar + dx - 30;
            al_play_sample_instance(reflect_instance[i]);
        }

        if (attack_pos3[i][1] <= HEIGHT * bound_top * scalar + dy)
        {
            attack_direc3[i][1] = abs(attack_direc3[i][1]);
            attack_pos3[i][1] = HEIGHT * bound_top * scalar + dy;
            al_play_sample_instance(reflect_instance[i]);
        }
        else if (attack_pos3[i][1] >= HEIGHT * bound_bottom * scalar + dy - 45)
        {
            attack_direc3[i][1] = -1 * abs(attack_direc3[i][1]);
            attack_pos3[i][1] = HEIGHT * bound_bottom * scalar + dy - 45;
            al_play_sample_instance(reflect_instance[i]);
        }

        int r = 3;
        // al_draw_circle(attack_pos3[i][0] + r * 2, attack_pos3[i][1] + r * 2, r,
        //                i == 0 ? al_map_rgb(0, 255, 0) : al_map_rgb(255, 255, 255), 5.0);
        // al_draw_circle(attack_pos3[i][0], attack_pos3[i][1], 3,
        //                i == 0 ? al_map_rgb(0, 255, 0) : al_map_rgb(255, 255, 255), 5.0);

        // al_draw_rotated_bitmap(
        //     i == 0 ? attack_img[1] : attack_img[0],
        //     0, 0, attack_pos3[i][0], attack_pos3[i][1], 0, 0);
        al_draw_scaled_bitmap(
            i == 0 ? attack_img[1] : attack_img[0],
            0, 0, 1024, 760, attack_pos3[i][0], attack_pos3[i][1], attack_pos3[i][0] + r, attack_pos3[i][1] + r, 0);

        character_attack_check3(attack_pos3, attack_sum3);
    }
}

void game_scene_destroy()
{
    al_destroy_font(font);
    // al_destroy_bitmap(background);
    music_destroy();
    for (int num = 0; num < 8; num++)
        al_destroy_sample_instance(reflect_instance[num]);
    al_destroy_sample(attack_reflect);
    character_destory();
    monster_destroy();
}
// --------------------------------------------------------------------- endin01
bool back_menu_button = false, exit_button = false;
void ending1_init()
{
    font = al_load_ttf_font("./font/UndertaleSans.ttf", 50, 0);

    if (win)
    {
        if (kill)
        {
            background = al_load_bitmap("./image/killing_ending.png");
            song = al_load_sample("./sound/killing ending.mp3");
        }
        else
        {
            background = al_load_bitmap("./image/peace_ending.jpg");
            song = al_load_sample("./sound/A Peace Ending.mp3");
        }
    }
    else
    {
        background = al_load_bitmap("./image/Ending01.jpg");
        song = al_load_sample("./sound/failing ending.mp3");
    }

    sample_instance = al_create_sample_instance(song);
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    al_set_sample_instance_gain(sample_instance, (volume_value - 10) / 200);
    // al_play_sample_instance(reflect_instance);
    al_play_sample_instance(sample_instance);
}

void ending1_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (back_menu_button)
        {
            judge_next_window = MENU_WINDOW;
            back_menu_button = false;

            cheating_mode = false;
            win = false, kill = false;
            game_scene_mode1 = 0;
            game_scene_mode2 = 0;
            game_scene_mode2_ = 0;
            monster_hp = 12;
            character_hp_reset();
        }
        else if (exit_button)
        {
            judge_next_window = EXIT_WINDOW;
            exit_button = false;
        }
    }
    if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        pos_x = event.mouse.x;
        pos_y = event.mouse.y;
        if (pos_x >= (WIDTH * 350 / 1024) * scalar + dx && pos_x <= (WIDTH * 650 / 1024) * scalar + dx)
        {
            if (pos_y >= (HEIGHT * 500 / 760) * scalar + dy && pos_y <= (HEIGHT * 555 / 760) * scalar + dy)
                back_menu_button = true;
            else if (pos_y >= (HEIGHT * 600 / 760) * scalar + dy && pos_y <= (HEIGHT * 655 / 760) * scalar + dy)
                exit_button = true;
            else
                back_menu_button = false, exit_button = false;
        }
        else
            back_menu_button = false, exit_button = false;
    }
}
void ending1_draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    if (win)
    {
        if (kill)
            al_draw_scaled_bitmap(background, 0, 0, 244, 207, 300, 50, 244 * 2, 207 * 2, 0);
        else
            al_draw_bitmap(background, 250, 100, 0);
    }
    else
        al_draw_scaled_bitmap(background, 0, 0, 1080, 720, 0, 0, WIDTH, HEIGHT, 0);

    al_draw_text(
        font,
        (back_menu_button) ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 370 / 1024) * scalar + dx,
        (HEIGHT * 505 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "Back to menu");
    al_draw_rectangle(
        (WIDTH * 350 / 1024) * scalar + dx,
        (HEIGHT * 500 / 760) * scalar + dy,
        (WIDTH * 700 / 1024) * scalar + dx,
        (HEIGHT * 555 / 760) * scalar + dy,
        (back_menu_button) ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        0);
    al_draw_text(
        font,
        (exit_button) ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        (WIDTH * 370 / 1024) * scalar + dx,
        (HEIGHT * 605 / 760) * scalar + dy,
        ALLEGRO_ALIGN_LEFT,
        "Exit the game");

    al_draw_rectangle(
        (WIDTH * 350 / 1024) * scalar + dx,
        (HEIGHT * 600 / 760) * scalar + dy,
        (WIDTH * 700 / 1024) * scalar + dx,
        (HEIGHT * 655 / 760) * scalar + dy,
        (exit_button) ? al_map_rgb(255, 100, 100) : al_map_rgb(255, 255, 255),
        0);
}
void ending1_destroy()
{
    al_destroy_font(font);
    al_destroy_bitmap(background);
    music_destroy();
}

void ending2_init();
void ending2_process(ALLEGRO_EVENT event);
void ending2_draw();
void ending2_destroy();
