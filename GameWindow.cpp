#include "GameWindow.h"
/*
editor: Kuo
change parts: menu interface
             ,beginning animation
             ,about interface -> scene.cpp line 146
             ,setting interface -> scene.cpp line 206

notice:

1. press 'Esc' button to skip the video
2. The content of about interface is not finished yet
3. 'Start', 'About' and 'Back' button was finish, you can press 'About' button into about interface and press 'Back' button back to menu interface.
   'Setting' and 'Quit' are also finished
4. I changed the variable 'judge_next_window' to int type, to identify which window we want to replace with
5. the variable 'window' value's meaning:
    1 -> menu
    2 -> game_scene
    3 -> about
    4 -> setting
    5 -> exit(directly close the program)
6. I also isolate the menu music so that it would not replay if we back to the menu.you can check the function in scene.cpp line 186

*/

/*
#define MENU_WINDOW 1;
#define GAME_SCENE_WINDOW 2;
#define ABOUT_WINDOW 3;
#define SETTING_WINDOW 4;
#define EXIT_WINDOW 5;
*/

bool draw = false;
int window = 1;

const char *title = "Final Project 10xxxxxxx";

// ALLEGRO Variables
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_VIDEO *video;
ALLEGRO_FONT *font_ = NULL;

int Game_establish()
{
    int msg = 0;

    animation();

    game_init();
    game_begin();

    while (msg != GAME_TERMINATE)
    {
        msg = game_run();
        // al_rest(0.1);
        if (msg == GAME_TERMINATE)
            printf("Game Over\n");
    }

    game_destroy();
    return 0;
}

void video_display(ALLEGRO_VIDEO *video)
{
    ALLEGRO_BITMAP *frame = al_get_video_frame(video);
    // check if we get the frame successfully
    // Note the this code is necessary
    if (!frame)
        return;
    // Display the frame.
    // rescale the frame into the size of screen
    al_draw_scaled_bitmap(frame,
                          // the rescale position of the frame
                          0, 0,
                          // the width and height you want to rescale
                          al_get_bitmap_width(frame),
                          al_get_bitmap_height(frame),
                          // the position of result image
                          0, 0,
                          // the width and height of result image
                          al_get_display_width(display),
                          al_get_display_height(display), 0);
    al_flip_display();
}
void init_video()
{
    al_init();
    al_init_video_addon();
    al_install_audio();
    al_install_keyboard();
    fps = al_create_timer(1.0 / FPS);
    // al_set_new_display_flags(ALLEGRO_RESIZABLE);
    // al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    display = al_create_display(1024, 760);
    // linear interpolation for scaling images
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    char filename[50] = "animation.ogv";
    printf("reading video.....\n");
    video = al_open_video(filename);
    if (video)
        printf("read video succeed\n");
    else
        printf("read video fail!!!!\n");
    queue = al_create_event_queue();
    // register video event
    ALLEGRO_EVENT_SOURCE *temp = al_get_video_event_source(video);
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, temp);
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(fps));
}
void video_begin()
{
    al_reserve_samples(1);
    al_start_video(video, al_get_default_mixer());
    al_start_timer(fps);
}
void animation()
{
    // font_ = al_load_ttf_font("./font/UndertaleSans.ttf", 50, 0);

    ALLEGRO_EVENT event;
    init_video();
    video_begin();
    while (1)
    {
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            video_display(video);
            // al_draw_text(font_, al_map_rgb(255, 100, 100), 90, HEIGHT / 2 + 220, ALLEGRO_ALIGN_LEFT, "Start");
            // al_draw_rectangle(70, 600, 230, 655, al_map_rgb(255, 100, 100), 0);
        }
        else if ((event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) || (event.type == ALLEGRO_EVENT_KEY_UP && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE))
        {
            al_close_video(video);
            break;
        }
        else if (event.type == ALLEGRO_EVENT_VIDEO_FINISHED)
        {
            break;
        }
    }
    al_destroy_event_queue(queue);
}
void game_init()
{
    printf("Game Initializing...\n");
    //  al_init();              //initialize the allegro--------------------
    // init audio
    al_install_audio();
    al_init_acodec_addon();
    // Create display
    //   display = al_create_display(WIDTH, HEIGHT);     //set the window with width and height-----------------------------
    // create event queue
    event_queue = al_create_event_queue(); // set the window with position
    // Initialize Allegro settings
    //  al_set_window_position(display, 0, 0);//---------------------------------
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_init_font_addon();   // initialize the font addon
    al_init_ttf_addon();    // initialize the ttf (True Type Font) addon
    al_init_image_addon();  // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
                            //   al_install_keyboard(); // install keyboard event--------------------------------
    al_install_mouse();     // install mouse event
                            //   al_install_audio();    // install audio event
    // Register event
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    //   fps  = al_create_timer( 1.0 / FPS );//---------------------------------------
    al_register_event_source(event_queue, al_get_timer_event_source(fps));
    // initialize the icon on the display
    ALLEGRO_BITMAP *icon = al_load_bitmap("./image/icon.jpg");
    al_set_display_icon(display, icon);

    // font_ = al_load_ttf_font("./font/UndertaleSans.ttf", 50, 0);
    // al_draw_text(font_, al_map_rgb(255, 100, 100), 90, HEIGHT / 2 + 220, ALLEGRO_ALIGN_LEFT, "Start");
    // al_draw_rectangle(70, 600, 230, 655, al_map_rgb(255, 100, 100), 0);
}

