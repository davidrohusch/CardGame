#include "CPlayerHuman.h"
#include <curses.h>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <string>


CPlayerHuman::CPlayerHuman(int hp, int mana, int gold, int attack) : CPlayer(hp, mana, gold, attack) {
}

string CPlayerHuman::whatAmI() const {
    return "HUMAN";
}

void CPlayerHuman::goToDungeon(CGame *pGame) {
    srand(time(0));
    int goldgain = rand() % 10 + 1;
    int buffgain = rand() % 3 + 1;
    shared_ptr<CCard> randCard = pGame->randomCard();
    string dialog;



    int action = rand() % 3;
    switch(action){
        case(0):
            ///random card

            if(addCard( randCard)) {
                dialog = "Nalezl jsi tuto vecicku pod kamenem : " + randCard->getName();
                printDialog(dialog);
            }else{
                dialog = "Nalezl jsi tuto vecicku pod kamenem : " + randCard->getName() + ". Ale tve kapsy jsou prilis plne!";
                printDialog(dialog);
            }
            break;

        case(1):

            applyEffect(0,0,goldgain,0);
            dialog = "Narazil jsi na trolla, ktery vytrousil  : " + to_string(goldgain) + " zlataku.";
            printDialog(dialog);
            ///random gold
            break;
        case(2):

            applyEffect(buffgain,buffgain,0,0);
            dialog = "objevil jsi svatyni, po napiti se ze dzbanu si pripadas silnejsi." ;
            printDialog(dialog);
            ///random buff
            break;
    }


}

void CPlayerHuman::playing(CGame *game) {
    bool turn = true;
    char ch;
    mana+=2; //give player some mana

    cout << "zivoty: " << hp << "  utok: " << attack << "  zlataky: " << gold << "  mana:  " << mana;
    cout << "\n\n" << "Cislem vyber moznost, a nebo pismenem kartu" << endl;

    char zn = 'a';
    for(const auto &i : hand){
        cout << zn << ") " << i->getName() << endl;
        zn++;
    }
    cout << endl  << endl << "1) lizni kartu 2) Jdi do dungeonu 3) zautoc na nepritele 4) uloz hru 5) ukonci hru " << endl;
    shared_ptr<CPlayer> spFoo = enemyPlayer.lock();

    while(turn){


        cin >> ch;

       switch(ch){
           case '1':
               if(cardMax > hand.size()){
                   game->drawCard( hand );
                   printDialog("Liznul sis kartu, konec kola!");
                   turn = false;
               }else{
                   printDialog("Neudrzis tolik karet v ruce najednou");
               }

               break;
           case '2':
               goToDungeon(game);
               turn = false;
               break;
           case '3':
               attackPlayer(spFoo,attack);
               printDialog("Zpusobil jsi nepriteli : " + to_string(attack) + " poskozeni, a tim skoncil tvuj tah.");
               turn = false;
              break;
           case '4':
                if (game->saveGame())
                printDialog("Ulozeno");
                else{
                    printDialog("Zli carodejove ti zamitli ulozeni hry! (Nastala chyba pri ukladani)");
                }
               break;
           case '5':
               game->endGame();
               turn = false;
               break;

       }

        if(ch >= 'a' && ch<='z'){
            if (showCardInfo(hand[ch - 'a'], (ch - 'a'))) {
                turn = false;
            };
        }

    }
}

void CPlayerHuman::printDialog(const string &dialog) const {
    cout << dialog << endl;
}

bool CPlayerHuman::showCardInfo(shared_ptr<CCard> &card, int index) {
    cout << "\n\n\n" << card->getName() << "\n" << card->getDesc() << "\n\n";
    cout << "Cena : " << card->getEffect().price << "Zvyseni zdravi o : " << card->getEffect().hpSelf
         << " Zvyseni poskozeni o : " << card->getEffect().dmgSelf << endl
         << "Snizeni zdravi nepritele o : " << card->getEffect().hpEnemy << " Snizeni utoku nepritele o : "
         << card->getEffect().dmgEnemy << endl;

    cout << "Pro zahrati napis 1, zpatky do menu 2" << endl;


    while (1) {
        int ch = 0;
        cin >> ch;

        if(ch==1){
            if(card->canBePlayed(mana, gold)) {

                cout << "Zahral jsi " << hand[index]->getName() << " a zpusobil jsi tim: " << endl
                     << "Zvyseni svych zivotu o " << to_string(hand[index]->getEffect().hpSelf) << " bodu."
                     << "Zvyseni sve sily o " << to_string(hand[index]->getEffect().dmgSelf) << " bodu."
                     << "Snizeni nepritolovo zdravi o  " << to_string(hand[index]->getEffect().hpEnemy) << " bodu."
                     << "Snizeni nepratelskeho utoku o " << to_string(hand[index]->getEffect().dmgEnemy) << " bodu.";
                cout << endl;
                playCard(index);
                hand.erase(hand.begin() + index);
                return true;
            }else{
                cout << "Nedostatek zdroju" << endl;

            }
        }
        if(ch==2){
            return false;
        }
    }
}


