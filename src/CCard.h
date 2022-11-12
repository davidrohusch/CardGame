#pragma once
#include <iostream>
#include <string>
#include "SEffect.h"
#include <memory>

using namespace std;



/** @brief Abstract class used to store cards.

    This class stores name, description and effect of the card.
    @author David Rohusch @rohusdav
    @date June 2021
    */


class CCard{
protected:
    string name;
    string desc;
    SEffect effect;

public:
    /*   getters */
    const SEffect &getEffect() const;
    const string &getName() const;
    const string &getDesc() const;
    const int &getID() const;

    CCard( const string &name, const string &description, const SEffect &effect );
    ~CCard() = default;

    virtual void payPrice ( int &mana, int &gold ) = 0;
    virtual bool canBePlayed(int mana, int gold) const = 0;
    virtual ostream& printCard (ostream &os) ; ///Print card on the stream


};