#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
//#include"global.h"
#include<iostream>
#include "Circle.h"

class Object {
public:
    Object() {}
    ~Object() {}

    // pure function for drawing object
    virtual void Draw() = 0;

    int getX() { return circle.x; }
    int getY() { return circle.y; }
    int get_gridx() { return gridx;}
    int get_gridy() { return gridy;}
    int getRadius() { return circle.r; }
    int get_width() { return width;}
    int get_height() { return height;}

    void set_posx(double x) {
        std::cout<<"begin set pos"<<std::endl;
         circle.x = x;
        std::cout<<"end set pos"<<std::endl; 
         }
    void set_posy(double y) { circle.y = y;}
    void set_gridx(int x) { gridx = x;}
    void set_gridy(int y) { gridy = y;}
    void set_width(int w) { width=w;}
    void set_height(int h) { height = h;}


    double get_posx() { return circle.x;}
    double get_posy() { return circle.y;}
    Circle getCircle() const { return circle; }
    static bool same_grid(Object* obj1,Object* obj2)
    {
        return obj1->gridx == obj2->gridx
            && obj1->gridy == obj2->gridy;
    }

    friend class Grid;
protected:
    Circle circle;
    int gridx;
    int gridy;
    int width;
    int height;

};

#endif // OBJECT_H_INCLUDED

