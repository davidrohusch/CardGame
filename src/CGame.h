#pragma once

#include <string>
#include "CDeck.h"
#include "CPlayer.h"
#include "CSaveSystem.h"

using namespace std;


class CPlayer;

/** @brief Class used to maintain the main game logic.

    This class maintain everything in the game.
    Starting a new game
    loading and old game from savefile
    And some other tweaks with cards.

    @author David Rohusch @rohusdav
    @date June 2021
    */

class CGame {
protected:
    CSaveSystem saveHandler;                   /*!< Save/Load hadnler */
    CDeck deck;                                /*!< Database of cards and deck */
    shared_ptr<CPlayer> playerOne, playerTwo;  /*!< Two players */

    int hpMax, manaMax, startGold, startAttack;/*!< Stats */
    unsigned int round;                        /*!< Round number */

    bool isRunning;                           /*!< Boolean if the game is running  */
    bool inMenu;                              /*!< Boolean if the game is in menu  */

    //! Starts a new game
    /*!
      \sa CPlayer
      \pram A
      \pram B
      \return void
    */
    void newGame(shared_ptr<CPlayer> &A, shared_ptr<CPlayer> &B);       ///
    //! Checks if playerOne or playerTwo are death
    /*!
      \sa CPlayer
      \return Returns true if one of the players have won
    */
    bool winCheck();
    //! Ends the game
    /*!
      \return void
    */
    void endGame();
public:
    CGame(int hpMax, int manaMax, int startGold, int startAttack);
    //! Saves the game
    /*!
      \return void
    */
    void saveGame() const;
    //! Returns if the game is running
    /*!
      \return Returns if the game is running
    */
    bool running() const;
    //! Main Menu handler.
    /*!
      \return Returns false if menu is supposed to end
    */
    bool menu();           /// Pre-game menu
    //! Gives card to player
    /*!
      \sa CCard
      \sa CPlayer
      \pram src Player
      \pram card Card
      \return Returns true if it succeeds
    */
    bool giveCard(const shared_ptr<CPlayer> &src, const shared_ptr<CCard> &card);
    //! Draws a card from top of the deck and gives it to player
    /*!
      \sa CCard
      \sa CPlayer
      \pram src Player
      \return returns true if it succeeds
    */
    bool drawCard(const shared_ptr<CPlayer> &src);
    //! Main game logic loop handler
    /*!
      \return void
    */
    void step();
    //! Loads cards and the deck
    /*!
      \sa CCard
      \sa CDeck
      \return void
    */
    void load();
    //! Draw a card from top of the deck and pushes it into hand
    /*!
      \sa CCard
      \sa CPlayer
      \pram src vector of cards in hand
      \return void
    */
    void drawCard(vector<shared_ptr<CCard>> &src); /// Gives player a card from the top of the deck.
    //! sets game status
    /*!
      \pram menu
      \pram run
      \return void
    */
    void setStatus(bool menu, bool run);
    //! Gives random card from card database
    /*!
      \sa CCard
      \return Returns random card from card database
    */
    shared_ptr<CCard> randomCard();
};

