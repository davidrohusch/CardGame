#pragma once

#include "CCard.h"

/** @brief Class used to identify card as Spell.

    Cards are paid by player's mana to play.
    @author David Rohusch @rohusdav
    @date June 2021
    */

class CCardSpell : public CCard{
public:
    CCardSpell (const string &name, const string &desc, const SEffect &effect);  // constructor, který uloží detaily o kartě.
    //! Sends card information to stream
    /*!
      \param os    ostream
      \return returns stream containing information about card.
    */
    ostream& printCard (ostream &os)      const;  ///prints itself to stream

    //! Checks if mana is >= than the price
    /*!
      \sa SEffect().price
      \param mana
      \param gold
      \return returns mana >= cardPrice;
    */
    bool canBePlayed (int mana, int gold) const;  ///returns true if gold > price of the card
    //! Decreases mana by Price value
    /*!
      \sa SEffect().price
      \param mana
      \param gold
      \return void;
    */
    void payPrice (int &mana, int &gold);         /// gold - price

    //! Returns "Mana"
    /*!
      \return "Mana";
    */
    string price () const;
};