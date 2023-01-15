#include "Charactor.h"
//#include <allegro5/allegro.h>
//#include <allegro5/allegro_primitives.h>
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};
// set counter frequency of drawing moving animation
const int draw_frequency = 10;

void Charactor::Draw(){
    /*TODO*/

}
void Charactor::load_move()
{
   /*TODO*/
}
bool Charactor::valid_move(int dx,int dy)
{
    return this->width/2 + get_posx()+dx*speed > 0
        && this->width/2 + get_posx()+dx*speed < 500
        && this->height/2 + get_posy()+dy*speed > 0
        && this->height/2 + get_posy()+dy*speed < 500;
}
void Charactor::step(double dx,double dy)
{
    set_posx(get_posx()+dx);
    set_posy(get_posy()+dy);
    set_gridx( (int)(get_posx() * 500 / 500) );
    set_gridy( (int)(get_posy() * 500 / 500) );
}
Charactor::~Charactor()
{

}
