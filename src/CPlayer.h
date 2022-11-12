#pragma once

#include "CGame.h"
#include <memory>
#include "CCard.h"
#include <vector>


/** @brief Abstract Class used to maintain Player object.

    This class stores data of a player. His hp, mana, gold, attack, card limit and his cards in his hands.

    @author David Rohusch @rohusdav
    @date June 2021
    */

class CGame;

class CPlayer{
protected:
    int hp;
    int mana;
    int gold;
    int attack;
    vector<shared_ptr<CCard>> hand; /// Vector of player's cards.
    unsigned int cardMax = 6;       /// Card limit

    weak_ptr<CPlayer> enemyPlayer;  /// Pointer to the enemy player

public:
    CPlayer(int hp, int mana, int gold, int attack);

    bool playCard( int cardNumber );                                 /// Plays a card by the index of position in the hand.
    bool addCard (const shared_ptr<CCard> &card);                    /// Adds a card to the hand
    virtual string whatAmI ( ) const;
    virtual void goToDungeon(CGame *pGame) = 0;
    virtual void playing(CGame *game) = 0;
    void attackPlayer ( const shared_ptr<CPlayer> &src , int dmg );  /// Attacks 'enemyPlayer' object
    void applyEffect (const int &hpself, const int &dmgself, const int &goldself, const int &manaself);  /// Applies effects to the player

    void setEnemy ( shared_ptr<CPlayer> &enemy ); /// Sets a pointer to the enemy

    bool save(const string &filename);            /// Saves itself to filename
    void setCardLimit(const int &n);              /// Sets a new card limit

    bool dead () const ;                          /// Returtns true if HP <= 0
};