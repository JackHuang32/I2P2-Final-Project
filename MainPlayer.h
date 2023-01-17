#ifndef MAINPLAYER_H_INCLUDED
#define MAINPLAYER_H_INCLUDED
#include"Charactor.h"
#include"global.h"

#include<vector>
class MainPlayer : public Charactor{
private:
    //number of hint
    int hint;
    //goal to make to next map
    int goal;
    //number of chance to dig
    int chance;
    static std::string player_Impath;
public:
    //parameters gridx,gridy,width ,height, hint amounts
    //goals, dig chances
    MainPlayer(){}
    MainPlayer(int x,int y,int w,int h,int hint_,int g,int ch)
    {
        set_gridx(x);
        set_gridy(y);
        set_width(w);
        set_height(h);
        set_hint(hint_);
        set_chance(ch);
        set_goal(g);
        set_posx((y+0.5)*grid_width);
        set_posy((x+0.5)*grid_height);
    }

    void set_hint(int h) { hint = h;}
    void set_goal(int g) { goal = g;}
    void set_chance(int c) { chance = c;}
    void Inc_chance() {chance++;}
    void Dec_chance() {chance--;}
    void Inc_hint() {hint++;}
    void Dec_hint() {hint--;}
    bool dig() override;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void PrintInfo();

    int get_goal() { return goal;}
    int get_hint() { return hint;}
    int use_hint();
    bool haveHint() { return hint>0;}
    int get_chance() { return chance;}

    bool isWin() { return goal <= point;}
    bool isLose() { return chance <= 0;}
};
#endif
