#include <iostream>
#include <string>
#include "CGame.h"
#include <curses.h>


using namespace std;



int main(){

    CGame game(100, 10, 10, 5);

    game.load();

    while(game.menu());

    while (game.running()){

        game.step();
    }

    game.endGame();






    return 0;
}