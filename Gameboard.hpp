#ifndef _GAMEBOARD_
#define _GAMEBOARD_
#include <unistd.h>
#include <list>
#include <iterator>
#include <algorithm>
#include "Cards.hpp"
#include "Player.hpp"

using std::string;

extern const unsigned int MAXPLAYERS;


class GameBoard {
private:
DeckBuilder* db;
std::list<Player*>* playersList;

void startingPhase();
void equipPhase();
void economyPhase();
void battlePhase();
bool finalPhase();

void connectHoldings(list<BlackCard*>*);
Player *checkWinningCondition() const;
void printArena(Player& pl) const;

public:
GameBoard(int=2);
~GameBoard();

void initializeGameBoard();
void printGameStatistics() const;

void gameplay();   // calls all phases for each player
};

#endif
