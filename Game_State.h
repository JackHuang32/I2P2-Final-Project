#ifndef GAME_STATE_H_INCLUDED
#define GAME_STATE_H_INCLUDED
//For State checking
typedef enum{LEVEL1,LEVEL2,LEVEL3,WIN,LOSE} GameState;

class Game_State{
private:
    GameState state;
public:
    Game_State(){}
    ~Game_State(){}
    bool isLevel1(){return state == LEVEL1;}
    bool isLevel2(){return state == LEVEL2;}
    bool isLevel3(){return state == LEVEL3;}
    bool isWIN(){return state == WIN;}
    bool isLOSE(){return state == LOSE;}
    void set_LEVEL1(){state = LEVEL1;}
    void set_LEVEL2(){state = LEVEL2;}
    void set_LEVEL3(){state = LEVEL3;}
    void set_WIN(){state = WIN;}
    void set_LOSE(){state = LOSE;}
};

#endif