#include"MainPlayer.h"
#include"global.h"
void MainPlayer::dig()
{   
    this->set_state(DIG);
    //use one chance to dig
    this->Dec_chance();
    //dig the grid with waste otherwise return
    if(isfull( this->get_gridx(),this->get_gridy() ))
    {
        //mark the waste empty
        set_empty(this->get_gridx(),this->get_gridy());
        //add point to the charactor
        this->add_point(get_waste_value(
            this->get_gridx(),this->get_gridy()
                )
            );
    }
    else
    {
        return;
    }
    
}
void MainPlayer::moveUp()
{
    //key_state[] is a boolean global array
    //of size ALLEGRO_KEY_MAX
    this->set_state(UP);
    if(this->valid_move(dir[UP][0],dir[UP][1]))
    {
        step(dir[UP][0]*speed,dir[UP][1]*speed);
    }
}
void MainPlayer::moveDown()
{
    //key_state[] is a boolean global array
    //of size ALLEGRO_KEY_MAX
    this->set_state(DOWN);
    if(this->valid_move(dir[DOWN][0],dir[DOWN][1]))
    {
        step(dir[DOWN][0]*speed,dir[DOWN][1]*speed);
    }
}
void MainPlayer::moveLeft()
{
    //key_state[] is a boolean global array
    //of size ALLEGRO_KEY_MAX
    this->set_state(LEFT);
    if(this->valid_move(dir[LEFT][0],dir[LEFT][1]))
    {
        step(dir[LEFT][0]*speed,dir[LEFT][1]*speed);
    }
}
void MainPlayer::moveRight()
{
    //key_state[] is a boolean global array
    //of size ALLEGRO_KEY_MAX
    this->set_state(RIGHT);
    if(this->valid_move(dir[RIGHT][0],dir[RIGHT][1]))
    {
        step(dir[RIGHT][0]*speed,dir[RIGHT][1]*speed);
    }
}
void MainPlayer::PrintInfo()
{
    std::cout<<"------------"<<"MainPlayer Info"<<"----------"<<std::endl;
    std::cout<<"posx: "<<get_posx()<<std::endl;
    std::cout<<"posy: "<<get_posy()<<std::endl;
    std::cout<<"gridx: "<<get_gridx()<<std::endl;
    std::cout<<"gridy: "<<get_gridy()<<std::endl;
    std::cout<<"hint: "<<get_hint()<<std::endl;
    std::cout<<"goal: "<<get_goal()<<std::endl;
    std::cout<<"------------------END----------------------"<<std::endl;
}

int MainPlayer::use_hint()
{
    if(!this->haveHint())return -1;
    this->Dec_hint();
    int count = 0;
    int cur_x = this->get_gridx();
    int cur_y = this->get_gridy();
    for(int x=cur_x-1 ; x<=cur_x+1 ; x++)
    {
        for(int y=cur_y-1 ; y<=cur_y+1 ; y++)
        {
            if(x<0 || x>=rows || y<0 || y>=cols)
            {
                continue;
            }
            else if(check_grid[x][y] && !grid[x][y].found())
            {
                count++;
            }
        }
    }
    return count;
}