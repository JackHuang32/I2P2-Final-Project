#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <list>
#include <time.h>
#include "Menu.h"
#include "Level.h"
#include "NPC.h"
#include "MainPlayer.h"

#include "Attack.h"
#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7

// clock rate
const float FPS = 60;

// total number of level
const int LevelNum = 4;

// 1 coin every 2 seconds
const int CoinSpeed = FPS * 2;
const int Coin_Time_Gain = 1;

class GameWindow
{
public:
    // constructor
    GameWindow();
    // each process of scene
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();

    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();

    // each drawing scene function
    void draw_running_map();

    // process of updated event
    int process_event();
    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);
    // detect if a tower will be constructed on road
    bool isOnRoad();

    //Tower* create_tower(int);
    //Monster* create_monster();

public:
    bool initial = true;

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *waste[Num_WasteType];
    ALLEGRO_BITMAP *background = NULL;

    ALLEGRO_BITMAP* player;
    ALLEGRO_BITMAP* npc_graph;
    ALLEGRO_BITMAP* win_graph;
    ALLEGRO_BITMAP* lose_graph;
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *npc_timer = NULL;
    ALLEGRO_TIMER *npc_move_timer = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *hintSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *hintSoundgirl = NULL;
    ALLEGRO_SAMPLE_INSTANCE *digSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *correctSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *wrongSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *paperSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *winSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *loseSound = NULL;

    //player
    MainPlayer gamer;

    //NPC
    NPC npc;


    LEVEL *level = NULL;
    Menu *menu = NULL;

    int Monster_Pro_Count = 0;
    int Coin_Inc_Count = 0;
    int mouse_x, mouse_y;
    int selectedTower = -1, lastClicked = -1;
    int sourceX = 78;
    bool flagforhint=false;

    bool redraw = false;
    bool mute = false;
};


#endif // MAINWINDOW_H_INCLUDED
