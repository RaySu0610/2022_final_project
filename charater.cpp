#include "charater.h"

int heart_counter_initial = 500;
int heart_counter = heart_counter_initial;
ALLEGRO_SAMPLE *injuried = NULL;
ALLEGRO_SAMPLE_INSTANCE *injuried_instance;
// the state of character
enum
{
    STOP = 0,
    MOVE,
    ATK
};
typedef struct
{
    int x, y;
    int width, height;
    int scale;
    ALLEGRO_BITMAP *img;
} Monster;
Monster monster[10];

typedef struct
{
    int x, y; // the position of image
    int width, height;
    int v = 3;
    double scale = 0.1;
    int hp = 20;
    bool cheating = false;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *died;
} Heart;

Heart heart;
ALLEGRO_SAMPLE *sample = NULL;
void character_init()
{
    // heart.img = al_load_bitmap("./image/heart1.jfif");
    heart.img = al_load_bitmap("./image/heart.png");
    al_convert_mask_to_alpha(heart.img, al_map_rgb(255, 255, 255));
    heart.died = al_load_bitmap("./image/dead.png");
    al_convert_mask_to_alpha(heart.died, al_map_rgb(255, 255, 255));
    injuried = al_load_sample("./sound/injuried.wav");
    injuried_instance = al_create_sample_instance(injuried);
    al_set_sample_instance_playmode(injuried_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(injuried_instance, al_get_default_mixer());
    al_set_sample_instance_gain(injuried_instance, (volume_value) / 200);
    // initial the geometric information of character
    heart.width = al_get_bitmap_width(heart.img);
    heart.height = al_get_bitmap_height(heart.img);
    printf("%d %d\n", heart.width, heart.height);
    // heart.x = WIDTH / 2;
    // heart.y = HEIGHT / 2;
    heart.x = WIDTH * (bound_left1 + bound_right1) / 2;
    heart.y = HEIGHT * (bound_top + bound_bottom) / 2;
}
void charater_process(ALLEGRO_EVENT event)
{
    // // process the animation
    if (event.type == ALLEGRO_EVENT_TIMER)
    {
        // if (event.timer.source == fps)
        // {
        //     chara.anime++;
        //     chara.anime %= chara.anime_time;
        // }
        // // process the keyboard event
    }
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        key_state[event.keyboard.keycode] = true;
        // chara.anime = 0;
    }
    else if (event.type == ALLEGRO_EVENT_KEY_UP)
    {
        key_state[event.keyboard.keycode] = false;
    }
}
void charater_update()
{
    // // use the idea of finite state machine to deal with different state
    if (key_state[ALLEGRO_KEY_W])
    {
        heart.y -= heart.v;
        if (heart.y <= HEIGHT * bound_top + heart.height * heart.scale)
        {
            heart.y = HEIGHT * bound_top + heart.height * heart.scale;
        }
        // chara.state = MOVE;
    }
    else if (key_state[ALLEGRO_KEY_S])
    {
        heart.y += heart.v;
        if (heart.y >= HEIGHT * bound_bottom - heart.height * heart.scale)
        {
            heart.y = HEIGHT * bound_bottom - heart.height * heart.scale;
        }
        // chara.state = MOVE;
    }

    if (key_state[ALLEGRO_KEY_A])
    {
        // chara.dir = false;
        heart.x -= heart.v;
        if (heart.x <= WIDTH * bound_left1 + heart.width * heart.scale / 2)
        {
            heart.x = WIDTH * bound_left1 + heart.width * heart.scale / 2;
        }
        // chara.state = MOVE;
    }
    else if (key_state[ALLEGRO_KEY_D])
    {
        // chara.dir = true;
        heart.x += heart.v;
        if (heart.x >= WIDTH * bound_right1 - heart.width * heart.scale / 2)
        {
            heart.x = WIDTH * bound_right1 - heart.width * heart.scale / 2;
        }
        // chara.state = MOVE;
    }
}
void character_draw()
{

    // show heart
    if (heart_counter == heart_counter_initial || (heart_counter % 50) < 25 || isgreen == 1)
    {
        if (!lose)
        {
            al_draw_scaled_bitmap(
                heart.img, 0, 0, heart.width, heart.height,
                heart.x, heart.y,
                heart.width * heart.scale, heart.height * heart.scale,
                0);
        }
        else
        {
            al_draw_scaled_bitmap(
                heart.died, 0, 0, heart.width, heart.height,
                heart.x, heart.y,
                heart.width * heart.scale, heart.height * heart.scale,
                0);
        }
    }
}
void character_destory()
{
    al_destroy_bitmap(heart.img);
    al_destroy_bitmap(heart.died);
    al_destroy_sample(injuried);
    al_destroy_sample_instance(injuried_instance);
    // al_destroy_bitmap(chara.img_atk[1]);
    // al_destroy_bitmap(chara.img_move[0]);
    // al_destroy_bitmap(chara.img_move[1]);
    // al_destroy_sample_instance(chara.atk_Sound);
    // al_destroy_sample(sample);
}

int get_character_hp()
{
    return heart.hp;
}
void character_hp_reset()
{
    heart.hp = 20;
}

