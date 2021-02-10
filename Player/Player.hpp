#ifndef _PLAYER_
#define _PLAYER_

#include "DeckBuilder.hpp"
#include "Statistics.hpp"


class Player {
private:
string name;
list<GreenCard*>* fateDeck;
list<BlackCard*>* dynastyDeck;
list<GreenCard*>* hand;
list<BlackCard*>* holdings;
list<BlackCard*>* army;
list<BlackCard*>* provinces;
Stronghold* sh;

int numberOfProvinces;
int money;
int honour;

Statistics *stats;

public:

Player(string);
~Player();

/* startingPhase functions */
void untapEverything();
void drawFateCard();
void revealProvinces();
void printHand() const;
int printProvinces() const;
/* ------------------------- */

list<BlackCard*>* getProvinces() const;
Stronghold* getSh() const;
list<BlackCard*>* getArmy() const;
string getName() const;
int getHonour() const;
int getMoney() const;
int getNumberOfProvinces() const;
list<BlackCard*>* getDynastyDeck() const;
list<GreenCard*>* getFateDeck() const;
list<GreenCard*>* getHand() const;
list<BlackCard*>* getHoldings() const;
Statistics *getStats() const;

void setMoney(int);
void setHonour(int);
void setDynastyDeck(list<BlackCard*>*);
void setFateDeck(list<GreenCard*>*);

void printArmy() const;
int printHoldings() const;
void printAllHoldings() const;
int printUntappedArmy() const;
void AvailableProvinces() const;
int maxHarvestMoney() const;    //returns the maximun money that the player can get from tapping his holdings

int untappedArmy()const;   //returns the number of untapped personalities in the army

};

#endif
