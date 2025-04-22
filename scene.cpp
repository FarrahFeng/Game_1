#include "scene.h"
ALLEGRO_FONT *font = NULL;
//  內文字體用font_content存取(大小都30)
ALLEGRO_FONT *font_content = NULL;
//  標題字體用font_title存取(大小都50)
ALLEGRO_FONT *font_title = NULL;
ALLEGRO_BITMAP *menu_back = NULL;
ALLEGRO_SAMPLE *menu_sound_sample = NULL;
ALLEGRO_SAMPLE_INSTANCE *menu_Sound = NULL;
ALLEGRO_BITMAP *background_1_sample = NULL;
ALLEGRO_BITMAP *background_2_sample = NULL;

ALLEGRO_BITMAP *about_word = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *img_end = NULL;
ALLEGRO_SAMPLE *sample = NULL; //load sound instance
ALLEGRO_SAMPLE_INSTANCE *background_music = NULL;
int background_choice = 0; //兩種背景選擇

ALGIF_ANIMATION *character_1_sample = NULL;
ALGIF_ANIMATION *character_2_sample = NULL;
ALGIF_ANIMATION *character_3_sample = NULL;

ALGIF_ANIMATION *winner_sample = NULL;
int cnt = 0;

int start = 0;

// function of menu
void menu_init()
{
    font = al_load_ttf_font("./font/pirulen.ttf", 15, 0);
    font_content = al_load_ttf_font("./font/pirulen.ttf", 30, 0);
    //load pirun of size 50 to font_game_name
    font_title = al_load_ttf_font("./font/pirulen.ttf", 50, 0);
    about_word = al_load_bitmap("./image/about.png"); //load about word
    //laod character gif
    character_1_sample = algif_load_animation("./image/character/關羽/choose_chara.gif");
    character_2_sample = algif_load_animation("./image/character/曹操/choose_chara.gif");
    character_3_sample = algif_load_animation("./image/character/呂布/choose_chara.gif");

    menu_sound_sample = al_load_sample("./sound/menu_1.wav"); //load music
    menu_Sound = al_create_sample_instance(menu_sound_sample);
    al_set_sample_instance_playmode(menu_Sound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(menu_Sound, al_get_default_mixer());
}

void menu_process(ALLEGRO_EVENT event)
{
    if (event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if (event.keyboard.keycode == ALLEGRO_KEY_ENTER)
        {
            judge_next_window = true;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_B)
        { //選擇背景
            //printf("enter key B\n");
            judge_menu_next = true;
            start = 1;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_A)
        { //進入ABOUT
            //printf("enter key A \n");
            judge_menu_next = true;
            start = 2;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_C)
        { //選擇角色
            //printf("enter key C\n");
            judge_menu_next = true;
            start = 3;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_R)
        { //返回目錄
            //printf("enter keyboard R\n");
            judge_menu_next = true;
            start = 0; //這裏start=0才能讓進入menu draw時畫主畫面出來
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) //結束遊戲
            menu_destroy();
    }
    //進入選擇背景畫面，透過按鍵1,2選擇遊戲背景
    if (start == 1 && event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if (event.keyboard.keycode == ALLEGRO_KEY_1)
        {
            //printf("choose background1\n");
            background_choice = 1;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_2)
        {
            //printf("choose background2\n");
            background_choice = 2;
            //printf("success\n");
        }
    }
    //進入選擇角色畫面，透過按鍵1,2,3選擇遊戲角色
    if (start == 3 && event.type == ALLEGRO_EVENT_KEY_DOWN)
    { //player 1 choose
        //printf("player 1 choosing\n");
        if (event.keyboard.keycode == ALLEGRO_KEY_Q)
        {
            //printf("1 choose 1\n");
            main_character_1 = 1;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_W)
        {
            //printf("1 choose 2\n");
            main_character_1 = 2;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_E)
        {
            //printf("1 choose 3\n");
            main_character_1 = 3;
        }
        //player 2
        //printf("player 2 choosing\n");
        if (event.keyboard.keycode == ALLEGRO_KEY_I)
        {
            //printf("2 choose 1\n");
            main_character_2 = 1;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_O)
        {
            //printf("2 choose 2\n");
            main_character_2 = 2;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_P)
        {
            //printf("2 choose 3\n");
            main_character_2 = 3;
        }
    }
}

void menu_draw()
{
    al_set_sample_instance_gain(menu_Sound, 1); //調音量
    al_play_sample_instance(menu_Sound);

    if (start == 0)
    {
        //改變背景
        al_clear_to_color(al_map_rgb(139, 125, 107));
        al_draw_text(font_title, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - 280, ALLEGRO_ALIGN_CENTRE, "GAME");
        //寫主選單內容，寫入文字
        al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - 133, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
        al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - 33, ALLEGRO_ALIGN_CENTRE, "Press 'A' to about");
        al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 67, ALLEGRO_ALIGN_CENTRE, "Press 'B' to GAME BACKGROUND");
        al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 167, ALLEGRO_ALIGN_CENTRE, "Press 'C' to CHARACTER");
        al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 267, ALLEGRO_ALIGN_CENTRE, "Press 'Esc' to exit");
        //把方匡都先畫出來（5個）
        int i, rec_height_up = 195, rec_height_down = 254;
        for (i = 0; i < 5; i++)
        {
            al_draw_rectangle(WIDTH / 2 - 200, rec_height_up, WIDTH / 2 + 200, rec_height_down, al_map_rgb(255, 255, 255), 3);
            rec_height_up += 100;
            rec_height_down += 100;
        }
    }
    else if (start == 1) //選擇背景byB
    {
        menu_back = al_load_bitmap("./image/stage_1.png"); //選擇背景圖的背景（捲軸）
        al_draw_bitmap(menu_back, -130, -10, 0);
        //標題
        al_draw_text(font_title, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 - 280, ALLEGRO_ALIGN_CENTRE, "Choose the background");

        background_1_sample = al_load_bitmap("./image/background_1_sample.jpg");
        al_draw_bitmap(background_1_sample, WIDTH / 4 - 200, 190, 0); //可選的背景1
        al_draw_text(font, al_map_rgb(0, 0, 0), WIDTH / 4, 160, ALLEGRO_ALIGN_CENTRE, "background 1");
        background_2_sample = al_load_bitmap("./image/background_2_sample.jpg");
        al_draw_bitmap(background_2_sample, WIDTH / 2 + 30, 190, 0); //可選的背景2
        al_draw_text(font, al_map_rgb(0, 0, 0), 3 * WIDTH / 4, 160, ALLEGRO_ALIGN_CENTRE, "background 2");
        al_draw_text(font_content, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 + 160, ALLEGRO_ALIGN_CENTRE, "please press '1' or '2' to ");
        al_draw_text(font_content, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 + 195, ALLEGRO_ALIGN_CENTRE, "Choose the background '1' or '2'");
        al_draw_text(font, al_map_rgb(0, 0, 0), 183, HEIGHT - 100, ALLEGRO_ALIGN_CENTRE, "press 'r' to back to menu");
        //畫return的框框
        al_draw_rectangle(20, HEIGHT - 105, 350, HEIGHT - 75, al_map_rgb(0, 0, 0), 3);
    }
    else if (start == 2) //about
    {
        menu_back = al_load_bitmap("./image/stage_1.png"); //捲軸）
        al_draw_bitmap(menu_back, -130, -10, 0);
        //標題
        al_draw_text(font_title, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 - 280, ALLEGRO_ALIGN_CENTRE, "about");
        al_draw_bitmap(about_word, 125, 115, 0);
        al_draw_text(font, al_map_rgb(0, 0, 0), 183, HEIGHT - 100, ALLEGRO_ALIGN_CENTRE, "press 'r' to back to menu");
        //畫return的框框
        al_draw_rectangle(20, HEIGHT - 105, 350, HEIGHT - 75, al_map_rgb(0, 0, 0), 3);
    }
    else if (start == 3) //choose character
    {
        menu_back = al_load_bitmap("./image/stage_1.png"); //（捲軸）
        al_draw_bitmap(menu_back, -130, -10, 0);
        //標題
        al_draw_text(font_title, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 - 280, ALLEGRO_ALIGN_CENTRE, "Choose the character");
        //choose chara 的圖和字
        al_draw_bitmap(algif_get_bitmap(character_1_sample, al_get_time()), 5 * WIDTH / 48, 180, 0); //可選的角色1
        al_draw_text(font, al_map_rgb(0, 0, 0), 5 * WIDTH / 24, 160, ALLEGRO_ALIGN_CENTRE, "character 1");
        al_draw_bitmap(algif_get_bitmap(character_2_sample, al_get_time()), 1 * WIDTH / 3, 180, 0); //可選的角色1
        al_draw_text(font, al_map_rgb(0, 0, 0), 11 * WIDTH / 24, 160, ALLEGRO_ALIGN_CENTRE, "character 2");
        al_draw_bitmap(algif_get_bitmap(character_3_sample, al_get_time()), 15 * WIDTH / 24, 180, 0); //可選的角色1
        al_draw_text(font, al_map_rgb(0, 0, 0), 25 * WIDTH / 32, 160, ALLEGRO_ALIGN_CENTRE, "character 3");
        al_draw_text(font_content, al_map_rgb(0, 0, 0), 590, HEIGHT / 2 + 95, ALLEGRO_ALIGN_CENTRE, "*player1 please press 'q' or 'w' or 'e' to ");
        al_draw_text(font_content, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 + 125, ALLEGRO_ALIGN_CENTRE, "Choose the character '1' or '2' or '3'");
        al_draw_text(font_content, al_map_rgb(0, 0, 0), 582, HEIGHT / 2 + 165, ALLEGRO_ALIGN_CENTRE, "*player2 please press 'i' or 'o' or 'p' to ");
        al_draw_text(font_content, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 + 195, ALLEGRO_ALIGN_CENTRE, "Choose the character '1' or '2' or '3'");

        al_draw_text(font, al_map_rgb(0, 0, 0), 183, HEIGHT - 100, ALLEGRO_ALIGN_CENTRE, "press 'r' to back to menu");
        //畫return的框框
        al_draw_rectangle(20, HEIGHT - 105, 350, HEIGHT - 75, al_map_rgb(0, 0, 0), 3);
    }
}
void menu_destroy()
{
    al_destroy_font(font);
    al_destroy_font(font_title);
    al_destroy_bitmap(menu_back);
    al_destroy_bitmap(about_word);
    al_destroy_bitmap(background_1_sample);
    al_destroy_bitmap(background_2_sample);
    algif_destroy_animation(character_1_sample);
    algif_destroy_animation(character_2_sample);
    algif_destroy_animation(character_3_sample);

    //al_destroy_bitmap(img);
}
// function of game_scene
void game_scene_init()
{
    character_init();
    if (background_choice == 1)
    {
        background = al_load_bitmap("./image/background_1.jpg");
        //load music
        sample = al_load_sample("./sound/back_music1.wav");
    }
    else
    {
        background = al_load_bitmap("./image/background_2.jpg");
        sample = al_load_sample("./sound/back_music2.wav");
    }

    //設定背景音樂
    background_music = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(background_music, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(background_music, al_get_default_mixer());

    img_end = al_load_bitmap("./image/gameover.jpg");
}
void game_scene_draw()
{

    if (judge_gameover == false)
    {
        al_draw_bitmap(background, 0, 0, 0);
        al_stop_sample_instance(menu_Sound);

        al_draw_rectangle(130, 23, 304, 32, al_map_rgb(222, 184, 135), 20); //hp sp player 的框框
        al_draw_rectangle(10, 57, 51, 71, al_map_rgb(222, 184, 135), 15);
        al_draw_rectangle(10, 91, 51, 105, al_map_rgb(222, 184, 135), 15);
        al_draw_rectangle(876, 23, 1060, 32, al_map_rgb(222, 184, 135), 20);
        al_draw_rectangle(759, 57, 802, 71, al_map_rgb(222, 184, 135), 15);
        al_draw_rectangle(759, 91, 802, 105, al_map_rgb(222, 184, 135), 15);

        al_draw_text(font_content, al_map_rgb(0, 0, 0), 222, 10, ALLEGRO_ALIGN_CENTRE, "player 1 ");
        al_draw_text(font_content, al_map_rgb(0, 0, 0), 975, 10, ALLEGRO_ALIGN_CENTRE, "player 2 ");
        al_draw_text(font_content, al_map_rgb(0, 0, 0), 30, 45, ALLEGRO_ALIGN_CENTRE, "HP");
        al_draw_text(font_content, al_map_rgb(0, 0, 0), 30, 80, ALLEGRO_ALIGN_CENTRE, "SP");
        al_draw_text(font_content, al_map_rgb(0, 0, 0), 780, 45, ALLEGRO_ALIGN_CENTRE, "HP");
        al_draw_text(font_content, al_map_rgb(0, 0, 0), 780, 80, ALLEGRO_ALIGN_CENTRE, "SP");

        al_set_sample_instance_gain(background_music, 0.5); //調音量
        al_play_sample_instance(background_music);

        character_draw();
    }
    else
    {
        al_stop_sample_instance(background_music);
        al_set_sample_instance_gain(menu_Sound, 1); //調音量
        al_play_sample_instance(menu_Sound);
        font_title = al_load_ttf_font("./font/pirulen.ttf", 50, 0);

        if (cnt < 100)
        {
            al_draw_bitmap(img_end, -80, 0, 0);
            cnt++;
        }
        else
        { //畫人

            al_clear_to_color(al_map_rgb(139, 125, 107));
            al_draw_text(font_title, al_map_rgb(139, 0, 0), WIDTH / 2, 100, ALLEGRO_ALIGN_CENTRE, "WINNER");
            if (winner == 1)
            {
                if (main_character_1 == 1)
                    winner_sample = algif_load_animation("./image/character/關羽/choose_chara.gif");
                else if (main_character_1 == 2)
                    winner_sample = algif_load_animation("./image/character/曹操/choose_chara.gif");
                else if (main_character_1 == 3)
                    winner_sample = algif_load_animation("./image/character/呂布/choose_chara.gif");
                al_draw_bitmap(algif_get_bitmap(winner_sample, al_get_time()), 450, 200, 0);
                al_draw_text(font_title, al_map_rgb(139, 0, 0), WIDTH / 2 + 1, 500, ALLEGRO_ALIGN_CENTRE, "PLAYER 1");
            }
            else if (winner == 2)
            {
                if (main_character_2 == 1)
                    winner_sample = algif_load_animation("./image/character/關羽/choose_chara.gif");
                else if (main_character_2 == 2)
                    winner_sample = algif_load_animation("./image/character/曹操/choose_chara.gif");
                else if (main_character_2 == 3)
                    winner_sample = algif_load_animation("./image/character/呂布/choose_chara.gif");
                al_draw_bitmap(algif_get_bitmap(winner_sample, al_get_time()), 445, 200, 0);
                al_draw_text(font_title, al_map_rgb(139, 0, 0), WIDTH / 2 + 1, 500, ALLEGRO_ALIGN_CENTRE, "PLAYER 2");
            }
        }
    }

    //al_flip_display();
}
void game_scene_destroy()
{
    al_destroy_sample_instance(menu_Sound);
    al_destroy_bitmap(background);
    al_destroy_sample_instance(background_music);
    al_destroy_bitmap(img_end);
    al_destroy_font(font_content);
    al_destroy_font(font_title);
    character_destory();
}
