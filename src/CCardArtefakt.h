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
    CCardArtefakt(const string &name, const string &desc, const SEffect &effect);   // constructor, který uloží detaily o kartě.


    ostream& printCard (ostream &os);            ///prints itself to stream

    bool canBePlayed(int mana, int gold) const;  ///returns true if gold > price of the card
    void payPrice ( int &mana, int &gold );      /// gold - price
};