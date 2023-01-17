#include "Charactor.h"
#include "global.h"
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
    return this->width/2 + get_posx()+dx*speed > -25
        && this->width/2 + get_posx()+dx*speed < field_width-50
        && this->height/2 + get_posy()+dy*speed > -50
        && this->height/2 + get_posy()+dy*speed < field_height-80;
}
void Charactor::step(double dx,double dy)
{
    set_posx(get_posx()+dx);

    set_posy(get_posy()+dy);

    set_gridx( (int)(get_posy() / grid_width+1) );
    set_gridy( (int)(get_posx() / grid_height+1) );
}
Charactor::~Charactor()
{

}
