#include"NPC.h"
#include<ctime>

void NPC::move()
{
    //generate random direction to move
    srand(time(nullptr));
    CharactorState st;
    st = static_cast<CharactorState>(rand()%4);
    int dx = dir[st][0];
    int dy = dir[st][1];
    this->set_state(st);
    //move if the step is not out of range otherwise return
    if(this->valid_move(dx,dy))
    {
        this->set_state(st);
        this->step(dx * speed,dy * speed);
    }
    else
    {
        return;
    }
}
bool NPC::dig()
{
    //dif the grid with waste otherwise return
    if(isfull( this->get_gridx(),this->get_gridy() ))
    {
        //mark the waste empty
        //set_empty(this->get_gridx(),this->get_gridy());
        //add point to the charactor
        grid[get_gridx()][get_gridy()].set_discovered();
        this->add_point(get_waste_value(
            this->get_gridx(),this->get_gridy()
                )
            ); 
        return true;
    }
    else
    {
        printf("NPC: no waste\n");
        return false; 
    }
}
void NPC::update()
{
    Inc_count();
    if(dig_time())
    {
        //reset count
        set_count(0);
        this->dig();
    }
    else
    {
        move();
    }
}
void NPC::PrintInfo()
{
    std::cout<<"------------"<<"NPC Info"<<"----------"<<std::endl;
    std::cout<<"posx: "<<get_posx()<<std::endl;
    std::cout<<"posy: "<<get_posy()<<std::endl;
    std::cout<<"gridx: "<<get_gridx()<<std::endl;
    std::cout<<"gridy: "<<get_gridy()<<std::endl;
    std::cout<<"------------------END----------------------"<<std::endl;

}