#include "Statistics.hpp"

void Statistics::initialiseStats(){
  initialArmy=0;        // number of personality cards (army) at the start of a round
  attackBonus=0;      //attack bonus gained from followers/items in this round
  defBonus=0;           //defence bonus gained from followers/items in this round
  finalArmy=0;        // number of personality cards (army) at the end of a round
  armyLost=0;         //number of personalities lost in battle
  moneySpent=0;     //money that the player spent to buy provinces or to equip army cards.
  moneyLost=0;      //money that the player lost during tapping proccess from the beggining of the game("lost money")
}


void Statistics::setInitialArmy(int x){
  initialArmy=x;
}
void Statistics::setMoneySpent(int x){
  moneySpent=x;
}
void Statistics::setAttackBonus(int x){
  attackBonus=x;
}
void Statistics::setDefBonus(int x){
  defBonus=x;
}
void Statistics::setFinalArmy(int x){
  finalArmy=x;
}
void Statistics::setArmyLost(int x){
  armyLost=x;
}
void Statistics::setMoneyLost(int x){
  moneyLost=x;
}

int Statistics::getInitialArmy()const{
  return initialArmy;
}
int Statistics::getMoneyLost()const{
  return moneyLost;
}
int Statistics::getFinalArmy()const{
  return finalArmy;
}
int Statistics::getMoneySpent()const{
  return moneySpent;
}

int Statistics::getAttackBonus()const{
    return attackBonus;
}
int Statistics::getDefenceBonus()const{
  return defBonus;
}

int Statistics::getArmyLost()const{
  return armyLost;
}


double Statistics::armyPercentage()const{     //army increase/decrease persentage at this round
  if(initialArmy>finalArmy)
    return ( (double)initialArmy - (double)finalArmy ) / (double)initialArmy * 100.0;
  if(initialArmy<finalArmy)
    return ( (double)finalArmy - (double)initialArmy ) / (double)initialArmy * 100.0;
  return 0.0;
}

double Statistics::armyLostPercentage()const{     //persentage of the army lost in battle
  if(initialArmy!=0)
    return ( (double)initialArmy - (double)armyLost ) / (double)initialArmy * 100.0;
  else
    return 0;
}
