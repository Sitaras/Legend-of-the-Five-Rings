#ifndef _CARDS_
#define _CARDS_

#include <iostream>
#include <list>
#include <string>

using namespace std;

extern const unsigned int MAXEQUIP;
extern const unsigned int MAXHAND;

enum  {PERSONALITY = 1, HOLDING, FOLLOWER, ITEM};

enum  {KATANA, SPEAR, BOW, NINJATO, WAKIZASHI};
enum  {ATTACKER, DEFENDER, SHOGUN, CHANCELLOR, CHAMPION};
enum  {PLAIN,MINE,GOLD_MINE,CRYSTAL_MINE,FARMS,SOLO,STRONGHOLD};
enum  {FOOTSOLDIER, ARCHER, SIEGER, CAVALRY, NAVAL, BUSHIDO};


class Personality;
class Item;
class Stronghold;
class GreenCard;
class BlackCard;


///////////////////  CARD  ///////////////////////////

class Card {
protected:
        string name;
        int cost;
        bool isTapped;
        int type;
        int kind;
public:
        Card();
        Card(string,int=0,int =-1,int =-1);
        virtual ~Card();

        string getName() const;
        int getCost() const;
        bool getIsTapped() const;
        virtual int getType() const=0;
        virtual int getKind() const=0;

        virtual void print() const=0;

        virtual void setIsTapped(bool);

};

//======================================================
///////////////////  GREENCARD  ///////////////////////////////


class GreenCard: public Card {
protected:
        int attackBonus;
        int defenceBonus;
        int minimumHonour;
        int effectCost;
        int effectBonus;
        bool UsingEffectBonus;
        string cardText;
public:
        GreenCard();
        GreenCard(string ,int ,int ,int  ,int ,int ,string ,int ,int ,int );

        int getMinimumHonour() const;
        int getAttackBonus() const;
        int getDefenceBonus() const;
        int getEffectBonus() const;
        int getEffectCost() const;
        bool getUsingEffectBonus() const;
        string getCardText() const;

        void setUsingEffectBonus(bool);

       ~GreenCard();
};
///////////////// BLACKCARD  /////////////////////////////////


class BlackCard: public Card {
protected:
        bool isReleaved;
public:
        BlackCard();
        BlackCard(string,int ,int, int );
        virtual ~BlackCard();

        void setIsReleaved(bool);
        bool getIsReleaved() const;


};

////////////////  FOLLOWER  //////////////////////////////////

class Follower: public GreenCard {
public:
        Follower(string ,int ,int ,int ,int ,int ,int ,int,string);
        ~Follower();

        int getType() const;
};

class Footsoldier : public Follower {

public:
Footsoldier(string);
~Footsoldier();

int getKind() const;
void print() const;
};

class Archer : public Follower {

public:
Archer(string);
~Archer();

int getKind() const;
void print() const;
};

class Sieger : public Follower {

public:
  Sieger(string);
  ~Sieger();

  int getKind() const;
  void print() const;
};
class Cavalry : public Follower {

public:
Cavalry(string);
~Cavalry();

int getKind() const;
void print() const;
};

class Atakebune : public Follower {    // Naval

public:

  Atakebune(string);
  ~Atakebune();

  int getKind() const;
  void print() const;

};

class Bushido : public Follower {

public:
  Bushido(string);
  ~Bushido();

  int getKind() const;
  void print() const;
};


///////////////////  ITEM  ////////////////////////////////



class Item: public GreenCard {
protected:
        int durability;
public:
        Item(string ,int ,int,int ,int  ,int ,int ,int ,int,string);
        ~Item();


        int getDurability() const;
        int getType() const;

        void setDurability(int );

};

class Katana : public Item {

public:
Katana(string);
~Katana();

int getKind() const;
void print() const;
};



class Spear : public Item {

public:
Spear(string);
~Spear();

int getKind() const;
void print() const;
};



class Bow : public Item {

public:
Bow(string);
~Bow();

int getKind() const;
void print() const;
};



class Ninjato : public Item {

public:
Ninjato(string);
~Ninjato();

int getKind() const;
void print() const;
};


class Wakizashi : public Item {

public:
Wakizashi(string);
~Wakizashi();

int getKind() const;
void print() const;
};


//////////////////  PERSONALITY  ////////////////////////////////


class Personality: public BlackCard {
protected:
        int attack;
        int defence;
        int honour;
        bool isDead;
        list<GreenCard*>* equipList;     // Followers or Items
        bool isDefending;
public:
        Personality(string,int,int,int,int,int);
        ~Personality();

        void setAttack(int );
        void setDefence(int );
        void setHonour(int );
        void setIsDead(bool );
        void setIsTapped(bool);
        void setIsDefending(bool);


        int getAttack() const;
        int getDefence() const;
        int getHonour() const;
        bool getIsDead() const;
        int getType() const;
        list<GreenCard*>* getEquipList() const;
        bool getIsDefending()const;

};

class Attacker : public Personality {
private:

public:
Attacker(string);
~Attacker();

int getKind() const;
void print() const;

};

class Defender : public Personality {
public:
Defender(string);
~Defender();

void print() const;
int getKind() const;
};


class Shogun : public Personality {
public:
Shogun(string);
~Shogun();

void print() const;
int getKind() const;
};

class Chancellor : public Personality {
public:
Chancellor(string);
~Chancellor();

void print() const;
int getKind() const;
};

class Champion : public Personality {
public:
Champion(string);
~Champion();

void print() const;
int getKind() const;
};

//////////////////  HOLDING  ////////////////////////////////


class Holding: public BlackCard {
protected:
        Holding *upperHolding;
        Holding *subHolding;
        int harvestValue;
public:
        Holding(string ,int,int,int);
        ~Holding();

        int getHarvestValue() const;
        int getType() const;
        Holding* getsubHolding() const;
        Holding* getupperHolding() const;

        void setHarvestValue(int);
        void setupperHolding(Holding*);
        void setsubHolding(Holding*);


};


class Plain : public Holding {
public:
Plain(string);
~Plain();

int getKind() const;
void print() const;
};



class Mine : public Holding {
public:
Mine(string);
~Mine();

int getKind() const;
void print() const;
};

class GoldMine : public Holding {
public:
GoldMine(string);
~GoldMine();

int getKind() const;
void print() const;
};

class CrystalMine : public Holding {
public:
CrystalMine(string);
~CrystalMine();

int getKind() const;
void print() const;
};

class Farmland : public Holding {
public:
Farmland(string);
~Farmland();

int getKind() const;
void print() const;
};

class GiftsandFavour : public Holding {  // SOLO
public:
GiftsandFavour(string);
~GiftsandFavour();

int getKind() const;
void print() const;

};

class Stronghold : public Holding {
private:
int startingHonour;
int initialDefence;

public:
Stronghold();

int get_startingHonour() const;
int get_initialDefence() const;
int getKind() const;

void print() const;

};

#endif
