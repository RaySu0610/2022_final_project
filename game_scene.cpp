#include "game_scene.h"

/*ALLEGRO_BITMAP *background = NULL;
ALLEGRO_FONT *font = NULL;
ALLEGRO_SAMPLE *song = NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;*/
enum window_
{
    MENU_WINDOW = 1,
    GAME_SCENE_WINDOW = 2,
    ABOUT_WINDOW = 3,
    SETTING_WINDOW = 4,
    EXIT_WINDOW = 5
};
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
    al_draw_bitmap(background, 0, 0, 0);
    character_draw();
}
void game_scene_destroy()
{
    al_destroy_bitmap(background);
    character_destory();
}
