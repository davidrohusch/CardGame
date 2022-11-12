#include <string>
#include <iostream>
#include "CDeck.h"
#include "CGame.h"
#include <curses.h>
#include "CPlayerComputer.h"
#include "CPlayerHuman.h"
#include <memory>
#include <fstream>
#include "CPlayerComputerExpert.h"
#include "Graphics.h"


using namespace std;


CGame::CGame(int hpMax, int manaMax, int startGold, int startAttack) : hpMax(hpMax), manaMax(manaMax),
                                                                       startGold(startGold), startAttack(startAttack) {

    isRunning = true;
    inMenu = true;
    round = 0;

}



bool CGame::menu() {
    if (!inMenu) return false;

    int highlight = 1;
    int choice = 0;
    int startx = (80 - 10) / 2;
    int starty = (24 - 10) / 2;
    int c;

    WINDOW *menu_win = newwin(10, 40, starty, startx);
    keypad(menu_win, TRUE);
    refresh();

    vector<string> choices;
    choices.emplace_back("New Game against Expert computer");
    choices.emplace_back("New Game against computer");
    choices.emplace_back("New Game against human");
    choices.emplace_back("Load game");
    choices.emplace_back("Exit");

    print_menu(menu_win, highlight, choices);

    while(1)
    {
        c = wgetch(menu_win);
        switch(c)
        {	case KEY_UP:
                if(highlight == 1)
                    highlight = choices.size();
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == choices.size())
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                refresh();
                break;
        }
        print_menu(menu_win, highlight, choices);
        if(choice != 0)
            break;
    }

    clear();

    switch(choice){
        case 1:
            inMenu = false;
            playerOne = make_shared<CPlayerHuman>(hpMax, manaMax, startGold, startAttack);
            playerTwo = make_shared<CPlayerComputerExpert>(hpMax, manaMax, startGold, startAttack);
            newGame(playerOne, playerTwo);
            break;
        case 2:
            inMenu = false;
            playerOne = make_shared<CPlayerHuman>(hpMax, manaMax, startGold, startAttack);
            playerTwo = make_shared<CPlayerComputer>(hpMax, manaMax, startGold, startAttack);
            newGame(playerOne, playerTwo);
            break;
        case 3:
            inMenu = false;
            playerOne = make_shared<CPlayerHuman>(hpMax, manaMax, startGold, startAttack);
            playerTwo = make_shared<CPlayerHuman>(hpMax, manaMax, startGold, startAttack);
            newGame(playerOne, playerTwo);
            break;
        case 4:
            inMenu = false;

            try{
                saveHandler.loadGame(deck, playerOne, playerTwo, inMenu, isRunning, round);
            }catch(...)
            {
                clear();
                mvprintw(24, 0, "Error loading savefile.");
                inMenu = true;
                isRunning = false;
            }
            break;
        case 5:
            inMenu = false;
            endGame();
            break;
    }

    return true;
}


void CGame::step() {
    int startx = (80 ) / 2;
    int starty = (24 ) / 2;

    WINDOW *w = newwin(4, 20, starty, startx);

    keypad(w, TRUE);
    refresh();

    if (winCheck()) return;

    if (!(round % 2)) {
        printBox(w,"Player 1 - start");
        refresh();
        getch();
        clear();
        playerOne->playing(this);
    }

    if (winCheck()) return;

    if (round % 2) {
        printBox(w,"Player 2 - start");
        refresh();
        getch();
        clear();
        playerTwo->playing(this);
    }

    round++;

}


void CGame::load() {

    try{
      deck.loadCards("cardlist.txt");

      deck.loadDeck ("decklist.txt");
    }
    catch (const char *e)
    {
        mvprintw(15, 30, "Error loading cardlist.txt and decklist.txt");
        getch();
        endGame();
    }

}

void CGame::newGame(shared_ptr<CPlayer> &A , shared_ptr<CPlayer> &B) {
    round = 0;
    playerOne->setEnemy(playerTwo);
    playerTwo->setEnemy(playerOne);
    for (int i = 0; i < 4; i++) {
       drawCard(playerOne);
       drawCard(playerTwo);
    }
}

void CGame::endGame() {
    isRunning = false;
    inMenu = false;
}

bool CGame::running() const {
    return isRunning;
}


bool CGame::winCheck() {
    if(playerOne->dead()){
        clear();
        printw("PLAYER 2 WINS !");
        getch();

        endGame();
    }
    if(playerTwo->dead()){
        clear();
        printw("PLAYER 1 WINS !");
        getch();

        endGame();
    }
    if (!isRunning) return true;
    else return false;
}




bool CGame::giveCard(const shared_ptr<CPlayer> &src, const shared_ptr<CCard> &card) {
    if (!(src->addCard(card))) return false;
    return true;
}

bool CGame::drawCard(const shared_ptr<CPlayer> &src) {
    shared_ptr<CCard> card = deck.drawCard();

    if (!giveCard(src, card)) {
        deck.returnCard(card);
        return false;
    }

    return true;
}


void CGame::drawCard(vector<shared_ptr<CCard>> &src) {
    shared_ptr<CCard> card = deck.drawCard();

    src.push_back(card);

}


shared_ptr<CCard> CGame::randomCard() {

    return deck.randomCard();
}



void CGame::setStatus(bool mn, bool run) {
    inMenu = mn;
    isRunning = run;
}



void CGame::saveGame() const {
    saveHandler.saveGame(deck, round, playerOne, playerTwo);
}

