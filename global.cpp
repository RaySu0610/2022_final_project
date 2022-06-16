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

int bound_top = 400;
int bound_bottom = 580;
int bound_left = WIDTH * 1 / 10;
int bound_right = WIDTH * 9 / 10;
int bound_left1 = WIDTH * 3 / 10;
int bound_right1 = WIDTH * 7 / 10;