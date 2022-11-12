#pragma once

#include<memory> //shared_ptr
#include<vector>
#include"CCard.h"
#include "SEffect.h"

using namespace std;

/** @brief Class used to store deck and card data.

    This class stores database of loaded cards from file. These cards are used to create a deck of cards.

    @author David Rohusch @rohusdav
    @date June 2021
    */

class CDeck {
private:
    vector<shared_ptr<CCard>> cardList; /*!< Card's name database of all loaded cards */
    vector<shared_ptr<CCard>> deck;     /*!< database of loaded cards inside of the deck */
public:
    CDeck() = default;
    //! Returns the most top card and removes it from the deck.
    /*!
      \sa CCard
      \return Returns the most top card and removes it from the deck.
    */
    shared_ptr<CCard> drawCard   ();
    //! Returns random card from the card database
    /*!
      \sa CCard
      \return Returns random card from the card database
    */
    shared_ptr<CCard> randomCard ()               const;
    //! Returns card from carddatabase by index
    /*!
      \sa CCard
      \pram index
      \return Returns card from carddatabase by index
    */
    shared_ptr<CCard> getCardByIndex (int index)  const;

    //! Load cards into database
    /*!
      \pram filename
      \return void
    */
    void loadCards (const string &filename);
    //! Load deck into database
    /*!
      \pram filename
      \return void
    */
    void loadDeck  (const string &filename);

    //! Saves all cards listed inside of cardList into filename
    /*!
      \pram filename
      \return void
    */
    void saveCardsToFile (const string &filename) const;
    //! Saves card's indexes of all cards inside deck into filename
    /*!
      \pram filename
      \return void
    */
    void saveDeckToFile  (const string &filename) const;
    //! Adds a card to the deck.
    /*!
      \pram src Card
      \return void
    */
    void returnCard (shared_ptr<CCard> &src);
    //! Adds a card to the deck by the index from card database
    /*!
      \pram index
      \return true if it'S succseful
    */
    bool returnCard (int index);
    //!Removes all records
    /*!
      \return void
    */
    void clear ();                                 /// Removes all records
    //! Returns size of cardlist database
    /*!
      \return Returns size of cardlist database
    */
    int cardListSize () const;


};