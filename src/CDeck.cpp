#include "CDeck.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "CCardSpell.h"
#include "CCardArtefakt.h"
#include <set>
#include <algorithm>    // std::random_shuffle
#include <ctime>


bool CDeck::loadDeck(const string &filename){


    int Q = 0;
    string line;
    ifstream deckListFile;

    if(filename=="")
         deckListFile.open("decklist.txt");
    else
        deckListFile.open(filename);


    if (deckListFile.is_open()) {
        set<int> tmp;
        while (getline(deckListFile, line)) {

            if (line[0]=='\r'  || line[0] == '\n') continue;
            if (line[0] == '#') continue;
            if (line[0] == '@') {
                Q = line[1] - '0';
                if (Q < 0) return false;
                continue;
            }
            int ID, n;
            stringstream ss;
            ss.clear();
            ss << line;
            ss >> ID >> n;


            if (ss.fail()) return false;
            tmp.insert(ID);

            for (int i = 0; i < n; i++) {
                deck.push_back(cardList[ID]);       //adds custom quantity of cards to the deck
            }

        }

        for (size_t i = 0; i < cardList.size(); i++) {
            if (tmp.find(i) != tmp.end()) continue;

            for (int k = 0; k < Q; k++) {
                deck.push_back(cardList[i]);
            }

        }


    } else return false;
    srand(std::time(0));
    random_shuffle(deck.begin(), deck.end());
    deckListFile.close();
    return true;
}

bool CDeck::loadCards(const string &filename) {
    ifstream cardListFile;

    if(filename==""){
         cardListFile.open("cardlist.txt");}
    else
         cardListFile.open(filename);

    string line;


    if (cardListFile.is_open()) {
        int tempID= 0;
        while (getline(cardListFile, line) ) {
            stringstream ss;
            string cardName;
            int cardType;
            SEffect effect{};
            string desc;

            if (line[0]=='\r'  || line[0] == '\n') continue;
            if (line[0] == '#') continue;                    /// # symbol is for comment.
            if (line[0] != '"') {                            /// Line is supposed to start with # or "
                return false;
            }
            int tmp = 0;
            for (size_t i = 1; i < line.length(); i++) {     /// " pairing
                if (line[i] == '"') {
                    tmp = i;
                    break;
                }
            }
            cardName = line.substr(1, tmp - 1);

            ss.clear();
            ss << line.substr(tmp + 1, line.length());
            ss >> cardType >> effect.price >> effect.hpSelf >> effect.dmgSelf >> effect.hpEnemy >> effect.dmgEnemy;

            if (ss.fail()) {
                //print error
                return false;
            }

            ss >> ws;
            getline(ss, desc);
            desc = desc.substr(1, desc.size() - 3);
            effect.ID = tempID;
            effect.cardValue = effect.hpSelf + effect.dmgSelf - effect.hpEnemy - effect.dmgEnemy;
            if (cardType == 1) {
                cardList.emplace_back(make_shared<CCardArtefakt>(cardName, desc, effect));
            }
            if (cardType == 2) {
                cardList.emplace_back(make_shared<CCardSpell>(cardName, desc, effect));
            }
            tempID++;
        }

        cardListFile.close();
        if(loadDeck("")) return true;
        else return false;

    }else
        return false;
}

shared_ptr<CCard> CDeck::drawCard() {


  if(deck.empty()){
      loadDeck("");
  };

  auto card = deck.back();

  deck.pop_back();
  return card;
}

shared_ptr<CCard> CDeck::randomCard() {

    return cardList[ ( rand() % cardList.size() )];
}

bool CDeck::saveCardsToFile(const string &filename) {
    ofstream save;
    save.open(filename);
    if(save.is_open()){
        for(const auto &i : cardList){
            i->printCard(save);
        }

    }else {
        save.close();
        return false;
    }

    save.close();
return true;
}

bool CDeck::saveDeckToFile(const string &filename) {
    ofstream save;
    save.open(filename);
    if(save.is_open()){
        for(const auto &i : deck){
            save << i->getID() << endl;
        }
    }else{
        save.close();
        return false;
    }
    save.close();
    return true;
}

void CDeck::returnCard(shared_ptr<CCard> &src) {
    deck.push_back(src);
}

void CDeck::clear() {
    cardList.clear();
    deck.clear();
}

vector<shared_ptr<struct CCard>> &CDeck::getDeck() {
    return deck;
}

bool CDeck::returnCard(int index) {
    if((size_t)index>cardList.size()) return false;
    deck.push_back(cardList[index]);
    return true;
}

