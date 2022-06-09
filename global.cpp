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
