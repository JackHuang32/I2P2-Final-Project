#include"Waste.h"
#include"global.h"
Waste::Waste(int x,int y,int w,int h,WasteType t,int v)
{
    set_gridx(x);
    set_gridy(y);
    set_width(w);
    set_height(h);
    set_posx( ((double)x+0.5) * grid_width );
    set_posy( ((double)y+0.5) * grid_height );
    set_covered();
    set_value(v);
    set_type(t);
}

void Waste::PrintInfo()
{
    std::string name;
    if (this->t == BRICK)name = "Brick";
    if (this->t == WIRE)name = "Wire";
    if (this->t == DRINK)name = "Drink";
    if (this->t == PAPER)name = "Paper";

    std::cout<<"------------"<<name+" Info"<<"----------"<<std::endl;
    std::cout<<"posx: "<<get_posx()<<std::endl;
    std::cout<<"posy: "<<get_posy()<<std::endl;
    std::cout<<"gridx: "<<get_gridx()<<std::endl;
    std::cout<<"gridy: "<<get_gridy()<<std::endl;
    if(this->found())std::cout<<"DICOVERED!"<<std::endl;
    else std::cout<<"COVERED!"<<std::endl;
    std::cout<<"------------------END----------------------"<<std::endl;

}

void Waste::Draw()
{
    /*TODO*/
}
