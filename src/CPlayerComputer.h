#pragma once

#include "CPlayer.h"


/** @brief  Class used to maintain Player object controlled by Computer.

    This class plays itself inside the game.

    @author David Rohusch @rohusdav
    @date June 2021
    */


class CPlayerComputer : public CPlayer{
private:
    int countPlayableCards () const ;
public:
    CPlayerComputer(int hp, int mana, int gold, int attack);



     string whatAmI ( ) const;                              /// returns string "PC"
     void goToDungeon(CGame *pGame);                        /// Gives randomly : 'new card to the hand' OR 'Applies effects on player' OR  'Gives random amount of gold'
     void playing(CGame *game);                             /// The same as CPlayerHuman, but controlled by it's own value checker.
};