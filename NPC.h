#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED
#include"Charactor.h"
#include"global.h"
class NPC : public Charactor{
private:
    static std::string NPC_Impath;
    //after count time of move, NPC will dig
    int time_;
    int count=0;
public:
    NPC(){}
    NPC(int x,int y,int w,int h,int t)
    {
        set_gridx(x);
        set_gridy(y);
        set_width(w);
        set_height(h);
        set_time(t);
        set_posx((y+0.5)*grid_width);
        set_posy((x+0.5)*grid_height);
    }
    void PrintInfo();
    //step to a random direction
    void move();
    //decide if move() or dig()
    void update();
    void set_time(int t_) { time_ = t_;}
    void set_count(int c) {count = c;}
    void Inc_count() { count++;}

    int get_count() { return count;}
    int get_time() { return time_;}

    bool dig()override;
    bool dig_time() { return get_time() == get_count();}
    //void step(double dx,double dy)override;
};
#endif
