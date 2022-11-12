#pragma once

#include <memory>
#include "CCard.h"
#include <vector>
#include "CPlayer.h"
#include <curses.h>

/** @brief  Class used to maintain Player object controlled by human.

    This class let's you controll the player in the game.

    @author David Rohusch @rohusdav
    @date June 2021
    */

class CPlayerHuman : public CPlayer {
protected:
    void goToDungeon(WINDOW *w, CGame *pGame);                            /// Gives randomly : 'new card to the hand' OR 'Applies effects on player' OR  'Gives random amount of gold'

public:
    CPlayerHuman(int hp, int mana, int gold, int attack);

    string whatAmI() const;                                  /// Returns string "Human"

    virtual void playing(CGame *pGame);                         /// Let's you control the player ingame.
};