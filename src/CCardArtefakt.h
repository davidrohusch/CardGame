#pragma once

#include "CCard.h"
#include "SEffect.h"


/** @brief Class used to identify card as Artiffact.

    Cards are paid by player's gold to play.
    @author David Rohusch @rohusdav
    @date June 2021
    */


class CCardArtefakt : public CCard{
public:
    CCardArtefakt (const string &name, const string &desc, const SEffect &effect);   // constructor, který uloží detaily o kartě.

    //! Sends card information to stream
    /*!
      \param os    ostream
      \return returns stream containing information about card.
    */
    ostream& printCard (ostream &os)      const;
    //! Checks if gold is >= than the price
    /*!
      \sa SEffect().price
      \param mana
      \param gold
      \return returns gold >= cardPrice;
    */
    bool canBePlayed (int mana, int gold) const;
    //! Decreases gold by Price value
    /*!
      \sa SEffect().price
      \param mana
      \param gold
      \return void;
    */
    void payPrice    (int &mana, int &gold);

    //! Returns "Gold"
    /*!
      \return "Gold";
    */
    string price () const;
};