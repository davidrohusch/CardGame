#pragma once

#include <memory>
#include "CCard.h"
#include <vector>
#include "CPlayer.h"

/** @brief  Class used to maintain Player object controlled by human.

    This class let's you controll the player in the game.

    @author David Rohusch @rohusdav
    @date June 2021
    */



class CPlayerHuman : public CPlayer{
private:

public:
     CPlayerHuman(int hp, int mana, int gold, int attack);

     string whatAmI ( ) const;                                  /// Returns string "Human"
     void goToDungeon(CGame *pGame);                            /// Gives randomly : 'new card to the hand' OR 'Applies effects on player' OR  'Gives random amount of gold'

     virtual void playing(CGame *game);                         /// Let's you control the player ingame.

     void printDialog(const string &dialog) const ;             /// Prints a message.

     bool showCardInfo (shared_ptr<CCard> &card , int index) ;  /// Prints more info about your card and lets you play it

};