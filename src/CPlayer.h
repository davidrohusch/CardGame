#pragma once

#include "CGame.h"
#include <memory>
#include "CCard.h"
#include <vector>
#include <curses.h>


class CGame;

/** @brief Abstract Class used to maintain Player object.

    This class stores data of a player. His hp, mana, gold, attack, card limit and his cards in his hands.

    @author David Rohusch @rohusdav
    @date June 2021
    */


class CPlayer {
protected:
    int hp, mana, gold, attack;
    unsigned int cardMax = 6;       /// Card limit

    vector<shared_ptr<CCard>> hand; /// Vector of player's cards.
    weak_ptr<CPlayer> enemyPlayer;  /// Pointer to the enemy player

    void attackPlayer(const shared_ptr<CPlayer> &src, int dmg);  /// Attacks 'enemyPlayer' object
    void applyEffect(const int &hpself, const int &dmgself, const int &goldself,
                     const int &manaself);  /// Applies effects to the player
    virtual void goToDungeon(WINDOW *w,CGame *pGame) = 0;

public:
    CPlayer(int hp, int mana, int gold, int attack);

    ~CPlayer() = default;

    virtual void playing(CGame *pGame) = 0;

    virtual string whatAmI() const = 0;

    bool playCard(int cardNumber);                                 /// Plays a card by the index of position in the hand.
    bool addCard(const shared_ptr<CCard> &card);                    /// Adds a card to the hand
    bool save(const string &filename);            /// Saves itself to filename
    bool dead() const;                           /// Returtns true if HP <= 0

    void setEnemy(shared_ptr<CPlayer> &enemy); /// Sets a pointer to the enemy
    void setCardLimit(const int &n);              /// Sets a new card limit

    int getHP() const;                          /// Returns HP
};