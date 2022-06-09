#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#define GAME_TERMINATE -1
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_video.h>
// note that you can't assign initial value here!
extern const float FPS;
extern int WIDTH;
extern int HEIGHT;
extern bool key_state[ALLEGRO_KEY_MAX];
extern int judge_next_window;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *fps;
extern ALLEGRO_DISPLAY *display;
extern const char *title;
extern float volume_value;
#endif
