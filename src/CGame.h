#pragma once



#include <string>
#include "CDeck.h"
#include "CPlayer.h"


using namespace std;

/** @brief Class used to maintain the main game logic.

    This class maintain everything in the game.
    Starting a new game
    loading and old game from savefile
    And some other tweaks with cards.

    @author David Rohusch @rohusdav
    @date June 2021
    */


class CPlayer;

class CGame {
private:
    int hpMax, manaMax, startGold, startAttack;

    shared_ptr<CPlayer> playerOne, playerTwo; /// Creates 2 players
    bool isRunning;                           /// Returns if the game is still running
    bool inMenu;                              /// Returns if the game is inside of the menu
    CDeck deck;                               /// List of all cards and deck
    unsigned int round;                       /// Let's you know whose turn it is now


    bool loadGame();      /// Loads the game from savefiles

    void newGame();       /// Starts a new game with player vs player

    void newGamePC();     /// Starts a new game with player vs computer


    bool saveSettings();  /// Saves whose round it is now inside of a file

    bool saveCards();     /// Saves all cards inside a file

    bool savePlayers();   /// Saves information about a player into a file

public:
    bool saveGame();      /// Saves everything

    CGame(int hpMax, int manaMax, int startGold, int startAttack);

    void step();          /// Game-step

    void endGame();       /// Ends the game

    bool running() const; /// Returns if the game is still running

    void load();          /// Load cards inside the deck

    bool menu();          /// Pre-game menu

    bool giveCard(const shared_ptr<CPlayer> &src, const shared_ptr<CCard> &card);  /// Gives a src player a card

    bool drawCard(const shared_ptr<CPlayer> &src);                                 /// Draw a card from the top of the deck to player's hand

    shared_ptr<CCard> randomCard();                /// Returns random card from the list of cards

    void drawCard(vector<shared_ptr<CCard>> &src); /// Gives player a card from the top of the deck.
};

