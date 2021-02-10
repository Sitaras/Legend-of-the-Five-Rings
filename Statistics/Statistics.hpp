// #ifndef _STATS_
// #define _STATS_

class Statistics{
  int initialArmy;
  int finalArmy;

  int attackBonus;
  int defBonus;

  int armyLost;

  int moneySpent;
  int moneyLost;


public:
  void initialiseStats();

  void setInitialArmy(int );
  void setAttackBonus(int );
  void setDefBonus(int );
  void setFinalArmy(int );
  void setArmyLost(int );
  void setMoneySpent(int );
  void setMoneyLost(int );

  int getInitialArmy()const;
  int getFinalArmy()const;
  int getAttackBonus()const;
  int getDefenceBonus()const;
  int getArmyLost()const;
  int getMoneyLost()const;
  int getMoneySpent()const;

  double armyPercentage()const;
  double armyLostPercentage()const;

};