void game_begin()
{
    // Load sound
    music_init();
    al_start_timer(fps);
    // initialize the menu before entering the loop
    menu_init();
}

void game_update()
{
    if (judge_next_window)
    {
        if (window == MENU_WINDOW) // destroy the last interface
            menu_destroy();
        else if (window == GAME_SCENE_WINDOW)
            game_scene_destroy();
        else if (window == ABOUT_WINDOW)
            about_destroy();
        else if (window == SETTING_WINDOW)
            setting_destroy();

        if (judge_next_window == MENU_WINDOW) // init the corresponding interface
            menu_init();
        else if (judge_next_window == GAME_SCENE_WINDOW)
        {
            music_destroy(); // destroy the menu music since we need to play the new music in game_scene
            game_scene_init();
        }
        else if (judge_next_window == ABOUT_WINDOW)
            about_init();
        else if (judge_next_window == SETTING_WINDOW)
            setting_init();
        window = judge_next_window;
        judge_next_window = 0;
    }
    if (window == GAME_SCENE_WINDOW)
    {
        charater_update();
    }
}
int process_event()
{
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    // process the event of other component
    if (window == MENU_WINDOW)
    { // doing the corresponding process
        menu_process(event);
    }
    else if (window == GAME_SCENE_WINDOW)
    {
        charater_process(event);
    }
    else if (window == ABOUT_WINDOW)
    {
        about_process(event);
    }
    else if (window == SETTING_WINDOW)
    {
        setting_process(event);
    }
    else if (window == EXIT_WINDOW)
    {
        return GAME_TERMINATE; //------------------------ exit button
    }

    // Shutdown our program
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;
    else if (event.type == ALLEGRO_EVENT_TIMER)
        if (event.timer.source == fps)
            draw = true;
    if (draw)
        game_update();
    return 0;
}
void game_draw()
{
    if (window == MENU_WINDOW)
    {
        menu_draw();
    }
    else if (window == GAME_SCENE_WINDOW)
    {
        game_scene_draw();
    }
    else if (window == ABOUT_WINDOW)
    {
        about_draw();
    }
    else if (window == SETTING_WINDOW)
    {
        setting_draw();
    }

    al_flip_display(); // display the result
}
int game_run()
{
    int error = 0;
    if (draw)
    {
        game_draw();
        draw = false;
    }
    if (!al_is_event_queue_empty(event_queue))
    {
        error = process_event();
    }
    return error;
}

void game_destroy()
{
    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(display); // release the memory of variable
    music_destroy();
    al_destroy_timer(fps);
    if (window == MENU_WINDOW || window == EXIT_WINDOW)
        menu_destroy();
    else if (window == GAME_SCENE_WINDOW)
        game_scene_destroy();
    else if (window == ABOUT_WINDOW)
        about_destroy();
    else if (window == SETTING_WINDOW)
        setting_destroy();
}
