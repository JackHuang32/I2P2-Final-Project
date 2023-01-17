#include "Menu.h"
#include "MainPlayer.h"
#include "global.h"

const int ThumbWidth = 50;
const int ThumbHeight = 50;
const int gapX = 40, gapY = 30;
const int offsetX = 30 + field_width, offsetY = 150;
int hint_res;
int dig;

bool
Menu::Waste_Found(int type)
{

    if(type < 0 || type >= Num_WasteType)
        return false;

    return (waste_found[type] >= 0);
}

Menu::Menu()
{
    char filename[50];


    for(int i=0;i<Num_WasteType; i++)
    {
        ALLEGRO_BITMAP *waste;
        sprintf(filename, "./Tower/%s.png", WasteClass[i]);

        waste = al_load_bitmap(filename);
        menu_waste.push_back(waste);
    }

    light = al_load_bitmap("./Tower/light.png");

    menuFont = al_load_ttf_font("pirulen.ttf", 12, 0); // load font
}

Menu::~Menu()
{
    al_destroy_bitmap(light);
    al_destroy_font(menuFont);

    for(int i=0; i < Num_WasteType; i++)
        al_destroy_bitmap(menu_waste[i]);

    menu_waste.clear();
}

void
Menu::Reset()
{
    hint_res = -1;
}

void
Menu::Draw()
{
    char buffer[50];

    sprintf(buffer, ": %d", hint);
    al_draw_bitmap(light, offsetX, 10, 0);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), al_get_bitmap_width(light) + offsetX, 20, 0, buffer);

    sprintf(buffer, "Score: %d", score);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 20 + 1.5*gapY, 0, buffer);

    sprintf(buffer, "Dig: %d", dig);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 20 + 3*gapY, 0, buffer);

    sprintf(buffer, "near: %d", hint_res);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 20 + 4.5*gapY, 0, buffer);

    for(int i=0; i < Num_WasteType; i++)
    {
        int pos_x = offsetX + (ThumbWidth + gapX) * (i % 2);
        int pos_y = offsetY + (ThumbHeight + gapY) * (i / 2);
        pos_y += 1.5*gapY;

        al_draw_bitmap(menu_waste[i], pos_x, pos_y, 0);
        if(!Waste_Found(i))
            al_draw_filled_rectangle(pos_x, pos_y , pos_x + ThumbWidth, pos_y + ThumbHeight , al_map_rgba(100, 100, 100, 100));
        else if(i == selectedTower)
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 0, 0), 0);
        else
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 255, 255), 0);
    }
}


void
Menu::Gain_Score(int scoreWorth)
{
    killedMonster++;

}



