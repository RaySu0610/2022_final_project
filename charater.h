#include "global.h"

void character_init();
void charater_process(ALLEGRO_EVENT event);
void charater_update();
void character_draw();
void character_destory();

int get_character_hp();

void character_attack_check1(int pos[][2], int n);
void character_attack_check2(int pos[][2], int n);
void character_attack_check3(int pos[][2], int n);

void cheating_init();
void recover(int val);

void monster_init();
void monster_draw();
void monster_distroy();
