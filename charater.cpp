#include "charater.h"
#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)
// the state of character
enum
{
    STOP = 0,
    JUMP,
    MOVE,
    ATK1,
    ATK2

};
typedef struct
{
    int x;
    int y;
    int width;
    bool exist;
    int anime;
} Tool;

Character player1, player2;
Tool treasure;
ALLEGRO_BITMAP *HP_picture[11]; //HP image
ALLEGRO_BITMAP *SP_picture[11]; //SP image

ALLEGRO_SAMPLE *sound_sample1 = NULL;
ALLEGRO_SAMPLE *sound_sample2 = NULL;
ALLEGRO_SAMPLE *sound_sample3 = NULL;

ALLEGRO_SAMPLE *soundsample1 = NULL;
ALLEGRO_SAMPLE *soundsample2 = NULL;
ALLEGRO_SAMPLE *soundsample3 = NULL;

ALLEGRO_BITMAP *infor_1 = NULL;
ALLEGRO_BITMAP *infor_2 = NULL;
ALLEGRO_BITMAP *infor_3 = NULL;
ALLEGRO_BITMAP *img_tr = NULL; //treasure image

ALLEGRO_SAMPLE *trea_sample = NULL;
ALLEGRO_SAMPLE_INSTANCE *trea_sound = NULL;
bool judge = false;
int count = 0;

void character_init()
{ //player 1
    if (main_character_1 == 1)
    {
        player1 = character1_init(); //表示player 1選到character 1
        player1.x = WIDTH / 2 - 500;
    }
    else if (main_character_1 == 2)
    {
        player1 = character2_init();
        player1.x = WIDTH / 2 - 530;
    }
    else
    {
        player1 = character3_init();
        player1.x = WIDTH / 2 - 520;
    }

    player1.HP = 100;
    player1.SP = 0;
    player1.dir = true;
    player1.y = HEIGHT / 2;

    //player 2

    if (main_character_2 == 1)
    {
        player2 = character1_init();
        player2.x = WIDTH / 2 + 340;
    }
    else if (main_character_2 == 2)
    {
        player2 = character2_init();
        player2.x = WIDTH / 2 + 220;
    }
    else
    {
        player2 = character3_init();
        player2.x = WIDTH / 2 + 220;
    }

    player2.HP = 100;
    player2.SP = 0;
    player2.dir = false;
    player2.y = HEIGHT / 2;

    //load hp sp picture
    for (int i = 0; i <= 10; i++)
    {
        char temp[50];
        sprintf(temp, "./image/HP/HP_%d.png", i);
        HP_picture[i] = al_load_bitmap(temp);
    }
    for (int i = 0; i <= 10; i++)
    {
        char temp[50];
        sprintf(temp, "./image/SP/SP_%d.png", i);
        SP_picture[i] = al_load_bitmap(temp);
    }

    img_tr = al_load_bitmap("./image/treasure.png");
    treasure.width = al_get_bitmap_width(img_tr);
    treasure.x = rand() % (WIDTH - treasure.width - 5);
    treasure.y = HEIGHT / 2 + 50;
    trea_sample = al_load_sample("./sound/trea_sound.wav");
    trea_sound = al_create_sample_instance(trea_sample);
    al_set_sample_instance_playmode(trea_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(trea_sound, al_get_default_mixer());
}
void charater_process(ALLEGRO_EVENT event)
{
    // process the animation
    if (event.type == ALLEGRO_EVENT_TIMER)
    {
        if (event.timer.source == fps)
        {
            player1.anime++;
            player1.anime %= player1.anime_time;
            player2.anime++;
            player2.anime %= player2.anime_time;
            treasure.anime++;

            if (treasure.anime == 1000)
                treasure.exist = true;
        }
        // process the keyboard event
    }
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        key_state[event.keyboard.keycode] = true;
        //按一次按鍵只做一次攻擊
        player1.atk = true;
        player1.bigatk = true;
        player2.atk = true;
        player2.bigatk = true;
        player1.anime = 0;
        player2.anime = 0;
    }
    else if (event.type == ALLEGRO_EVENT_KEY_UP)
    {
        key_state[event.keyboard.keycode] = false;
    }
}

void charater_update()
{
    if (player1.HP <= 0 || player2.HP <= 0)
    {
        if (player1.HP <= 0)
            winner = 2;
        else if (player2.HP <= 0)
            winner = 1;

        judge = true;
        count++;
    }
    if (judge == true && count == 100)
        judge_gameover = true;

    player1_update();
    player2_update();
}

