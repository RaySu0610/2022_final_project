#include "global.h"

// variables for global usage
const float FPS = 60.0;
int WIDTH = 1024;
int HEIGHT = 760;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
ALLEGRO_DISPLAY *display = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
int judge_next_window = 0;
const char *title = "Final Project 10xxxxxxx";
float volume_value = 20;

float bound_top = 400.0 / 760;
float bound_bottom = 580.0 / 760;
float bound_left = 1.0 / 10;
float bound_right = 9.0 / 10;
float bound_left1 = 3.0 / 10;
float bound_right1 = 7.0 / 10;

int monster_anime =0;
int monster_anime_time =240;
int monster_anime_hurt =20;
int monster_hurt = 0;

int isgreen = 0;

bool mercy_usabled = false;
bool lose = false;
