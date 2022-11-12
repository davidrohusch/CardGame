#pragma once

#include "CPlayer.h"


/** @brief  Class used to maintain Player object controlled by Computer.

    This class plays itself inside the game.

    @author David Rohusch @rohusdav
    @date June 2021
    */


class CPlayerComputer : public CPlayer {
protected:
    int countPlayableCards() const;

    void goToDungeon(WINDOW *w, CGame *pGame);                        /// Gives randomly : 'new card to the hand' OR 'Applies effects on player' OR  'Gives random amount of gold'
public:
    CPlayerComputer(int hp, int mana, int gold, int attack);


    virtual string whatAmI() const;                              /// returns string "PC"

    virtual void playing(CGame *pGame);                             /// The same as CPlayerHuman, but controlled by it's own value checker.
};