#pragma once
#include <string>
#include <memory>
#include "CPlayer.h"
#include "CGame.h"

using namespace std;

class CGame;
class CPlayer;

/** @brief  Save system class. Saves/Loads the game.

    This class is able to save the progress of the game to 5 seperated save files.
    And also to load them back into the game.

    @author David Rohusch @rohusdav
    @date June 2021
    */

class CSaveSystem{
private:
    void loadSettings(const string &fname, unsigned int &round); /// Loads settings from file.

    void loadDeckFromSave(const string &fname , CDeck &deck); /// Loads cards to deck from savefile.

    shared_ptr<CPlayer> makePlayerFrom(const string &fname , CDeck &deck); /// Create player from savefile;

    void saveSettings(const unsigned int &round) const;  /// Saves whose round it is now inside of a file

    void saveCards(const CDeck &deck) const ;     /// Saves all cards inside a file

    void savePlayers(const shared_ptr<CPlayer> &playerOne , const shared_ptr<CPlayer> &playerTwo) const;   /// Saves information about a player into a file

public:
    CSaveSystem() = default;

    ~CSaveSystem() = default;

    void saveGame(const CDeck &deck, const unsigned int &round, const shared_ptr<CPlayer> &playerOne, const shared_ptr<CPlayer> &playerTwo) const;      /// Saves everything

    void loadGame(CDeck &deck, shared_ptr<CPlayer> &playerOne, shared_ptr<CPlayer> &playerTwo , bool &inMenu , bool &inGame, unsigned int &round);     /// Loads the game from savefiles
};