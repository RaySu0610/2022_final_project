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
int dx = 10, dy = 0,scalar = 1,pos_x,pos_y;

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
        if (pos_y >= (HEIGHT*600/760 )*scalar+dy && pos_y <= (HEIGHT*655/760)*scalar+dy)
        {
            if (pos_x >= (WIDTH*70/1024 )*scalar+dx && pos_x <= (WIDTH*230/1024)*scalar+dx)
                start_inrange = true;
            else if (pos_x >= (WIDTH*290/1024)*scalar+dx && pos_x <= (WIDTH*450/1024)*scalar+dx)
                about_inrange = true;
            else if (pos_x >= (WIDTH*530/1024)*scalar+dx && pos_x <= (WIDTH*730/1024)*scalar+dx)
                setting_inrange = true;
            else if (pos_x >= (WIDTH*790/1024 )*scalar+dx && pos_x <= (WIDTH*920/1024)*scalar+dx)
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
    al_draw_scaled_bitmap(background, 0, 0, 1024, 720, 0, 0, WIDTH, HEIGHT, 0);
    if (start_inrange)
    {
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH*90/1024)*scalar + dx, (HEIGHT*600/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "Start");
        al_draw_rectangle((WIDTH*70/1024)*scalar+dx, (HEIGHT*600/760)*scalar+dy, (WIDTH*230/1024)*scalar+dx, (HEIGHT*655/760)*scalar+dy, al_map_rgb(255, 100, 100), 0);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH*90/1024)*scalar+dx, (HEIGHT*600/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "Start");
        al_draw_rectangle((WIDTH*70/1024)*scalar+dx, (HEIGHT*600/760)*scalar+dy, (WIDTH*230/1024)*scalar+dx, (HEIGHT*655/760)*scalar+dy, al_map_rgb(255, 255, 255), 0);
    }
    if (about_inrange)
    {
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH*310/1024)*scalar+dx, (HEIGHT*600/760 )*scalar+dy, ALLEGRO_ALIGN_LEFT, "About");
        al_draw_rectangle((WIDTH*290/1024)*scalar+dx, (HEIGHT*600/760)*scalar+dy, (WIDTH*450/1024)*scalar+dx, (HEIGHT*655/760)*scalar+dy, al_map_rgb(255, 100, 100), 0);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH*310/1024)*scalar+dx, (HEIGHT*600/760 )*scalar+dy, ALLEGRO_ALIGN_LEFT, "About");
        al_draw_rectangle((WIDTH*290/1024)*scalar+dx, (HEIGHT*600/760)*scalar+dy, (WIDTH*450/1024)*scalar+dx, (HEIGHT*655/760)*scalar+dy, al_map_rgb(255, 255, 255), 0);
    }

    if (setting_inrange)
    {
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH*550/1024)*scalar+dx,(HEIGHT*600/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "Setting");
        al_draw_rectangle((WIDTH*530/1024)*scalar+dx, (HEIGHT*600/760)*scalar+dy, (WIDTH*730/1024)*scalar+dx, (HEIGHT*655/760)*scalar+dy, al_map_rgb(255, 100, 100), 0);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH*550/1024)*scalar+dx, (HEIGHT*600/760 )*scalar+dy, ALLEGRO_ALIGN_LEFT, "Setting");
        al_draw_rectangle((WIDTH*530/1024)*scalar+dx, (HEIGHT*600/760)*scalar+dy, (WIDTH*730/1024)*scalar+dx, (HEIGHT*655/760)*scalar+dy, al_map_rgb(255, 255, 255), 0);
    }
    if (exit_inrange)
    {
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH*810/1024)*scalar+dx, (HEIGHT*600/760 )*scalar+dy, ALLEGRO_ALIGN_LEFT, "Exit");
        al_draw_rectangle((WIDTH*790/1024)*scalar+dx, (HEIGHT*600/760)*scalar+dy,(WIDTH*920/1024)*scalar+dx, (HEIGHT*655/760)*scalar+dy, al_map_rgb(255, 100, 100), 0);
    }
    else
    {
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH*810/1024)*scalar+dx, (HEIGHT*600/760 )*scalar+dy, ALLEGRO_ALIGN_LEFT, "Exit");
        al_draw_rectangle((WIDTH*790/1024)*scalar+dx, (HEIGHT*600/760)*scalar+dy, (WIDTH*920/1024)*scalar+dx, (HEIGHT*655/760)*scalar+dy, al_map_rgb(255, 255, 255), 0);
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

    al_draw_text(font, al_map_rgb(255, color, color), (WIDTH*40/1024)*scalar+dx, (HEIGHT*705/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "Back");
    al_draw_rectangle((WIDTH*20/1024)*scalar+dx, (HEIGHT*700/760)*scalar+dy, (WIDTH*180/1024)*scalar+dx, (HEIGHT*755/760)*scalar+dy, al_map_rgb(255, color, color), 0);
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
        if (pos_y >= (HEIGHT*700/760)*scalar+dy && pos_y <= (HEIGHT*755/760)*scalar+dy)
        {
            if (pos_x >= (WIDTH*20/1024)*scalar+dx && pos_x <= (WIDTH*180/1024)*scalar+dx)
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
    al_set_sample_instance_gain(sample_instance, (volume_value-10)/200);

    al_play_sample_instance(sample_instance);
}
void music_destroy()
{
    al_destroy_sample_instance(sample_instance);
    al_destroy_sample(song);
}

// setting func------------------------------------------------------------------------------------------------

bool Size_inrange[3]={false};
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
        if (pos_y >= (HEIGHT*260/760)*scalar+dy && pos_y <= (HEIGHT*300/760)*scalar+dy)
        {
            if (pos_x >= (WIDTH*250/1024)*scalar+dx && pos_x <= (WIDTH*(250+200)/1024)*scalar+dx)
            {
                volume_value = pos_x-WIDTH*250/1024;
                al_set_sample_instance_gain(sample_instance, (volume_value-10)/200);
            }
        }
        else if (pos_y >= (HEIGHT*445/760)*scalar+dy && pos_y <= (HEIGHT*495/760)*scalar+dy)
        {
            if (Size_inrange[0] && WIDTH!=1024)
                 screen_set(1024,760);
            else if (Size_inrange[1] && WIDTH!=1280)
                 screen_set(1280,720);
            else if (Size_inrange[2] && WIDTH!=1440)
                 screen_set(1440,900);

        }
        else
            Size_inrange[0]=false,Size_inrange[1]=false,Size_inrange[2]=false;

        //printf("%d %d\n",pos_x,pos_y);
    }
    if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        pos_x = event.mouse.x;
        pos_y = event.mouse.y;
        if (pos_y >= (HEIGHT*700/760)*scalar+dy && pos_y <= (HEIGHT*755/760)*scalar+dy)
        {
            if (pos_x >= (WIDTH*20/1024)*scalar+dx && pos_x <= (WIDTH*180/1024)*scalar+dx)
                back_inrange = true;
            else
                back_inrange = false;
        }
        else if (pos_y >= (HEIGHT*445/760)*scalar+dy && pos_y <= (HEIGHT*495/760)*scalar+dy)
        {
            if (pos_x >= (WIDTH*40/1024)*scalar+dx && pos_x <= (WIDTH*(305)/1024)*scalar+dx)
                Size_inrange[0] = true;
            else if (pos_x >= (WIDTH*370/1024)*scalar+dx && pos_x <= (WIDTH*(635)/1024)*scalar+dx)
                Size_inrange[1] = true;
            else if (pos_x >= (WIDTH*700/1024)*scalar+dx && pos_x <= (WIDTH*(959)/1024)*scalar+dx)
                Size_inrange[2] = true;
            else
                Size_inrange[0]=false,Size_inrange[1]=false,Size_inrange[2]=false;
        }
        else
            Size_inrange[0]=false,Size_inrange[1]=false,Size_inrange[2]=false,back_inrange = false;



    }

}
void setting_draw()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    if (back_inrange)
        back_draw(100);
    else
        back_draw(255);
    al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH*40/1024)*scalar+dx, (HEIGHT*250/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "Voloume");
    al_draw_rectangle((WIDTH*250/1024)*scalar+dx, (HEIGHT*280/760)*scalar+dy, (WIDTH*450/1024)*scalar+dx, (HEIGHT*280/760)*scalar+dy, al_map_rgb(255, 255, 255), 0);
    al_draw_filled_rectangle((WIDTH*(240+volume_value)/1024)*scalar+dx, (HEIGHT*260/760)*scalar+dy, (WIDTH*(250+volume_value)/1024)*scalar+dx, (HEIGHT*300/760)*scalar+dy, al_map_rgb(255, 255, 255));

    al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH*40/1024)*scalar+dx, (HEIGHT*380/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "Size");
    if(Size_inrange[0])
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH*40/1024)*scalar+dx, (HEIGHT*450/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "1024 X 760");
    else
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH*40/1024)*scalar+dx, (HEIGHT*450/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "1024 X 760");
    if(Size_inrange[1])
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH*370/1024)*scalar+dx, (HEIGHT*450/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "1280 X 720");
    else
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH*370/1024)*scalar+dx, (HEIGHT*450/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "1280 X 720");
    if(Size_inrange[2])
        al_draw_text(font, al_map_rgb(255, 100, 100), (WIDTH*700/1024)*scalar+dx, (HEIGHT*450/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "1440 X 900");
    else
        al_draw_text(font, al_map_rgb(255, 255, 255), (WIDTH*700/1024)*scalar+dx, (HEIGHT*450/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "1440 X 900");
}
void setting_destroy()
{
    al_destroy_font(font);
}

// volume func----------------------------------------------------------------------------------------------------------------------------------------
void volume_draw(int color){

    al_draw_text(font, al_map_rgb(255, color, color), (WIDTH*40/1024)*scalar+dx, (HEIGHT*250/760)*scalar+dy, ALLEGRO_ALIGN_LEFT, "Voloume");
    al_draw_rectangle((WIDTH*250/1024)*scalar+dx, (HEIGHT*280/760)*scalar+dy, (WIDTH*450/1024)*scalar+dx, (HEIGHT*280/760)*scalar+dy, al_map_rgb(255, color, color), 0);
    al_draw_filled_rectangle((WIDTH*(240+volume_value)/1024)*scalar+dx, (HEIGHT*260/760)*scalar+dy, (WIDTH*(250+volume_value)/1024)*scalar+dx, (HEIGHT*300/760)*scalar+dy, al_map_rgb(255, color, color));
}

// size reset func------------------------------------------------------------------------------------------------------------
void screen_set(int w,int h)
{
    if(al_acknowledge_resize(display))
        printf("resize call is approved\n");
    else
        printf("resize call is rejected\n");

    if(al_resize_display(display,w,h))
    {
        printf("resize success!!(%d, %d)\n",w,h);
        WIDTH = w,HEIGHT = h;
    }
    else
    {
        printf("resize failed\n");
    }

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
    al_set_sample_instance_gain(sample_instance, (volume_value-10)/200);

    al_play_sample_instance(sample_instance);
}
void game_scene_draw()
{
    al_draw_scaled_bitmap(background, 0, 0, 1024, 720, 0, 0, WIDTH, HEIGHT, 0);
    character_draw();
}
void game_scene_destroy()
{
    al_destroy_bitmap(background);
    character_destory();
}

