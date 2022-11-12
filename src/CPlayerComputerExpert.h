#pragma once

#include "CPlayerComputer.h"

/** @brief  Class used to maintain Player object controlled by Computer with more difficult moves.

    This class plays itself inside the game.
    This varion got more moves to be more complex and clever.

    @author David Rohusch @rohusdav
    @date June 2021
    */

class CPlayerComputerExpert : public CPlayerComputer {
public:
    CPlayerComputerExpert(int hp, int mana, int gold, int attack);
    void playing(CGame *pGame);                     /// The same as CPlayerComputer, but with more unfair playing

    string whatAmI() const;                              /// returns string "EXTREME"


};