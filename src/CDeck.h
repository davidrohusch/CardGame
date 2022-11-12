#pragma once

#include<memory> //shared_ptr
#include<vector>
#include"CCard.h"
#include "SEffect.h"


/** @brief Class used to store deck and card data.

    This class stores database of loaded cards from file. These cards are used to create a deck of cards.

    @author David Rohusch @rohusdav
    @date June 2021
    */

using namespace std;




class CDeck {
private:

    vector<shared_ptr<CCard>> cardList; ///database of all loaded cards
    vector<shared_ptr<CCard>> deck;     ///database of loaded cards inside of the deck
public:
    vector<shared_ptr<struct CCard>> &getDeck();  ///getter
    CDeck() = default;

    bool loadCards(const string &filename);       /// Load cards and deck into database
    bool loadDeck(const string &filename);
    shared_ptr<CCard> drawCard();                 /// Returns the most top card and removes it from the deck
    shared_ptr<CCard> randomCard();               /// Returns random card from the card database

    bool saveCardsToFile(const string &filename); /// Saves all cards listed inside of cardList into filename
    bool saveDeckToFile(const string &filename);  /// Saves card's indexes of all cards inside deck into filename



    void clear();                                 /// Removes all records
    void returnCard(shared_ptr<CCard> &src);      /// Adds a card to the deck.
    bool returnCard(int index);                   /// Adds a card to the deck by the index from card database
};