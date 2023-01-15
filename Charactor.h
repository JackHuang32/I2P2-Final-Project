#ifndef CHARARCTOR_H_INCLUDED
#define CHARARCTOR_H_INCLUDED

#include"Object.h"
#include<iostream>
#include<vector>
//For main player and NPC
typedef enum{UP,DOWN,LEFT,RIGHT,STOP,DIG} CharactorState;
class Charactor : public Object{
protected:
    CharactorState s;
    std::string image_path;
    double speed;
    std::vector<std::vector<int>>dir = {{0,-1},{0,1},{-1,0},{1,0}};
    //std::vector<ALLEGRO_BITMAP*> moveImg
    int width;
    int height;
    int point=0;
    void step(double dx,double dy);

public:
    Charactor(){};
    virtual ~Charactor();
    virtual void dig()=0;

    void Draw() override;
    void load_move();
    void set_state(CharactorState st) { s = st;}
    void set_speed(double s) { speed = s;}
    void add_point(int p) { point += p;}
    void set_point(int p) { point = p;}

    int get_point() { return point;}

    double get_speed() {return s;}

    bool valid_move(int dx,int dy);

    CharactorState get_state() {return s; }
};
#endif
