#include "global.h"

// variables for global usage
const float FPS = 30.0;
const int WIDTH = 1100; //這裡有改變數
const int HEIGHT = 700; //調成我們遊戲適合的size
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool judge_next_window = false;
bool judge_menu_next = false;
bool judge_gameover = false;
int main_character_1 = 1; //角色選擇
int main_character_2 = 1;
int winner = 1; //紀錄誰是winner