void character_attack_check1(int pos[][2], int n)
{
    if (heart.cheating)
    {
        return;
    }
    if (heart_counter != heart_counter_initial)
    {
        heart_counter--;
        if (heart_counter == 0)
        {
            heart_counter = heart_counter_initial;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (
                abs(pos[i][0] - heart.x) <= 6 &&
                abs(pos[i][1] - heart.y) <= 6)
            {
                heart.hp -= 3;
                heart_counter--;
                al_play_sample_instance(injuried_instance);
                printf("heart\n");
                alive();
                break;
            }
        }
    }
}
void character_attack_check2(int pos[][2], int n)
{
    if (heart.cheating)
    {
        return;
    }
    if (heart_counter != heart_counter_initial)
    {
        heart_counter--;
        if (heart_counter == 0)
        {
            heart_counter = heart_counter_initial;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (
                abs(pos[i][0] - heart.x) <= heart.width * heart.scale / 2 + 3 &&
                abs(pos[i][1] - heart.y) <= heart.height * heart.scale / 2 + 3)
            {
                heart.hp -= 3;
                heart_counter--;
                al_play_sample_instance(injuried_instance);
                printf("heart\n");
                alive();
                break;
            }
        }
    }
}
void character_attack_check3(int pos[][2], int n)
{
    if (heart.cheating)
    {
        return;
    }
    if (heart_counter != heart_counter_initial)
    {
        heart_counter--;
        if (heart_counter == 0)
        {
            heart_counter = heart_counter_initial;
            isgreen = 0;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (
                abs(pos[i][0] - heart.x) <= heart.width * heart.scale / 2 + 3 &&
                abs(pos[i][1] - heart.y) <= heart.height * heart.scale / 2 + 3)
            {
                if (i != 0)
                {
                    heart.hp -= 3;
                    heart_counter--;
                    al_play_sample_instance(injuried_instance);
                    printf("heart\n");
                    alive();
                    break;
                }
                else
                {
                    isgreen = 1;
                    mercy_usabled = true;
                    heart.hp += 1;
                    heart_counter--;
                    al_play_sample_instance(injuried_instance);
                    printf("heart_plus\n");
                    break;
                }
            }
        }
    }
}

void alive()
{
    if (heart.hp <= 0)
    {
        lose = true;
        printf("You died\n");
    }
}
void cheating_init()
{
    heart.cheating = true;
    // printf("Cheating mode is on!!!!!!!!!!!!!!!!!!!!\n");
}
void recover(int val)
{

    heart.hp += val;
    // printf("hp: %d\n", heart.hp);
}
void monster_init()
{
    int i;
    monster[0].img = al_load_bitmap("./image/vegetoid_01.jpg");
    monster[1].img = al_load_bitmap("./image/vegetoid_02.jpg");
    monster[2].img = al_load_bitmap("./image/vegetoid_03.jpg");
    monster[3].img = al_load_bitmap("./image/vegetoid_04.jpg");
    monster[4].img = al_load_bitmap("./image/vegetoid_05_01.png");
    monster[5].img = al_load_bitmap("./image/fight.png");
    //    printf("check2\n");
    //	monster.width  = al_get_bitmap_width(monster.img);
    //    monster.height = al_get_bitmap_height(monster.img);
    //    printf("check3\n");
    for (i = 0; i <= 4; i++)
        monster[i].x = WIDTH * (bound_left1 + bound_right1) / 2 - 100;
    for (i = 0; i <= 4; i++)
        monster[i].y = HEIGHT / 4;
    printf("monster_init\n");
}

void monster_draw()
{
    if (monster_hurt == 0)
    { //�Ǫ��]�@��^
        if (monster_anime < monster_anime_time / 4)
            al_draw_bitmap(monster[0].img, monster[0].x, monster[0].y, 0);
        else if (monster_anime < monster_anime_time / 2)
            al_draw_bitmap(monster[1].img, monster[0].x, monster[0].y, 0);
        else if (monster_anime < monster_anime_time * 3 / 4)
            al_draw_bitmap(monster[2].img, monster[0].x, monster[0].y, 0);
        else if (monster_anime < monster_anime_time)
            al_draw_bitmap(monster[3].img, monster[0].x, monster[0].y, 0);
    }
    else if (monster_hurt == 1)
    { //�Ǫ��Q��
        if (monster_anime < monster_anime_time / 4)
            al_draw_bitmap(monster[0].img, monster[0].x, monster[0].y, 0);
        else if (monster_anime < monster_anime_time / 2)
            al_draw_bitmap(monster[1].img, monster[0].x, monster[0].y, 0);
        else if (monster_anime < monster_anime_time * 3 / 4)
            al_draw_bitmap(monster[2].img, monster[0].x, monster[0].y, 0);
        else if (monster_anime < monster_anime_time)
            al_draw_bitmap(monster[3].img, monster[0].x, monster[0].y, 0);
        al_draw_bitmap(monster[5].img, monster[0].x, monster[0].y, 0);
    }
    else
    { //�Ǫ�����
        monster_anime %= monster_anime_hurt;
        //        printf("monster_anime=%d monster_anime_hurt=%d, position=%d\n",monster_anime,monster_anime_hurt,monster[0].x-(monster_anime_hurt/2)+monster_anime);
        if (monster_anime < monster_anime_hurt / 4)
            al_draw_bitmap(monster[4].img, monster[0].x - (monster_anime_hurt / 2) + monster_anime / 3, monster[0].y, 0);
        else if (monster_anime < monster_anime_hurt / 2)
            al_draw_bitmap(monster[4].img, monster[0].x + (monster_anime_hurt / 2) - monster_anime / 3, monster[0].y, 0);
        else if (monster_anime < monster_anime_hurt * 3 / 4)
            al_draw_bitmap(monster[4].img, monster[0].x - (monster_anime_hurt / 2) + monster_anime / 3, monster[0].y, 0);
        else if (monster_anime < monster_anime_hurt)
            al_draw_bitmap(monster[4].img, monster[0].x + (monster_anime_hurt / 2) - monster_anime / 3, monster[0].y, 0);
    }
}
void monster_destroy()
{
    for (int i = 0; i < 6; i++)
        al_destroy_bitmap(monster[i].img);
}
