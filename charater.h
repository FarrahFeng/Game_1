#include "global.h"
#include "algif.h"
//character
typedef struct character
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    bool dir;          // left: false, right: true
    bool atk;
    bool bigatk;
    int state; // the state of character
    ALGIF_ANIMATION *img_move[3];
    ALGIF_ANIMATION *img_atk[3];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    ALLEGRO_SAMPLE_INSTANCE *bigatk_Sound;
    ALLEGRO_BITMAP *img_move_infor;

    //用來調整gif檔的位置 //面向的方向會影響誤差
    int atk1_error_x;
    int atk1_error_y;
    int atk1_error_x_2; //反向的誤差
    int atk1_error_y_2;
    int atk3_error_x;
    int atk3_error_y;
    int atk3_error_x_2;
    int atk3_error_y_2;
    int move2_error_x;
    int move2_error_y;
    int move2_error_x_2;
    int move2_error_y_2;
    int move3_error_x;
    int move3_error_y;
    int move3_error_x_2;
    int move3_error_y_2;

    int HP;
    int SP;         //血量和能量值
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
} Character;

void character_init();
Character character1_init();
Character character2_init();
Character character3_init();
void charater_process(ALLEGRO_EVENT event);
void charater_update();
void player1_update();
void player2_update();
int valid_attack(Character, Character);
void character_draw();
void player1_draw();
void player2_draw();
void character_destory();
void treasure_draw();
int encounter(Character);
