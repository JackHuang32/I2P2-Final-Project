#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

//#include <allegro5/allegro_font.h>
#include <vector>
#include"Waste.h"

#define font_size 12
#define grid_width 50
#define grid_height 50

#define window_width 1000
#define window_height 600
#define field_width 800
#define field_height 600
//
#define Num_WasteType 4
#define Num_MonsterType 4
#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)


extern int TowerRadius[];
extern char WasteClass[][20];
extern int TowerWidth[];
extern int TowerHeight[];

extern int typesOfwaste;
extern int waste_num;
extern int rows;
extern int cols;
//Brick information begin
extern int Brick_w;
extern int Brick_h;
extern int Brick_v;
extern int Brick_n;
//Brick information end

//Wire information begin
extern int Wire_w;
extern int Wire_h;
extern int Wire_v;
extern int Wire_n;
//Wire information end

//Drink information begin
extern int Drink_w;
extern int Drink_h;
extern int Drink_v;
extern int Drink_n;
//Drink information end

//Paper information begin
extern int Paper_w;
extern int Paper_h;
extern int Paper_v;
extern int Paper_n;
//Paper information end

extern std::vector<std::vector<bool>> check_grid;
extern std::vector<std::vector<Waste>> grid;
extern std::vector<Waste> waste_set;
extern void init_grid(std::vector<int>typeNum);
extern void print_grid();
extern void set_empty(int x,int y);                             

extern int get_waste_value(int x,int y);

extern bool isfull(int x,int y);
#endif // GLOBAL_H_INCLUDED
