#include <iostream>
#include <string>
#include "CGame.h"
#include <curses.h>


using namespace std;



int main(){
    initscr();
    clear();
    noecho();

    CGame game(30   , 10, 10, 5);

    game.load();

    while(game.menu());

    while (game.running()){

        game.step();
    }

    endwin();

    return 0;
}