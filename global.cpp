#include "global.h"
#include<set>
#include<stdlib.h>
#include<ctime>
/*int window_width = 800;
int window_height = 600;
int field_width = 600;
int field_height = 600;
int NumOfTower = 5;*/

int TowerRadius[] = {80, 80, 70, 110, 150};
char WasteClass[][20] = {"brick", "wire", "drink", "paper", "Storm_Menu"};
int TowerWidth[] = {72, 66, 72, 59, 45};
int TowerHeight[] = {121, 108, 69, 98, 112};
int typesOfwaste = 4;
//int waste_num = 4;
int rows = (int)field_height/grid_height;
int cols = (int)field_width / grid_width;
std::vector<std::vector<bool>>check_grid = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
std::vector<std::vector<Waste>>grid = std::vector<std::vector<Waste>>(rows, std::vector<Waste>(cols));
//Brick information begin
int Brick_w=50;
int Brick_h=50;
int Brick_v=1;
int Brick_n=2;
//Brick information end

//Wire information begin
int Wire_w=50;
int Wire_h=50;
int Wire_v=1;
int Wire_n=2;
//Wire information end

//Drink information begin
int Drink_w=50;
int Drink_h=50;
int Drink_v=1;
int Drink_n=2;
//Drink information end

//Paper information begin
int Paper_w=50;
int Paper_h=50;
int Paper_v=1;
int Paper_n=2;
//Paper information end
int waste_num = Brick_n+Wire_n+Drink_n+Paper_n;

void init_grid(std::vector<int>typeNum)
{
    std::set<std::pair<int,int>>ind;
    srand(time(nullptr));
    //generate random coord
    std::cout<<"generating random coordinates"<<std::endl;
    while(waste_num > (int)ind.size())
    {   
        int tmpx = rand()%rows;
        int tmpy = rand()%cols;
        auto coord = std::make_pair(tmpx,tmpy);   
        ind.insert(coord);
    }
    std::cout<<"finish generating random coordinates"<<std::endl;
    for(WasteType t = BRICK;t<=PAPER; t = WasteType(t+1))
    {
        std::cout<<"t:"<<t<<std::endl;
        while(typeNum[t]--)
        {
            auto coord = *ind.begin();
            int tmpx = coord.first;
            int tmpy = coord.second;
            check_grid[tmpx][tmpy] = true;
            switch (t){
                case BRICK:
                //std::cout<<"generating brick"<<std::endl;
                    grid[tmpx][tmpy] = Waste(
                            tmpx,
                            tmpy,
                            Brick_w,
                            Brick_h,
                            t,
                            Brick_v
                    );
                //std::cout<<"finish generating brick"<<std::endl;    
                case WIRE:
                //std::cout<<"generating wire"<<std::endl;
                    grid[tmpx][tmpy] = Waste(
                            tmpx,
                            tmpy,
                            Wire_w,
                            Wire_h,
                            t,
                            Wire_v
                    );
                //std::cout<<"finish generating wire"<<std::endl;
                case DRINK:
                //std::cout<<"generating drink"<<std::endl;
                    grid[tmpx][tmpy] = Waste(
                            tmpx,
                            tmpy,
                            Drink_w,
                            Drink_h,
                            t,
                            Drink_v
                    );
                //std::cout<<"generating drink"<<std::endl;
                case PAPER:
                //std::cout<<"generating paper"<<std::endl;
                    grid[tmpx][tmpy] = Waste(
                            tmpx,
                            tmpy,
                            Paper_w,
                            Paper_h,
                            t,
                            Paper_v
                    );
                //std::cout<<"generating paper"<<std::endl;    
            }
            waste_set.push_back(grid[tmpx][tmpy]);
            ind.erase(coord);
        }
    }    
}
void print_grid()
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(check_grid[i][j])grid[i][j].PrintInfo();
        }
    }
}
void set_empty(int x,int y)
{
    check_grid[x][y] = false;
}

int get_waste_value(int x,int y)
{
    return grid[x][y].get_value();
}

bool isfull(int x,int y)
{
    return check_grid[x][y];
}