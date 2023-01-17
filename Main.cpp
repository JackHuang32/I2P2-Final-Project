#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow *digGame= new GameWindow();

    digGame->game_play();

    delete digGame;
    return 0;
}
