//
// Created by david on 10.06.2021.
//

#include <fstream>

#include "CPlayer.h"
#include "CPlayerHuman.h"
#include "CPlayerComputer.h"
#include "CPlayerComputerExpert.h"


void CSaveSystem::loadSettings(const string &fname, unsigned int &round) {
    ifstream setting;
    unsigned int n ;
    setting.open(fname);
    if (setting.is_open()) {
        setting >> round;
        setting.close();
    }
    else {
        setting.close();
        throw""; }
    setting.close();
    return ;
}

void CSaveSystem::loadDeckFromSave(const string &fname , CDeck &deck) {

    ifstream decksave;
    decksave.open("deck.sav");
    if (decksave.is_open()) {
        string line;
        while (getline(decksave, line)) {
            if (! deck.returnCard(stoi(line))) {
                decksave.close();
                throw"";
            }
        }
    }else {
        decksave.close();
        throw"";
    }
    return ;
}
shared_ptr<CPlayer> CSaveSystem::makePlayerFrom(const string &fname , CDeck &deck){
    shared_ptr<CPlayer> player;
    ifstream p1;
    p1.open(fname);

    if (p1.is_open()) {
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

        if(cmax <=0) throw"";

        if (whoAmI == "HUMAN")
            player = make_shared<CPlayerHuman>   (hp, mana, gold, attack);
        else if (whoAmI == "PC")
            player = make_shared<CPlayerComputer>(hp, mana, gold, attack);
        else if (whoAmI == "EXPERT")
            player = make_shared<CPlayerComputerExpert>(hp, mana, gold, attack);
        else {
            p1.close();
            throw"";
        }

        player->setCardLimit(cmax);
        while (getline(p1, line)) {
            if ((size_t) stoi(line) > deck.cardListSize()) {
                p1.close();
                throw"";
            }
            player->addCard(deck.getCardByIndex(stoi(line)));

        }
        return player;

    }
    else
        throw "";
}

void CSaveSystem::loadGame(CDeck &deck, shared_ptr<CPlayer> &playerOne, shared_ptr<CPlayer> &playerTwo , bool &inMenu , bool &inGame, unsigned int &round) {

    loadSettings("settings.sav", round);

    deck.clear();
    deck.loadCards("cards.sav");
    loadDeckFromSave("deck.sav",deck);

    playerOne = makePlayerFrom("playerOne.sav",deck);
    playerTwo = makePlayerFrom("playerTwo.sav",deck);

    playerOne->setEnemy(playerTwo );
    playerTwo->setEnemy(playerOne );

    inMenu = false;
    inGame = true;

    return;
}


void CSaveSystem::saveGame(const CDeck &deck, const unsigned int &round, const shared_ptr<CPlayer> &playerOne, const shared_ptr<CPlayer> &playerTwo) const {
    saveCards(deck);
    saveSettings(round);
    savePlayers(playerOne, playerTwo);

    return;
}



void CSaveSystem::saveCards(const CDeck &deck) const{

    deck.saveCardsToFile("cards.sav");
    deck.saveDeckToFile ("deck.sav");

    return ;
}


void CSaveSystem::saveSettings(const unsigned int &round) const {
    ofstream save;
    save.open("settings.sav");


    if (save.is_open()) {
        save << round;
    } else {
        save.close();
        throw "";
    }

    save.close();
    return ;
}


void CSaveSystem::savePlayers(const shared_ptr<CPlayer> &playerOne , const shared_ptr<CPlayer> &playerTwo) const {
    playerOne->save("playerOne.sav");
    playerTwo->save("playerTwo.sav");
    return;
}










