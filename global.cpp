#include "global.h"

/*int window_width = 800;
int window_height = 600;
int field_width = 600;
int field_height = 600;
int NumOfTower = 5;*/

int TowerRadius[] = {80, 80, 70, 110, 150};
char WasteClass[][20] = {"brick", "wire", "drink", "paper"};
int TowerWidth[] = {72, 66, 72, 59, 45};
int TowerHeight[] = {121, 108, 69, 98, 112};
int typesOfwaste = 4;

int rows = (int)field_height/grid_height;
int cols = (int)field_width / grid_width;
std::vector<std::vector<bool>>check_grid = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
std::vector<std::vector<Waste>>grid = std::vector<std::vector<Waste>>(rows, std::vector<Waste>(cols));

//Brick information begin
int Brick_w=50;
int Brick_h=50;
int Brick_v=10;
int Brick_n=20;
//Brick information end

//Wire information begin
int Wire_w=50;
int Wire_h=50;
int Wire_v=15;
int Wire_n=20;
//Wire information end

//Drink information begin
int Drink_w=50;
int Drink_h=50;
int Drink_v=12;
int Drink_n=20;
//Drink information end

//Paper information begin
int Paper_w=50;
int Paper_h=50;
int Paper_v=-100;
int Paper_n=2;
//Paper information end

int npc_sourceX = 78;

int hint = 6;
int score = 0;
int waste_num = Brick_n+Wire_n+Drink_n+Paper_n;
std::vector<int>typeNum ={Brick_n, Wire_n, Drink_n, Paper_n};
std::vector<Waste> waste_set;
void draw_waste()
{
    for (int i=0; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            if (check_grid[i][j] && grid[i][j].found())
                grid[i][j].Draw();
        }
    }
}
void init_grid()
{
    std::vector<std::pair<int,int>>ind;
    std::set<std::pair<int,int>>ind_set;
    srand(time(nullptr));
    //generate random coord
    std::cout<<"generating random coordinates"<<std::endl;
    while(waste_num > (int)ind_set.size())
    {
        int tmpx = rand()%rows;
        int tmpy = rand()%cols;
        auto coord = std::make_pair(tmpx,tmpy);
        if(ind_set.find(coord)==ind_set.end())
        {
            ind_set.insert(coord);
            ind.push_back(coord);
        }

    }
    std::cout<<"finish generating random coordinates"<<std::endl;
    for(WasteType t = BRICK;t<=PAPER; t = WasteType(t+1))
    {
        std::cout<<"t:"<<t<<std::endl;
        while(typeNum[t]--)
        {
            auto coord = ind.back();
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

                    break;
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
                    break;
                    //grid[tmpx][tmpy].PrintInfo();
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
                    break;
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
                    break;
                //std::cout<<"generating paper"<<std::endl;

            }
            //print_grid();
           //waste_set.push_back(grid[tmpx][tmpy]);
            ind.pop_back();
        }
    }
}
void print_grid()
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            if(check_grid[i][j] && grid[i][j].get_type() == 3) grid[i][j].PrintInfo();
        }
    }
}
void set_empty(int x,int y)
{
    //check_grid[x][y] = false;
}

int get_waste_value(int x,int y)
{
    return grid[x][y].get_value();
}

bool isfull(int x,int y)
{
    return check_grid[x][y];
}

bool map_empty(){
     for (int i=0; i<rows ; i++){
        for (int j=0 ; j<cols ; j++){
            if (check_grid[i][j] && !grid[i][j].found())
                return false;
        }
     }
     return true;
}
