#ifndef WASTE_H_INCLUDED
#define WASTE_H_INCLUDED
#include<string>
#include<iostream>
#include<vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include"Object.h"


typedef enum {DISCOVERED,COVERED} WasteState;
typedef enum {BRICK,WIRE,DRINK,PAPER} WasteType;
class Waste :public Object{
protected:
    WasteState s = COVERED;
    WasteType t;
    int value;
    bool discovered;
    ALLEGRO_BITMAP* img;
    std::vector<ALLEGRO_BITMAP*> waste_graph;

public:
    Waste(){}
    Waste(int x,int y,int w,int h,WasteType t,int v);
    WasteState get_state() { return s;}
    WasteType get_type() { return t;}
    void set_discovered() { s = DISCOVERED;}
    void set_covered() { s = COVERED;}
    void set_value(int v) { value = v;}
    void set_type(WasteType t_) { t = t_;}
    void Draw() override;
    void PrintInfo();

    int get_value() { return value;}

    bool found() { return s == DISCOVERED;}

    //friend class Grid;
};
#endif