void character_draw()
{
    if (treasure.exist == true && judge == false)
        treasure_draw();
    player1_draw();
    player2_draw();
}

Character character1_init() //關羽
{
    //printf("ch1_ini\n");
    Character player;
    // load character images//load player1 images
    for (int i = 1; i <= 3; i++) //laod movegif
    {
        char temp[50];
        sprintf(temp, "./image/character/關羽/move_%d.gif", i);
        player.img_move[i - 1] = algif_load_animation(temp);
    }
    //用來存角色寬、高
    infor_1 = al_load_bitmap("./image/character/關羽/move_1_infor.png");
    player.img_move_infor = infor_1;

    for (int i = 1; i <= 3; i++)
    {
        char temp[50];
        sprintf(temp, "./image/character/關羽/atk_%d.gif", i);
        player.img_atk[i - 1] = algif_load_animation(temp);
    }

    // load effective sound
    sound_sample1 = al_load_sample("./sound/atk_sound.wav");
    player.atk_Sound = al_create_sample_instance(sound_sample1);
    al_set_sample_instance_playmode(player.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(player.atk_Sound, al_get_default_mixer());

    soundsample1 = al_load_sample("./sound/bigatk_1.wav");
    player.bigatk_Sound = al_create_sample_instance(soundsample1);
    al_set_sample_instance_playmode(player.bigatk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(player.bigatk_Sound, al_get_default_mixer());

    // initial the geometric information of player1
    player.width = al_get_bitmap_width(player.img_move_infor);
    player.height = al_get_bitmap_height(player.img_move_infor);

    // initial the animation component
    player.state = STOP;
    player.anime = 0;
    player.anime_time = 30;
    //
    player.atk1_error_x = -210;   //-180 -175 -160太右 ok
    player.atk1_error_y = -30;    //-33 -35太上 ok
    player.atk1_error_x_2 = -190; //-180 -175 -160太右 ok
    player.atk1_error_y_2 = -31;  //-33 -35 太上 ok

    player.atk3_error_x = -295;   //-180 -250 -280太右 -300太左ok
    player.atk3_error_y = -185;   //-120 -180 太下面 -300 -250 -200 太上ok
    player.atk3_error_x_2 = -400; //-300 -350太右
    player.atk3_error_y_2 = -180; //-120太下面 -300 -250 -200up

    player.move2_error_x = -155; //ok
    player.move2_error_y = 55;   //ok
    player.move2_error_x_2 = 0;  // -155太左 ok
    player.move2_error_y_2 = 53; //55 太下  50上ok

    player.move3_error_x = -150;   //ok
    player.move3_error_y = -140;   //ok
    player.move3_error_x_2 = -170; //-150 -160太又ok
    player.move3_error_y_2 = -140; // -150太上 -130下ok

    return player;
}
Character character2_init() //曹操
{
    //printf("ch2_ini\n");
    Character player;
    // load character images//load player2 images
    for (int i = 1; i <= 3; i++)
    { //原本用gif檔案，但是實際上不存在這個檔案，所以才會直接shut down

        char temp[50];
        sprintf(temp, "./image/character/曹操/move_%d.gif", i);
        player.img_move[i - 1] = algif_load_animation(temp);
    }

    infor_2 = al_load_bitmap("./image/character/曹操/move_1_infor.png");
    player.img_move_infor = infor_2;

    for (int i = 1; i <= 3; i++)
    {
        char temp[50];
        sprintf(temp, "./image/character/曹操/atk_%d.gif", i);
        player.img_atk[i - 1] = algif_load_animation(temp);
    }
    //printf("success to load 2\n");

    // load effective sound

    sound_sample2 = al_load_sample("./sound/atk_sound.wav");
    player.atk_Sound = al_create_sample_instance(sound_sample2);
    al_set_sample_instance_playmode(player.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(player.atk_Sound, al_get_default_mixer());

    soundsample2 = al_load_sample("./sound/bigatk_2.wav");
    player.bigatk_Sound = al_create_sample_instance(soundsample2);
    al_set_sample_instance_playmode(player.bigatk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(player.bigatk_Sound, al_get_default_mixer());

    // initial the geometric information of player2//這裡出問題
    player.width = al_get_bitmap_width(player.img_move_infor);
    player.height = al_get_bitmap_height(player.img_move_infor);

    // initial the animation component
    player.state = STOP;
    player.anime = 0;
    player.anime_time = 30;

    player.atk1_error_x = -35;
    player.atk1_error_y = -5;
    player.atk1_error_x_2 = -90;
    player.atk1_error_y_2 = -5;

    player.atk3_error_x = -217;
    player.atk3_error_y = -91;
    player.atk3_error_x_2 = -150;
    player.atk3_error_y_2 = -93;

    player.move2_error_x = -24;
    player.move2_error_y = -10;
    player.move2_error_x_2 = 0;
    player.move2_error_y_2 = -7;

    player.move3_error_x = -290;
    player.move3_error_y = 21;
    player.move3_error_x_2 = -180;
    player.move3_error_y_2 = 20;

    return player;
}
Character character3_init() //呂布
{
    //printf("ch3_ini\n");
    Character player;
    // load character images//load player1 images
    for (int i = 1; i <= 3; i++)
    { //原本用gif檔案，但是實際上不存在這個檔案，所以才會直接shut down
        char temp[50];
        sprintf(temp, "./image/character/呂布/move_%d.gif", i);
        player.img_move[i - 1] = algif_load_animation(temp);
    }

    infor_3 = al_load_bitmap("./image/character/呂布/move_1_infor.png");
    player.img_move_infor = infor_3;

    for (int i = 1; i <= 3; i++)
    {
        char temp[50];
        sprintf(temp, "./image/character/呂布/atk_%d.gif", i);
        player.img_atk[i - 1] = algif_load_animation(temp);
    }

    // load effective sound
    sound_sample3 = al_load_sample("./sound/atk_sound.wav");
    player.atk_Sound = al_create_sample_instance(sound_sample3);
    al_set_sample_instance_playmode(player.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(player.atk_Sound, al_get_default_mixer());

    soundsample3 = al_load_sample("./sound/bigatk_3.wav");
    player.bigatk_Sound = al_create_sample_instance(soundsample3);
    al_set_sample_instance_playmode(player.bigatk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(player.bigatk_Sound, al_get_default_mixer());

    // initial the geometric information of player1
    player.width = al_get_bitmap_width(player.img_move_infor);
    player.height = al_get_bitmap_height(player.img_move_infor);

    // initial the animation component
    player.state = STOP;
    player.anime = 0;
    player.anime_time = 30;

    player.atk1_error_x = -10;
    player.atk1_error_y = 0;
    player.atk1_error_x_2 = -150;
    player.atk1_error_y_2 = 3;

    player.atk3_error_x = -280;
    player.atk3_error_y = -115;
    player.atk3_error_x_2 = -220;
    player.atk3_error_y_2 = -110;

    player.move2_error_x = -100;
    player.move2_error_y = 5;
    player.move2_error_x_2 = -50;
    player.move2_error_y_2 = 2;

    player.move3_error_x = -120;
    player.move3_error_y = -115;
    player.move3_error_x_2 = 20;
    player.move3_error_y_2 = -130;

    return player;
}

void player1_update()
{
    // use the idea of finite state machine to deal with different state
    //player1
    if (key_state[ALLEGRO_KEY_W])
    {
        //player1.y -= 5;
        player1.state = JUMP;
    }
    else if (key_state[ALLEGRO_KEY_A])
    {
        player1.dir = false;
        player1.x -= 5;
        if (player1.x < 0)
            player1.x = 0;
        player1.state = MOVE;
    }
    /*else if (key_state[ALLEGRO_KEY_S])
    {
        player1.y += 5;
        player1.state = MOVE;
    }*/
    else if (key_state[ALLEGRO_KEY_D])
    {
        player1.dir = true;
        player1.x += 5;
        if (player1.x > (WIDTH - player1.width))
            player1.x = (WIDTH - player1.width);
        player1.state = MOVE;
    }
    else if (key_state[ALLEGRO_KEY_SPACE])
    {
        player1.state = ATK1; //攻擊1

        if (valid_attack(player1, player2) && player1.atk == true)
        {
            //printf("player 1 attack player2\n");
            player2.HP -= 10;
            player2.HP = MAX(0, player2.HP);
            player2.SP -= 10;
            player2.SP = MAX(0, player2.SP);
            //printf("update player2 hp sp\n");

            player1.SP += 20;
            player1.SP = MIN(100, player1.SP);

            player1.atk = false; //必免按一次按鍵造成兩次攻擊傷害
            //printf("player1 HP:%d,SP:%d\n", player1.HP, player1.SP);
            //printf("player2 HP:%d,SP:%d\n", player2.HP, player2.SP);

            //printf("update player1 sp\n");
        }
    }
    else if (key_state[ALLEGRO_KEY_COMMAND])
    {
        if (player1.SP >= 100)
        {
            //if (key_state[ALLEGRO_KEY_ENTER])
            player1.state = ATK2; //大絕
            player1.SP = 0;

            if (valid_attack(player1, player2) && player1.bigatk == true)
            {
                player2.HP -= 30;
                player2.HP = MAX(0, player2.HP);
                player2.SP = 0;

                player1.bigatk = false;
                //printf("player1 HP:%d,SP:%d\n", player1.HP, player1.SP);
                //printf("player2 HP:%d,SP:%d\n", player2.HP, player2.SP);
            }
        }
    }
    else if (player1.anime == player1.anime_time - 1)
    {
        player1.anime = 0;
        player1.state = STOP;
    }
    else if (player1.anime == 0)
    {
        player1.state = STOP;
    }
    else if (encounter(player1)) //成功吃到寶箱
    {
        al_play_sample_instance(trea_sound);
        al_set_sample_instance_gain(trea_sound, 5);
        player1.SP += 40; //吃到寶箱技能值增加
        player1.SP = MIN(100, player1.SP);
        treasure.exist = false;
        //printf("player1 eats treasure\n");
    }
}
void player2_update()
{ //player 2
    if (key_state[ALLEGRO_KEY_UP])
    {
        //player2.y -= 5;
        player2.state = JUMP;
    }
    else if (key_state[ALLEGRO_KEY_LEFT])
    {
        player2.dir = false;
        player2.x -= 5;
        if (player2.x < 0)
            player2.x = 0;
        player2.state = MOVE;
    }
    /*else if (key_state[ALLEGRO_KEY_DOWN])
    {
        player2.y += 5;
        player2.state = MOVE;
    }*/
    else if (key_state[ALLEGRO_KEY_RIGHT])
    {
        player2.dir = true;
        player2.x += 5;
        if (player2.x > (WIDTH - player2.width))
            player2.x = (WIDTH - player2.width);
        player2.state = MOVE;
    }
    else if (key_state[ALLEGRO_KEY_ENTER])
    {
        player2.state = ATK1; //攻擊

        if (valid_attack(player2, player1) && player2.atk == true)
        {
            //printf("player 2 attack player1\n");
            player1.HP -= 10;
            player1.HP = MAX(0, player1.HP);
            player1.SP -= 10;
            player1.SP = MAX(0, player1.SP);

            player2.SP += 20;
            player2.SP = MIN(100, player2.SP);

            player2.atk = false; //必免按一次按鍵造成兩次攻擊傷害
            //printf("player1 HP:%d,SP:%d\n", player1.HP, player1.SP);
            //printf("player2 HP:%d,SP:%d\n", player2.HP, player2.SP);
        }
    }
    else if (key_state[ALLEGRO_KEY_L])
    {
        if (player2.SP >= 100)
        {
            //if (key_state[ALLEGRO_KEY_ENTER])
            player2.state = ATK2; //大絕
            player2.SP = 0;

            if (valid_attack(player2, player1) && player2.bigatk == true)
            {
                player1.HP -= 30;
                player1.HP = MAX(0, player1.HP);
                player1.SP = 0;

                player2.bigatk = false;
                //printf("player1 HP:%d,SP:%d\n", player1.HP, player1.SP);
                //printf("player2 HP:%d,SP:%d\n", player2.HP, player2.SP);

                //printf("update player1 hp sp\n");
            }
        }
    }
    else if (player2.anime == player2.anime_time - 1)
    {
        player2.anime = 0;
        player2.state = STOP;
    }
    else if (player2.anime == 0)
    {
        player2.state = STOP;
    }
    else if (encounter(player2)) //成功吃到寶箱
    {
        al_play_sample_instance(trea_sound);
        al_set_sample_instance_gain(trea_sound, 5);
        player2.SP += 40; //吃到寶箱技能值增加
        player2.SP = MIN(100, player2.SP);
        treasure.exist = false;
        //printf("player2 eats treasure\n");
    }
}

int valid_attack(Character attacker, Character defender) //前面攻擊者 後面被攻擊
{
    if (attacker.x <= defender.x) //攻擊方在左邊 防禦在右
    {
        if (attacker.dir) //攻擊面相防禦方才攻擊成功
        {
            //printf("attacker dir:%d\n", attacker.dir);
            if (attacker.x + attacker.width >= defender.x)
                return 1;
            else
                return 0;
        }
    }
    else
    {                      //防禦．．．．攻擊
        if (!attacker.dir) //攻擊面相防禦方
        {
            //printf("attacker dir:%d\n", attacker.dir);
            if (attacker.x <= (defender.x + defender.width))
                return 1;
            else
                return 0;
        }
    }
    return 0;
}
void player1_draw() //畫player的動作
{
    // with the state, draw corresponding image
    if (player1.state == STOP)
    {
        if (player1.dir) //true: ringht  照片本身就是朝向右邊
            al_draw_bitmap(algif_get_bitmap(player1.img_move[0], al_get_time()), player1.x, player1.y, 0);
        else
            al_draw_bitmap(algif_get_bitmap(player1.img_move[0], al_get_time()), player1.x, player1.y, ALLEGRO_FLIP_HORIZONTAL);
    }
    else if (player1.state == MOVE)
    {
        if (player1.dir)
        {
            al_draw_bitmap(algif_get_bitmap(player1.img_move[1], al_get_time()), player1.x + player1.move2_error_x, player1.y + player1.move2_error_y, 0);
        }
        else
        {
            al_draw_bitmap(algif_get_bitmap(player1.img_move[1], al_get_time()), player1.x + player1.move2_error_x_2, player1.y + player1.move2_error_y_2, ALLEGRO_FLIP_HORIZONTAL);
        }
    }
    else if (player1.state == JUMP)
    {
        if (player1.dir)
        {
            al_draw_bitmap(algif_get_bitmap(player1.img_move[2], al_get_time()), player1.x + player1.move3_error_x, player1.y + player1.move3_error_y, 0);
        }
        else
        {
            al_draw_bitmap(algif_get_bitmap(player1.img_move[2], al_get_time()), player1.x + player1.move3_error_x_2, player1.y + player1.move3_error_y_2, ALLEGRO_FLIP_HORIZONTAL);
        }
    }
    else if (player1.state == ATK1)
    {

        if (player1.dir)
        {
            al_draw_bitmap(algif_get_bitmap(player1.img_atk[0], al_get_time()), player1.x + player1.atk1_error_x, player1.y + player1.atk1_error_y, 0);
            al_play_sample_instance(player1.atk_Sound);
        }
        else
        {
            al_draw_bitmap(algif_get_bitmap(player1.img_atk[0], al_get_time()), player1.x + player1.atk1_error_x_2, player1.y + player1.atk1_error_y_2, ALLEGRO_FLIP_HORIZONTAL);
            al_play_sample_instance(player1.atk_Sound);
        }
    }
    else if (player1.state == ATK2)
    {
        if (player1.dir)
        {
            al_draw_bitmap(algif_get_bitmap(player1.img_atk[2], al_get_time()), player1.x + player1.atk3_error_x, player1.y + player1.atk3_error_y, 0);
            al_play_sample_instance(player1.bigatk_Sound);
        }
        else
        {
            al_draw_bitmap(algif_get_bitmap(player1.img_atk[2], al_get_time()), player1.x + player1.atk3_error_x_2, player1.y + player1.atk3_error_y_2, ALLEGRO_FLIP_HORIZONTAL);
            al_play_sample_instance(player1.bigatk_Sound);
        }
        al_set_sample_instance_gain(player1.bigatk_Sound, 4); //調音量
    }
    //draw HP,SP image
    al_draw_bitmap(HP_picture[player1.HP / 10], -55, -145, 0);
    al_draw_bitmap(SP_picture[player1.SP / 10], -66, -155, 0); //更新技能條
}

//畫player的動作
void player2_draw()
{
    // with the state, draw corresponding image
    if (player2.state == STOP)
    {
        if (player2.dir)
            al_draw_bitmap(algif_get_bitmap(player2.img_move[0], al_get_time()), player2.x, player2.y, 0);
        //al_draw_bitmap(player1.img_move[0], player1.x, player1.y, ALLEGRO_FLIP_HORIZONTAL);
        else
            al_draw_bitmap(algif_get_bitmap(player2.img_move[0], al_get_time()), player2.x, player2.y, ALLEGRO_FLIP_HORIZONTAL);
    }
    else if (player2.state == MOVE)
    {
        if (player2.dir)
        {
            al_draw_bitmap(algif_get_bitmap(player2.img_move[1], al_get_time()), player2.x + player2.move2_error_x, player2.y + player2.move2_error_y, 0);
        }
        else
        {
            al_draw_bitmap(algif_get_bitmap(player2.img_move[1], al_get_time()), player2.x + player2.move2_error_x_2, player2.y + player2.move2_error_y_2, ALLEGRO_FLIP_HORIZONTAL);
        }
    }
    else if (player2.state == JUMP)
    {
        if (player2.dir)
        {
            al_draw_bitmap(algif_get_bitmap(player2.img_move[2], al_get_time()), player2.x + player2.move3_error_x, player2.y + player2.move3_error_y, 0);
        }
        else
        {
            al_draw_bitmap(algif_get_bitmap(player2.img_move[2], al_get_time()), player2.x + player2.move3_error_x_2, player2.y + player2.move3_error_y_2, ALLEGRO_FLIP_HORIZONTAL);
        }
    }
    else if (player2.state == ATK1)
    {

        if (player2.dir)
        {
            al_draw_bitmap(algif_get_bitmap(player2.img_atk[0], al_get_time()), player2.x + player2.atk1_error_x, player2.y + player2.atk1_error_y, 0);
            al_play_sample_instance(player2.atk_Sound);
        }
        else
        {
            al_draw_bitmap(algif_get_bitmap(player2.img_atk[0], al_get_time()), player2.x + player2.atk1_error_x_2, player2.y + player2.atk1_error_y_2, ALLEGRO_FLIP_HORIZONTAL);
            al_play_sample_instance(player2.atk_Sound);
        }
    }
    else if (player2.state == ATK2)
    {
        if (player2.dir)
        {
            al_draw_bitmap(algif_get_bitmap(player2.img_atk[2], al_get_time()), player2.x + player2.atk3_error_x, player2.y + player2.atk3_error_y, 0);
            al_play_sample_instance(player2.bigatk_Sound);
        }
        else
        {
            al_draw_bitmap(algif_get_bitmap(player2.img_atk[2], al_get_time()), player2.x + player2.atk3_error_x_2, player2.y + player2.atk3_error_y_2, ALLEGRO_FLIP_HORIZONTAL);
            al_play_sample_instance(player2.bigatk_Sound);
        }
        al_set_sample_instance_gain(player2.bigatk_Sound, 4); //調音量
    }
    //draw HP,SP image
    al_draw_bitmap(HP_picture[player2.HP / 10], 695, -145, 0);
    al_draw_bitmap(SP_picture[player2.SP / 10], 684, -155, 0); //更新技能條
}

void treasure_draw()
{ //畫出寶箱;
    al_draw_bitmap(img_tr, treasure.x, treasure.y, 0);
    //printf("draw treasure\n");
}

int encounter(Character player)
{
    if (treasure.exist == false) //不存在
        return 0;
    //判斷寶箱方向
    if (player.x <= treasure.x) //player ... treasure
    {
        if (player.x + player.width > treasure.x + treasure.width / 2)
            return 1;
    }
    if (player.x > treasure.x) //treasure ... player
    {
        if (player.x + player.width / 2 < treasure.x + treasure.width)
            return 1;
    }
    return 0;
}

void character_destory()
{
    al_destroy_bitmap(player1.img_move_infor);
    for (int i = 0; i < 3; i++)
    {
        algif_destroy_animation(player1.img_atk[i]);
        algif_destroy_animation(player1.img_move[i]);
    }
    al_destroy_sample_instance(player1.atk_Sound);
    al_destroy_sample_instance(player1.bigatk_Sound);

    al_destroy_bitmap(player2.img_move_infor);
    for (int i = 0; i < 3; i++)
    {
        algif_destroy_animation(player2.img_atk[i]);
        algif_destroy_animation(player2.img_move[i]);
    }
    al_destroy_sample_instance(player2.atk_Sound);
    al_destroy_sample_instance(player2.bigatk_Sound);
    // destroy HP, SP image
    for (int i = 0; i <= 10; i++)
    {
        al_destroy_bitmap(HP_picture[i]);
        al_destroy_bitmap(SP_picture[i]);
    }

    al_destroy_bitmap(img_tr);
    al_destroy_sample_instance(trea_sound);
    //printf("success to destroy character\n");
}
