#include <string>
#include <iostream>
#include "CDeck.h"
#include "CGame.h"
#include <curses.h>
#include "CPlayerComputer.h"
#include "CPlayerHuman.h"
#include <memory>
#include <fstream>


using namespace std;


CGame::CGame(int hpMax, int manaMax, int startGold, int startAttack) : hpMax(hpMax), manaMax(manaMax),
                                                                       startGold(startGold), startAttack(startAttack) {
    isRunning = true;
    inMenu = true;
    round = 0;

}

bool CGame::menu() {
    int selection = 0;
    if (!inMenu) return false;

    cout << "Zadejte volbu:\n1)Zacit novou hru proti pocitaci\n2)Zacit novou hru proti hraci.\n3)Nahrat existujici hru\n4)ukoncit hru\n";

    cin >> selection;


    if (selection == 1) {
        inMenu = false;
        newGamePC();
    }
    if (selection == 2) {
        inMenu = false;
        newGame();
    }

    if (selection == 3) {
        inMenu = false;
        if (!loadGame()) {
            cout << "\n\n\n\n\n\n\n\nERROR LOADING FILE";
            endGame();
        };
    }

    if (selection == 4) {
        inMenu = false;
        endGame();
    }

    return true;
}

void CGame::load() {
    if (!deck.loadCards("")) {

        cout << "Error, soubory s kartama obsahuje chybu." << endl
             << "Mozne chyby:\n-Soubor s kartama se nejmenuje cardlist.txt\n-Soubor s balickem se nejmenuje decklist.txt"
             << endl << "-Soubory obsahují syntatickou chybu.\n";

        endGame();
        ///print error a ukončit hru
    }

}

void CGame::newGame() {
    round = 0;
    playerOne = make_shared<CPlayerHuman>(hpMax, manaMax, startGold, startAttack);
    playerTwo = make_shared<CPlayerHuman>(hpMax, manaMax, startGold, startAttack);
    for (int i = 0; i < 4; i++) {
        bool a = drawCard(playerOne);
        bool b = drawCard(playerTwo);

        if (!(a || b)) {
            cout << "ERROR";
            endGame();
        }
    }
}

void CGame::newGamePC() {

    round = 0;
    playerOne = make_shared<CPlayerHuman>(hpMax, manaMax, startGold, startAttack);
    playerTwo = make_shared<CPlayerComputer>(hpMax, manaMax, startGold, startAttack);

    playerOne->setEnemy(playerTwo);
    playerTwo->setEnemy(playerOne);
    for (int i = 0; i < 4; i++) {

        bool a = drawCard(playerOne);
        bool b = drawCard(playerTwo);

        if (!(a || b)) {
            cout << "ERROR";
            endGame();
        }
    }


}


bool CGame::loadGame() {
    ifstream setting;

    setting.open("settings.sav");

    if (setting.is_open()) {

        setting >> round;
        setting.close();

        deck.clear();

        if (!deck.loadCards("cards.sav")) {

            return false;
        };

        ifstream decksave;
        decksave.open("deck.sav");
        if (decksave.is_open()) {
            string line;
            while (getline(decksave, line)) {
                if (!deck.returnCard(stoi(line))) {
                    decksave.close();
                    return false;
                }
            }
        } else {
            decksave.close();
            return false;
        }

        ifstream p1, p2;
        p1.open("playerOne.sav");
        p2.open("playerTwo.sav");
        if (p1.is_open() && p2.is_open()) {
            string line, whoAmI;
            int hp, mana, gold, attack, cmax;
            getline(p1, line);
            whoAmI = line;
            getline(p1, line);
            hp = stoi(line);
            getline(p1, line);
            mana = stoi(line);
            getline(p1, line);
            gold = stoi(line);
            getline(p1, line);
            attack = stoi(line);
            getline(p1, line);
            cmax = stoi(line);

            if (whoAmI == "HUMAN")
                playerOne = make_shared<CPlayerHuman>(hp, mana, gold, attack);
            else if (whoAmI == "PC")
                playerOne = make_shared<CPlayerComputer>(hp, mana, gold, attack);
            else {
                p1.close();
                p2.close();
                return false;
            }

            playerOne->setCardLimit(cmax);
            while (getline(p1, line)) {
                if ((size_t) stoi(line) > deck.getDeck().size()) {
                    p1.close();
                    p2.close();
                    return false;
                }
                giveCard(playerOne, deck.getDeck()[stoi(line)]);
            }


            getline(p2, line);
            whoAmI = line;
            getline(p2, line);
            hp = stoi(line);
            getline(p2, line);
            mana = stoi(line);
            getline(p2, line);
            gold = stoi(line);
            getline(p2, line);
            attack = stoi(line);
            getline(p2, line);
            cmax = stoi(line);

            if (whoAmI == "HUMAN")
                playerTwo = make_shared<CPlayerHuman>(hp, mana, gold, attack);
            else if (whoAmI == "PC")
                playerTwo = make_shared<CPlayerComputer>(hp, mana, gold, attack);
            else {
                p1.close();
                p2.close();
                return false;
            }

            playerTwo->setCardLimit(cmax);
            while (getline(p1, line)) {
                if ((size_t) stoi(line) > deck.getDeck().size()) {
                    p1.close();
                    p2.close();
                    return false;
                }
                giveCard(playerTwo, deck.getDeck()[stoi(line)]);
            }


            playerOne->setEnemy(playerTwo);
            playerTwo->setEnemy(playerOne);
        } else {
            p1.close();
            p2.close();
            return false;
        }


    } else {

        return false;
    }
    inMenu = false;
    isRunning = true;

    return true;
}

void CGame::endGame() {

    isRunning = false;
    inMenu = false;


}

bool CGame::running() const {
    return isRunning;
}


void CGame::step() {


    if (!(round % 2)) {
        cout << "Hrac 1: na rade" << endl;
        playerOne->playing(this);
    }
    if(playerOne->dead()){
        cout << "\n\n\n\n\n\n HRAC 2 VITEZI ! ! ! ";
        endGame();
    }
    if (!isRunning) return;

    if (round % 2) {
        cout << "Hrac 2: na rade" << endl;
        playerTwo->playing(this);
    }
    if(playerTwo->dead()){
        cout << "\n\n\n\n\n\n HRAC 1 VITEZI ! ! ! ";
        endGame();
    }
    if (!isRunning) return;

    round++;
}


bool CGame::saveGame() {
    if (!saveCards()) return false;
    if (!saveSettings()) return false;
    if (!savePlayers()) return false;

    return true;
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


bool CGame::saveCards() {

    if (!deck.saveCardsToFile("cards.sav")) return false;
    if (!deck.saveDeckToFile("deck.sav")) return false;

    return true;
}


bool CGame::saveSettings() {
    ofstream save;
    save.open("settings.sav");

    if (save.is_open()) {
        save << round;
    } else {
        save.close();
        return false;
    }

    save.close();
    return true;
}


bool CGame::savePlayers() {
    if (!playerOne->save("playerOne.sav")) return false;
    if (!playerTwo->save("playerTwo.sav")) return false;
    return true;
}

