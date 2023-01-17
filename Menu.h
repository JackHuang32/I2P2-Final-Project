#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Object.h"
#include "Circle.h"
#include "global.h"

class Menu : public Object
{
public:
    Menu();
    virtual ~Menu();

    void Reset();
    void Draw();

    static bool isInRange(int, int, int);

    // Check if current coin is not less than needed coin
    bool Waste_Found(int);
    //void Change_Coin(int change) { Coin += change; }
    bool Subtract_Hint(int escapeNum = 1);
    void Gain_Score(int);

    //int getTowerCoin(int type) { return need_coin[type]; }

    int getKilled() { return killedMonster; }

private:
    std::vector<ALLEGRO_BITMAP*> menu_waste;
    ALLEGRO_BITMAP *light = NULL;
    ALLEGRO_FONT *menuFont;
    int killedMonster = 0;
    int selectedTower = -1;
    int waste_found[Num_WasteType] = {1, 1, 1, 1};
};

#endif // MENU_H_INCLUDED

