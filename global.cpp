#include "global.h"

// variables for global usage
const float FPS = 60.0;
const int WIDTH = 1024;
const int HEIGHT = 760;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
int judge_next_window = 0;
