#include "Gameboard.hpp"
#include "TypeConverter.hpp"

extern const unsigned int MAXEQUIP;
extern const unsigned int MAXHAND;
const unsigned int MAXPLAYERS=8;


GameBoard::GameBoard(int num):db(new DeckBuilder){

  playersList=new list<Player *>();
  string name;
  for(int i=0;i<num;i++){
    cout << ">Insert player's name: ";
    cin >> name;
    cin.ignore();
    /* Players sort by honour in descending order (in list) */
    if(i==0){
      playersList->push_front(new Player(name));
    }else{
      Player *newPlayer=new Player(name);
        bool flag=true;
      for (auto pl=playersList->begin(); pl!=playersList->end(); pl++){
          if((*pl)->getHonour()<newPlayer->getHonour()){
            playersList->insert(pl,newPlayer);
            flag=false;
            break;
          }
      }
      if(flag)
        playersList->push_back(newPlayer);

    }
  }

}

GameBoard::~GameBoard(){
  list<Player *>::iterator it=playersList->begin();

  while(!playersList->empty()){
      delete *it;
  		it=playersList->erase(it);
  	}

    delete playersList;
    delete db; /* delete Fate and Dynasty Decks */

}

void GameBoard::connectHoldings(list<BlackCard*>* holdings){
  auto toconnect=holdings->begin(); /* iterator */
  TypeConverter tc;

  switch (tc.getHolding(*toconnect)->getKind()) {
    case MINE:
    for (auto h=next(toconnect); h!=holdings->end(); h++){
      /* search list of Holdings for GOLD_MINE */
      if(tc.getHolding(*h)->getKind()==GOLD_MINE){
        if(tc.getHolding(*h)->getsubHolding()==NULL && tc.getHolding(*toconnect)->getupperHolding()==NULL){ /* check if GoldMine and Mine has free/NULL the subHolding and upperHolding respectively */
          /*ok, then connect */
          cout << "Mine connected with GoldMine" << '\n';
          sleep(1);

           tc.getHolding(*h)->setsubHolding(tc.getHolding(*toconnect));
           tc.getHolding(*toconnect)->setupperHolding(tc.getHolding(*h));
           break;
        }
      }
    }
    /* bonus points for MINE, GOLD_MINE and CRYSTAL_MINE */
    if(tc.getHolding(*toconnect)->getupperHolding()!=NULL){ /* Mine has GoldMine as upperHolding */

      tc.getHolding(*toconnect)->setHarvestValue(tc.getHolding(*toconnect)->getHarvestValue() + 2); // Mine bonus

      if(tc.getHolding(*toconnect)->getupperHolding()->getupperHolding()!=NULL){ // Mine complete the chain: MINE<->GOLD_MINE<->CRYSTAL_MINE
        cout << "Mine has complete the chain: MINE<->GOLD_MINE<->CRYSTAL_MINE" << '\n';
        sleep(1);
        tc.getHolding(*toconnect)->getupperHolding()->setHarvestValue(tc.getHolding(*toconnect)->getupperHolding()->getHarvestValue() * 2); // GoldMine bonus
        tc.getHolding(*toconnect)->getupperHolding()->getupperHolding()->setHarvestValue(tc.getHolding(*toconnect)->getupperHolding()->getupperHolding()->getHarvestValue() * 3); // CrystalMine bonus
      }
      else{ /* GoldMine hasn't upperHolding */
        tc.getHolding(*toconnect)->getupperHolding()->setHarvestValue(tc.getHolding(*toconnect)->getupperHolding()->getHarvestValue() + 4); // GoldMine bonus
      }
    }
      break;

    case GOLD_MINE:
    for (auto h=next(toconnect); h!=holdings->end(); h++){
          /* search list of Holdings for MINE */
      if(tc.getHolding(*h)->getKind()==MINE){
        if(tc.getHolding(*h)->getupperHolding()==NULL && tc.getHolding(*toconnect)->getsubHolding()==NULL){ /* check if Mine and GoldMine has free/NULL the upperHolding and subHolding respectively */
          /* ok, then connect */
          cout << "GoldMine connected with Mine" << '\n';
          sleep(1);

           tc.getHolding(*h)->setupperHolding(tc.getHolding(*toconnect));
           tc.getHolding(*toconnect)->setsubHolding(tc.getHolding(*h));
        }
      }
      /* search list of Holdings for CRYSTAL_MINE */
      if(tc.getHolding(*h)->getKind()==CRYSTAL_MINE){
          if(tc.getHolding(*h)->getsubHolding()==NULL && tc.getHolding(*toconnect)->getupperHolding()==NULL){ /* check if CrystalMine and GoldMine has free/NULL the subHolding and upperHolding respectively */
            /* ok, then connect */
            cout << "GoldMine connected with CrystalMine" << '\n';
            sleep(1);

             tc.getHolding(*h)->setsubHolding(tc.getHolding(*toconnect));
             tc.getHolding(*toconnect)->setupperHolding(tc.getHolding(*h));
          }
      }
    }
    /* bonus points */
    if(tc.getHolding(*toconnect)->getsubHolding()!=NULL){ /* GoldMine has Mine as subHolding */
      tc.getHolding(*toconnect)->getsubHolding()->setHarvestValue(tc.getHolding(*toconnect)->getsubHolding()->getHarvestValue() + 2); // Mine bonus
      if(tc.getHolding(*toconnect)->getupperHolding()!=NULL){ // GoldMine (has CrystalMine as upperHolding) complete the chain: MINE<->GOLD_MINE<->CRYSTAL_MINE
        cout << "GoldMine has complete the chain: MINE<->GOLD_MINE<->CRYSTAL_MINE" << '\n';
        sleep(1);
        tc.getHolding(*toconnect)->setHarvestValue(tc.getHolding(*toconnect)->getHarvestValue() * 2); // GoldMine bonus
        tc.getHolding(*toconnect)->getupperHolding()->setHarvestValue(tc.getHolding(*toconnect)->getupperHolding()->getHarvestValue() * 3); // CrystalMine bonus
      }
      else{ /* GoldMine hasn't upperHolding */
        tc.getHolding(*toconnect)->setHarvestValue(tc.getHolding(*toconnect)->getHarvestValue() + 4); // GoldMine bonus
      }
    }
    else if(tc.getHolding(*toconnect)->getupperHolding()!=NULL){ /* GoldMine has CrystalMine as upperHolding */
      tc.getHolding(*toconnect)->setHarvestValue(tc.getHolding(*toconnect)->getHarvestValue() + 5); // GoldMine bonus
      tc.getHolding(*toconnect)->getupperHolding()->setHarvestValue(tc.getHolding(*toconnect)->getupperHolding()->getHarvestValue() * 2); // CrystalMine bonus
   }
      break;
    case CRYSTAL_MINE:
      for (auto h=next(toconnect); h!=holdings->end(); h++){
        /* search list of Holdings for GOLD_MINE */
        if(tc.getHolding(*h)->getKind()==GOLD_MINE){
            if(tc.getHolding(*h)->getupperHolding()==NULL && tc.getHolding(*toconnect)->getsubHolding()==NULL){/* check if GoldMine and CrystalMine has free/NULL the upperHolding and subHolding respectively */
              /* ok, then connect */
              cout << "CrystalMine connected with GoldMine" << '\n';
              sleep(1);

               tc.getHolding(*h)->setupperHolding(tc.getHolding(*toconnect));
               tc.getHolding(*toconnect)->setsubHolding(tc.getHolding(*h));
               break;
            }
        }

      }
      /* bonus points */
      if(tc.getHolding(*toconnect)->getsubHolding()!=NULL){ /* CrystalMine has GoldMine as subHolding */
        if(tc.getHolding(*toconnect)->getsubHolding()->getsubHolding()!=NULL){ // CrystalMine has complete the chain: MINE<->GOLD_MINE<->CRYSTAL_MINE
          cout << "CrystalMine has complete the chain: MINE<->GOLD_MINE<->CRYSTAL_MINE" << '\n';
          sleep(1);
          tc.getHolding(*toconnect)->getsubHolding()->setHarvestValue(tc.getHolding(*toconnect)->getsubHolding()->getHarvestValue() * 2); // GoldMine bonus
          tc.getHolding(*toconnect)->setHarvestValue(tc.getHolding(*toconnect)->getHarvestValue() * 3); // CrystalMine bonus
        }
        else { /* there isn't chain, just: GoldMine<->CrystalMine */
          tc.getHolding(*toconnect)->getsubHolding()->setHarvestValue(tc.getHolding(*toconnect)->getsubHolding()->getHarvestValue() + 5); // GoldMine
          tc.getHolding(*toconnect)->setHarvestValue(tc.getHolding(*toconnect)->getHarvestValue() * 2); // CrystalMine
        }
      }
      break;
  }

}

void GameBoard::initializeGameBoard(){

  cout<<">Players: "<<endl;
  for(auto p=playersList->begin(); p!=playersList->end(); p++){
    cout<<"|"<<(*p)->getName()<<"|"<<endl;

    /* creation of Decks for each player */
    (*p)->setDynastyDeck(db->createDynastyDeck());
    db->deckShuffler((*p)->getDynastyDeck());

    (*p)->setFateDeck(db->createFateDeck());
    db->deckShuffler((*p)->getFateDeck());

    (*p)->getStats()->initialiseStats();
  }

  for (auto p=playersList->begin(); p!=playersList->end(); p++) {
          for (int i=0; i < 4; i++) { /* each player has 4 Green Cards on his hand */
                  auto ft = (*p)->getFateDeck()->begin();
                  /* with splice: transfer a GreenCard from fateDeck list list Hand's list */
                  (*p)->getHand()->splice((*p)->getHand()->begin(), *(*p)->getFateDeck(), ft);
          }
  }

  for (auto p=playersList->begin(); p!=playersList->end(); p++) {
          for (int i=0; i < 4; i++) { /* each player has 4 provinces */
                  auto dns = (*p)->getDynastyDeck()->begin();
                  /* with splice: transfer a BlackCard from dynastyDeck list to Provinces list */
                  (*p)->getProvinces()->splice((*p)->getProvinces()->begin(), *(*p)->getDynastyDeck(), dns);
          }
  }

}


void GameBoard::startingPhase(){
  for (auto pp=playersList->begin(); pp!=playersList->end(); pp++){
    Player& pl=*(*pp);
    cout<<endl<<endl<< "---------------------------------" << '\n';
    cout<<">Starting Phase"<<endl;
    cout << "---------------------------------" << '\n';
    cout<<endl<<">Player: "<<pl.getName()<< endl<<endl;
    sleep(2);

    pl.untapEverything();
    pl.drawFateCard();
    pl.revealProvinces();
    pl.printHand();
    pl.printProvinces();

    cout<<endl<<endl << ">Press ENTER to continue." << '\n';
    getchar();

    pl.getStats()->setInitialArmy(pl.getArmy()->size());
    pl.getStats()->setAttackBonus(0);
    pl.getStats()->setDefBonus(0);
  }
}

void GameBoard::equipPhase(){
  for (auto pp=playersList->begin(); pp!=playersList->end(); pp++){
      Player& pl=*(*pp);
      cout <<endl<<endl<< "---------------------------------" << '\n';
      cout<<">Equip Phase"<<endl;
      cout << "---------------------------------" << '\n';
      cout<<">Player: "<<pl.getName()<<" plays."<< endl;
      sleep(2);

      TypeConverter tc;
      int armycard;
      int handcard;
      int holdingcard;

      if(pl.getArmy()->empty()){
        cout<<">No army to equip!!!"<<endl;
        sleep(2);
        continue;
      }

      for(;;){
        cout<<endl;
        if(pl.getHand()->empty()){
          cout<<endl<< "-> You have no other cards in your hand. All were used. <-" <<endl;
          break;
        }
        pl.printArmy();
        cout<<">Select the army card that you want to equip OR 0 to quit: "<<endl<<">> ";
        while(!(cin >> armycard) || (armycard < 0 || (unsigned) armycard > pl.getArmy()->size() )){
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input. Please, try again: ";
        }
        cin.ignore();

        if(armycard==0) /* exit from equipPhase */
          break;

        auto ar=pl.getArmy()->begin(); /* iterator */
        for(int i=0; i<armycard;i++)
          ar++;
        ar--;

        if(tc.getPersonality(*ar)->getEquipList()->size()>=MAXEQUIP){
          cout << ">>This Personality can not equip with additional green cards, has reached the limit! Please choose another one." << '\n';
          sleep(2);
          continue;
        }

        pl.printHand();
        cout<<">>>> WARNING! Personality's Honour is "<<tc.getPersonality(*ar)->getHonour()<<endl;
        cout<<">Select a green card from your hand: "<<endl;
        cout<<">Current Money: "<<pl.getMoney()<<endl<<">> ";
        while(!(cin >> handcard) || (handcard <= 0 || (unsigned) handcard > pl.getHand()->size() )){
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input. Please, try again: ";
        }
        cin.ignore();


        auto hd=pl.getHand()->begin(); /* iterator */
        for(int i=0; i<handcard;i++)
          hd++;
        hd--;

        if( (*hd)->getCost() > pl.maxHarvestMoney() ){
          cout<<"Cannot collect so much money by tapping your holdings. Please select another card."<<endl;
          sleep(2);
          continue;
        }

        /* holdings tapping process */
        for(;;){

          if(!pl.printHoldings()){
            cout << "-> All holdings are Tapped! <-" << endl;
            sleep(2);
            break;
          }

          cout<<">>Current money: "<<pl.getMoney()<<endl;
          cout<<">Select the holding card that you want to tap OR 0 to quit: "<<endl<<">> ";
          while(!(cin >> holdingcard) || (holdingcard < 0 || (unsigned) holdingcard > pl.getHoldings()->size() )){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please, try again: ";
          }
          cin.ignore();

          if(holdingcard==0){
            break;
          }

            auto hol=pl.getHoldings()->begin();
            for(int i=0; i<holdingcard;i++)
              hol++;
            hol--;

            (*hol)->setIsTapped(true); /* tapping */

            pl.setMoney(pl.getMoney() + tc.getHolding(*hol)->getHarvestValue());

            if(pl.getMoney() >= (*hd)->getCost()){
              cout<<endl << ">Enough money to buy the card (end of tapping holdings process)." <<endl;
              cout << "Card's cost: "<<(*hd)->getCost()<<" | Current money: "<<pl.getMoney()<<endl;
              sleep(1);
              break;
            }
          }

        /* check Player's money and Personality's honour if they are enough for the purchase */
        if(tc.getPersonality(*ar)->getHonour()>=(*hd)->getMinimumHonour()  && pl.getMoney()>=(*hd)->getCost()){
          char ans;
          cout<<">GreenCard: "<<(*hd)->getName()<<" Bought!"<<endl;
          sleep(1);
          /* with splice: transfer GreenCard from hand to Personality's equipList */
          tc.getPersonality(*ar)->getEquipList()->splice(tc.getPersonality(*ar)->getEquipList()->begin(),*(pl.getHand()),hd);

          pl.setMoney(pl.getMoney()-(*hd)->getCost());
          pl.getStats()->setMoneySpent(pl.getStats()->getMoneySpent()+(*hd)->getCost());    //statistics

          tc.getPersonality(*ar)->setAttack( tc.getPersonality(*ar)->getAttack() + (*hd)->getAttackBonus() );
          tc.getPersonality(*ar)->setDefence( tc.getPersonality(*ar)->getDefence() + (*hd)->getDefenceBonus() );

          pl.getStats()->setAttackBonus(pl.getStats()->getAttackBonus() + (*hd)->getAttackBonus() );
          pl.getStats()->setDefBonus(pl.getStats()->getDefenceBonus() + (*hd)->getDefenceBonus() );

          cout<<">Do you want to use effectBonus (Cost:"<<(*hd)->getEffectCost()<<")"<<endl<<"Yes(y) or No(n)?"<<endl;
          cout<<">Money: "<<pl.getMoney()<<endl<<">> ";
          while(!(cin >> ans) || (ans!='y' && ans!='n' )){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please, try again: ";
          }
          cin.ignore();

          if(ans=='y' && pl.getMoney()>=(*hd)->getEffectCost()){
            (*hd)->setUsingEffectBonus(true);
            cout << ">>Effect Bonus activated!" << '\n';
            sleep(1);

            tc.getPersonality(*ar)->setAttack( tc.getPersonality(*ar)->getAttack() + (*hd)->getEffectBonus() );
            tc.getPersonality(*ar)->setDefence( tc.getPersonality(*ar)->getDefence() + (*hd)->getEffectBonus() );
            pl.setMoney(pl.getMoney()-(*hd)->getEffectCost());
            pl.getStats()->setMoneySpent(pl.getStats()->getMoneySpent()+(*hd)->getEffectCost());    //statistics
            pl.getStats()->setAttackBonus(pl.getStats()->getAttackBonus() + (*hd)->getEffectBonus() );
            pl.getStats()->setDefBonus(pl.getStats()->getDefenceBonus() + (*hd)->getEffectBonus() );
          }
          else if(ans=='y' && pl.getMoney()<(*hd)->getEffectCost()){
              cout << ">>No enough money for effectBonus." << '\n';
              sleep(1);
          }
        }else {
            if (tc.getPersonality(*ar)->getHonour()<(*hd)->getMinimumHonour())
              cout<<endl << ">Not enough Personality's honor , please try another card..." <<endl<<endl;
            if (pl.getMoney()<(*hd)->getCost())
              cout << ">Not enough money , please try another card..." <<endl<<endl;
            sleep(1);
          }
          cout<<endl <<">Lost Money : "<<pl.getMoney()<<endl<<endl;
          pl.getStats()->setMoneyLost(pl.getStats()->getMoneyLost()+pl.getMoney());    //statistics
          sleep(1);
          pl.setMoney(0);
        }
      }
    }



void GameBoard::battlePhase(){
  for (auto pp=playersList->begin(); pp!=playersList->end(); pp++){ //loop for every player
    Player& pl=*(*pp);      // pl is the player tha is his turn
      cout <<endl<<endl<< "---------------------------------" << '\n';
      cout<<">Battle Phase"<<endl;
      cout << "---------------------------------" << '\n';
      cout<<endl<<">Player: "<<pl.getName()<<" plays."<< endl<<endl;
      sleep(2);
      cout<<pl.getName()<<"'s turn:"<<endl;
      if(pl.getArmy()->empty()){      // if the player has no army
        cout<<">No army, attack not possible!!!"<<endl;
        sleep(1);
        continue;
      }
      if(pl.untappedArmy()==0){      // if all the personalities in army are tapped (only untapped personalities can be used to attack)
        cout<<">All army cards are tapped, attack not possible!!!"<<endl;
        sleep(1);
        continue;
      }
      else{
          cout<<">Do you want to attack?"<<endl<<"Yes(y) or No(n)?"<<endl;
          char ans;
          while(!(cin >> ans) || (ans!='y' && ans!='n' )){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please, try again: ";
          }
          cin.ignore();
          if(ans!='y'){ // no attack
            continue;
            cout <<endl<<endl;
          }
          cout<<">Select army to attack"<<endl;
            TypeConverter tc;
            int armycard=-1;
            int maxAttackingCards=pl.getArmy()->size()+1;   //the max number of atttackers that the player can select
            int cardsToAttack[maxAttackingCards];     // an array that stores the attacker selections of the player
            int numOfCardsToAttack=0;       //the current number of atatcking cards that the player  has selected
            int maxToSelect=pl.printUntappedArmy();     //prints the army that the player can use to attack and returns the number of untapped army
            int count=0;
            while(armycard!=0){
              cout<<">Select an army card that you want to attack"<<endl;
              cout<<"Press 0 if you are OK"<<endl<<">> ";

              while(!(cin >> armycard) || (armycard < 0 || (unsigned) armycard > pl.getArmy()->size() )){   //check if the input is valid
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please, try again: ";
              }
              cin.ignore();
              if(armycard==0)     //if input is 0 the selection is over
                break;
              /* ----------------tapping------------------ */
              auto ar=pl.getArmy()->begin(); /* iterator */
              for(int i=0; i<armycard;i++)
                ar++;
              ar--;
              (*ar)->setIsTapped(true);     //tap all the cards that are selected to attack
              /* ------------------------------------------ */
              cardsToAttack[numOfCardsToAttack++]=armycard;     //store the selections of the player
              count++;
              if(count==maxToSelect){
                cout<<endl<<"** You selected all the available cards **"<<endl<<endl<<endl;
                break;
              }

              pl.printUntappedArmy();

            }

            for(int i=numOfCardsToAttack;i<maxAttackingCards;i++)
              cardsToAttack[i]=0;     //fill all the unused array spaces with 0

            cout<<">Select to who you want to attack (number)"<<endl;
            int counter=1;
            int currentPlayer;
            for (auto p=playersList->begin(); p!=playersList->end(); p++){    //print all the players except pl
                if((*p)->getName()!= pl.getName()){
                  cout<<counter++<<": "<<(*p)->getName()<<"  ";
                }else{
                  currentPlayer=counter;    //keep the index of pl for later use
                }
            }
            cout<<endl;
            int attackTo;     //index of the player that pl wants to attack
            while(!(cin >> attackTo) || (attackTo < 1 || (unsigned) attackTo > playersList->size())){   //check if input is valid
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << "Invalid input. Please, try again: ";
            }
            cin.ignore();
            if(attackTo>=currentPlayer){    //if the player that pl wants to attack is after pl int the list, in reality the index of attackTo is the next one because pl was not printed int the selection print
              attackTo++;
            }
            auto pl2=playersList->begin(); /* iterator */       //pl2=the player that will be attacked
            for(int i=0; i<attackTo;i++)
              pl2++;
            pl2--;


            (*pl2)->AvailableProvinces();   //print all the available provinces of pl2
            cout<<">Select the province you want to attack to"<<endl<<">> ";
            int attProv;      //index of the province of pl2 that pl will attack to
            while(!(cin >> attProv) || (attProv < 1 || attProv > pl.getNumberOfProvinces())){   //check if input is valid
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << "Invalid input. Please, try again: ";
            }
            cin.ignore();

            auto attackedProv=(*pl2)->getProvinces()->begin(); /* iterator */      //the province of pl2 that will be attacked
            for(int i=0; i<attProv;i++)
              attackedProv++;
            attackedProv--;

            int attackPower=0;
            counter=1;
            for (auto p=pl.getArmy()->begin(); p!=pl.getArmy()->end(); p++){    //find the atatcking power of pl
                  for(int i=0;i<maxAttackingCards;i++){
                      if(counter==cardsToAttack[i])
                        attackPower+=tc.getPersonality(*p)->getAttack();    //sum the attack power of all the selected cards that will be used to attack
                  }
                  counter++;
            }
            cout <<endl<< "Attack Power: "<<attackPower<< '\n';

            int defPower=0;
            for (auto p=(*pl2)->getArmy()->begin(); p!=(*pl2)->getArmy()->end(); p++){    //find the defence power of pl2
                  if(!(*p)->getIsTapped())    //only untapped army is used to defence
                    defPower+=tc.getPersonality(*p)->getDefence();  //sum the defence power of all the cards that are used to defend
            }
            defPower+=(*pl2)->getSh()->get_initialDefence();      //add also the defence of the province (from Stronghold)
            if(defPower<=attackPower) //else it is printed inside tha case (because fewer personalities can be chosen to defend)
              cout << "Defence Power: "<<defPower<< '\n'<<endl;


            if(attackPower-defPower > (*pl2)->getSh()->get_initialDefence()){   //first case
              cout<<pl.getName()<<" won the fight!"<<endl;                    //attacker wins
              if((*pl2)->getArmy()->empty())
                cout<<(*pl2)->getName()<<"'s province is destroyed!"<<endl;
              else
                cout<<(*pl2)->getName()<<"'s defending army and province are destroyed!"<<endl;

              delete (*attackedProv);           //the difference between attackPower and defPower is big enough to destroy the province of pl2
              (*pl2)->getProvinces()->erase(attackedProv);      //so the province is destroyed
              for (auto p=(*pl2)->getArmy()->begin(); p!=(*pl2)->getArmy()->end();){      //destroy the defending army
                    auto ptemp=p;     //keep the current position in the list
                    ptemp++;      //go to the next item of the list
                    if(!(*p)->getIsTapped()){     //if the card is untapped, it was used to defend
                      (*pl2)->getStats()->setArmyLost((*pl2)->getStats()->getArmyLost() + 1);         // *keep statistics for the army loss*
                      delete *p; /* equiped cards also deleted */
                      (*pl2)->getArmy()->erase(p);      //delete the card
                    }
                    p=ptemp;    //this is done because erase() returns iterator to the next node, so p is changed when we erase personality (even if we dont assign to p the return value of erase())
                                //so this is a sure way to always go to the next item of the list (if we delete a personality or not)
              }
            }else if( attackPower > defPower){      //case 2 , the attackPower is not enough to destroy the province
              cout<<pl.getName()<<" won the fight!"<<endl;      //attacker wins
              cout<<" The attack power is not enough to destroy the province"<<endl;
              if((*pl2)->getArmy()->empty())
                cout<<(*pl2)->getName()<<" has no defending army to be destroyed"<<endl;
              else
                cout<<(*pl2)->getName()<<"'s defending army is destroyed!"<<endl;
              sleep(1);
              for (auto p=(*pl2)->getArmy()->begin(); p!=(*pl2)->getArmy()->end();){      //destroy all the defending army of pl2
                auto ptemp=p;
                ptemp++;
                    if(!(*p)->getIsTapped()){
                      (*pl2)->getStats()->setArmyLost((*pl2)->getStats()->getArmyLost() + 1);
                      delete *p;
                      (*pl2)->getArmy()->erase(p);
                    }
                    p=ptemp;
              }
              int sub=attackPower-defPower;   //the difference between attackPower and defPower, is the sum of attack damage that the pl need to lose by discarting some of his cards
              while(sub>0){
                cout<<endl<<"You need to lose "<<sub<<" attack points"<<endl;
                counter=1;
                int counter2=1;
                for (auto p=pl.getArmy()->begin(); p!=pl.getArmy()->end(); p++){    //print all the cards that was used to atttack
                  if(!tc.getPersonality(*p)->getIsDead()){
                      for(int i=0;i<maxAttackingCards;i++){
                          if(counter==cardsToAttack[i]){      //the cards was used to atttack
                            cout << "Card no."<< counter2 << endl;
                            cout << "________________________" << '\n';
                            (*p)->print();
                            cout << "________________________" << '\n';
                            counter2++;
                          }

                      }
                  }
                  counter++;
                }
                cout<<"Select the personality that you want to discart (or it's followers)"<<endl<<">> ";
                int pers; //index to the selected personality
                while(!(cin >> pers) || (pers < 1 || (unsigned) pers > pl.getArmy()->size())){
                  cin.clear();
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                  cout << "Invalid input. Please, try again: ";
                }
                cin.ignore();
                cout<<" Press:\n  1: If you want to discart the entire personality\n  2: If you want to discart a follower"<<endl<<">> ";
                int choice;   //choise of the above selection {1,2}
                while(!(cin >> choice) || (choice < 1 ) || (choice > 2 )){
                  cin.clear();
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                  cout << "Invalid input. Please, try again: ";
                }
                cin.ignore();
                counter=1;
                counter2=1;
                auto pp=pl.getArmy()->begin();    //iterator that the selected personality will be stored
                for (auto p=pl.getArmy()->begin(); p!=pl.getArmy()->end();p++ ){    //find the selected personality   //same loop as the printing one
                  if(!tc.getPersonality(*p)->getIsDead()){
                      for(int i=0;i<maxAttackingCards;i++){
                          if(counter==cardsToAttack[i]){
                              if(counter2==pers)
                                pp=p;   //the selected personality
                              counter2++;
                          }

                      }
                  }
                  counter++;
                }
                if(choice==1){    //if choise==1 the entire personality is discarted
                  cout<<pl.getName()<<" lost "<<tc.getPersonality(*pp)->getName()<<" (personality)..."<<endl;
                  sub-=tc.getPersonality(*pp)->getAttack(); //decrease the attackPower that pl needs to lose
                  tc.getPersonality(*pp)->setIsDead(true);
                }else{    //else he need to sellect a follower of this personality to discard
                      cout<<"_________FOLLOWERS_________"<<endl;
                      int cc=0;
                      for (auto p2=tc.getPersonality(*pp)->getEquipList()->begin(); p2!=tc.getPersonality(*pp)->getEquipList()->end(); p2++){   //print all the follower of this personality
                          if (tc.getFollower(*p2)==NULL)
                            continue;
                          cc++;
                          cout << "Card no."<< cc << endl;
                          cout << "________________________" << '\n';
                          (*p2)->print();
                          cout<<"- - - - - - - - - - - - - - - - - -"<<endl;
                          if(tc.getFollower(*p2)->getUsingEffectBonus()){
                            cout<<" *** This card is using the effect bonus"<<endl;
                          }else{
                            cout<<" *** This card is NOT using the effect bonus"<<endl;
                          }
                          cout<<"- - - - - - - - - - - - - - - - - -"<<endl;
                          cout << "________________________" << '\n';
                      }
                      int foll;     //index to the follower that will be selected
                      if(cc==0){
                        cout<<endl<<"*** This personality has no followers, only items ***"<<endl<<endl;
                        continue;
                      }else{
                        cout<<"Select the follower you want to discart"<<endl<<">> ";
                        while(!(cin >> foll) || (foll < 1 ) || ((unsigned) foll > tc.getPersonality(*pp)->getEquipList()->size() )){
                          cin.clear();
                          cin.ignore(numeric_limits<streamsize>::max(), '\n');
                          cout << "Invalid input. Please, try again: ";
                        }
                        cin.ignore();
                      }
                      auto pp2=tc.getPersonality(*pp)->getEquipList()->begin();     //iterator that will be used to store the selected follower
                      cc=1;
                      for (auto p2=tc.getPersonality(*pp)->getEquipList()->begin(); p2!=tc.getPersonality(*pp)->getEquipList()->end(); p2++){
                          if (tc.getFollower(*p2)==NULL){
                            continue;
                          }
                          if(cc==foll)
                            pp2=p2;   //the wanted follower
                          cc++;
                       }

                        sub-=tc.getFollower(*pp2)->getAttackBonus();    //decrease the attackPower that pl needs to lose
                        cout<<pl.getName()<<" lost "<<tc.getPersonality(*pp)->getName()<<"'s (personality) "<<tc.getFollower(*pp2)->getName()<<" (follower)..."<<endl;
                        tc.getPersonality(*pp)->setAttack( tc.getPersonality(*pp)->getAttack() - tc.getFollower(*pp2)->getAttackBonus() );    //remove the atttackBonus of the follower from his personality
                        if(tc.getFollower(*pp2)->getUsingEffectBonus()){    //if the follower was using the effect bonus, remove this also
                          tc.getPersonality(*pp)->setAttack( tc.getPersonality(*pp)->getAttack() - tc.getFollower(*pp2)->getEffectBonus() );
                          sub-=tc.getFollower(*pp2)->getEffectBonus();
                        }
                        delete *pp2;      //delete the follower
                        tc.getPersonality(*pp)->getEquipList()->erase(pp2);
                  }


                }   //end of the discards
                counter=1;
                for (auto p=pl.getArmy()->begin(); p!=pl.getArmy()->end(); p++ ){
                  if(!tc.getPersonality(*p)->getIsDead()){
                      for(int i=0;i<maxAttackingCards;i++){     //  ** for every personality that attacked and lived **
                          if(counter==cardsToAttack[i]){
                              tc.getPersonality(*p)->setIsTapped(true);   //tap them
                              tc.getPersonality(*p)->setHonour(tc.getPersonality(*p)->getHonour() - 1);   //decrease honour
                              if(tc.getPersonality(*p)->getHonour()==0){ /* Personality's suiside */
                                cout<<pl.getName()<<"  "<<tc.getPersonality(*p)->getName()<<" (personality)  is performing Seppuku..."<<endl;
                                tc.getPersonality(*p)->setIsDead(true);
                                continue;
                              }
                              for (auto p2=tc.getPersonality(*p)->getEquipList()->begin(); p2!=tc.getPersonality(*p)->getEquipList()->end();){
                                  auto ptemp2=p2;               // for every personality's items
                                  ptemp2++;
                                  if (tc.getItem(*p2)!=NULL){   //it's an Item
                                    if(tc.getItem(*p2)->getDurability()<=1){ // detouch of item
                                      delete *p2;
                                      tc.getPersonality(*p)->getEquipList()->erase(p2);
                                    }else{
                                        tc.getItem(*p2)->setDurability(tc.getItem(*p2)->getDurability()-1);   //decrease durability
                                    }
                                  }
                                  p2=ptemp2;
                              }
                          }

                      }
                  }
                  counter++;
                }
                counter=1;
                for (auto p=pl.getArmy()->begin(); p!=pl.getArmy()->end(); ){   //delete all the personalities that are dead
                  auto ptemp2=p;
                  ptemp2++;
                  if(tc.getPersonality(*p)->getIsDead()){
                    pl.getStats()->setArmyLost(pl.getStats()->getArmyLost() + 1);     // keep statistics of the army loss
                    delete *p;
                    pl.getArmy()->erase(p);
                  }
                  counter++;
                  p=ptemp2;
                }

            }else if( attackPower == defPower ){      //case 3, Tie
              cout<<"Tie!  Both "<<pl.getName()<<" and "<<(*pl2)->getName()<<" lost all the active army..."<<endl;
              counter=1;
              for (auto p=pl.getArmy()->begin(); p!=pl.getArmy()->end(); p++){    //delete the army of pl
                    auto ptemp=p;
                    ptemp++;
                    for(int i=0;i<maxAttackingCards;i++){
                        if(counter==cardsToAttack[i]){
                          pl.getStats()->setArmyLost(pl.getStats()->getArmyLost() + 1);     // keep statistics of the army loss
                          delete *p;
                          pl.getArmy()->erase(p);
                        }

                    }
                    counter++;
                    p=ptemp;
              }
              for (auto p=(*pl2)->getArmy()->begin(); p!=(*pl2)->getArmy()->end();){ //delete the army of pl2
                    auto ptemp=p;
                    ptemp++;
                    if(!(*p)->getIsTapped()){
                      (*pl2)->getStats()->setArmyLost((*pl2)->getStats()->getArmyLost() + 1);     // keep statistics of the army loss
                      delete *p;
                      (*pl2)->getArmy()->erase(p);
                    }
                    p=ptemp;
              }
            }else{        // case 4, defender wins
              int tempdef=(*pl2)->getSh()->get_initialDefence();    //the new defence power will be stored here, initialize with the province defence
              for (auto p=(*pl2)->getArmy()->begin(); p!=(*pl2)->getArmy()->end();p++){   //take the minimum number of cards to defend so as to minimize the difference between defPower and attackPower
                if(tempdef>attackPower)
                  break;
                if(!(*p)->getIsTapped()){
                  tc.getPersonality((*p))->setIsDefending(true);
                  tempdef+=tc.getPersonality((*p))->getDefence();
                }
              }
              cout << "Defence Power: "<<tempdef<< '\n'<<endl;
              defPower=tempdef;
              counter=1;
              cout<<(*pl2)->getName()<<" won the fight!"<<endl;
              cout<<pl.getName()<<" lost all his/her attacking army..."<<endl;
              for (auto p=pl.getArmy()->begin(); p!=pl.getArmy()->end();){    //attacker loses all army (pl)
                    auto ptemp=p;
                    ptemp++;
                    for(int i=0;i<maxAttackingCards;i++){
                        if(counter==cardsToAttack[i]){
                          pl.getStats()->setArmyLost(pl.getStats()->getArmyLost() + 1);     // keep statistics of the army loss
                          delete *p;
                          pl.getArmy()->erase(p);
                        }

                    }
                    counter++;
                    p=ptemp;
              }
              int sub=defPower-attackPower;     //same as case 2, with the difference that there is not a selection
              for (auto p=(*pl2)->getArmy()->begin(); p!=(*pl2)->getArmy()->end();){    //for every personality in the army
                    auto ptemp=p;
                    ptemp++;
                    if(tc.getPersonality((*p))->getIsDefending()){     //if it was used to defend
                      if (tc.getPersonality(*p)==NULL)
                        continue;
                      for (auto p2=tc.getPersonality(*p)->getEquipList()->begin(); p2!=tc.getPersonality(*p)->getEquipList()->end();){   //for every follower of this personality
                        auto ptemp2=p2;
                        ptemp2++;
                        if (tc.getFollower(*p2)==NULL)
                          continue;
                        if(sub<=0)    //if the needed attack is lost, stop
                          break;
                        cout<<(*pl2)->getName()<<" lost "<<tc.getPersonality(*p)->getName()<<"'s (personality) "<<tc.getFollower(*p2)->getName()<<" (follower)..."<<endl;  //discart the follower
                        tc.getPersonality(*p)->setAttack( tc.getPersonality(*p)->getAttack() - tc.getFollower(*p2)->getAttackBonus() );
                        sub-=tc.getFollower(*p2)->getAttackBonus();   //decrease the atttack needed to lose
                        if(tc.getFollower(*p2)->getUsingEffectBonus()){
                          tc.getPersonality(*p)->setAttack( tc.getPersonality(*p)->getAttack() - tc.getFollower(*p2)->getEffectBonus() );
                          sub-=tc.getFollower(*p2)->getEffectBonus();
                        }
                        delete *p2;
                        tc.getPersonality(*p)->getEquipList()->erase(p2);
                        p2=ptemp2;
                      }
                      if(sub<=0)
                        break;
                      cout<<(*pl2)->getName()<<" lost "<<tc.getPersonality(*p)->getName()<<" (personality)..."<<endl;   //if the goal is not reached by discarding the followers, discard the personality
                      (*pl2)->getStats()->setArmyLost((*pl2)->getStats()->getArmyLost() + 1);
                      sub-=tc.getPersonality(*p)->getAttack();
                      delete *p;
                      (*pl2)->getArmy()->erase(p);
                    }
                    p=ptemp;
              }

              for (auto p=(*pl2)->getArmy()->begin(); p!=(*pl2)->getArmy()->end();p++){
                  if(tc.getPersonality((*p))->getIsDefending())
                    (*p)->setIsTapped(true);    //tap all the defending army tha lived
                  tc.getPersonality((*p))->setIsDefending(false);   //reset to false
              }

            }



      }
  }
}


void GameBoard::economyPhase(){
  for (auto pp=playersList->begin(); pp!=playersList->end(); pp++){

      Player& pl=*(*pp);
      cout <<endl<<endl<< "---------------------------------" << '\n';
      cout<<">Economy Phase"<<endl;
      cout << "---------------------------------" << '\n';
      cout<<">Player: "<<pl.getName()<<" plays."<< endl;
      sleep(2);

      TypeConverter tc;
      int provincecard;
      int holdingcard;

      for(;;) {
        if(!pl.printProvinces()){
          cout << "-> There aren't available provinces to buy! <-" << '\n';
          sleep(2);
          break;
        }
        cout<<">Select the province card that you want to buy (1-4) OR 0 to quit: "<<endl<<">> ";
        while(!(cin >> provincecard) || (provincecard < 0 || (unsigned) provincecard > pl.getProvinces()->size() )){
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input. Please, try again: ";
        }
        cin.ignore();

        if(provincecard==0){
          break;
        }


        auto prov=pl.getProvinces()->begin();


        for(int i=0; i<provincecard;i++)
          prov++;
        prov--;

        if( (*prov)->getCost() > pl.maxHarvestMoney() ){
          cout<<"Cannot collect so much money by tapping your holdings. Please select another card."<<endl;
          sleep(2);
          continue;
        }

        /* Holdings tapping process */
        for(;;){

          if(!pl.printHoldings()){
            cout << "-> All holdings are Tapped! <-" << endl;
            sleep(2);
            break;
          }

          cout<<">>Current money: "<<pl.getMoney()<<endl;
          cout<<">Select the holding card that you want to tap OR 0 to quit: "<<endl<<">> ";
          while(!(cin >> holdingcard) || (holdingcard < 0 || (unsigned) holdingcard > pl.getHoldings()->size() )){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please, try again: ";
          }
          cin.ignore();

          if(holdingcard==0){
            break;
          }

            auto hol=pl.getHoldings()->begin();
            for(int i=0; i<holdingcard;i++)
              hol++;
            hol--;

            (*hol)->setIsTapped(true); /* tapping */

            pl.setMoney(pl.getMoney() + tc.getHolding(*hol)->getHarvestValue());

            if(pl.getMoney() >= (*prov)->getCost()){
              cout<<endl << ">Enough money to buy the card (end of tapping holdings process)." <<endl;
              cout << "Card's cost: "<<(*prov)->getCost()<<" | Current money: "<<pl.getMoney()<<endl;
              sleep(1);
              break;
            }
          }

        if(pl.getMoney()>=(*prov)->getCost()){
          cout<<endl<< ">Bought!" <<endl;
          sleep(1);
          if(tc.getPersonality(*prov)!=NULL){ /* Personality */
            /* with splice: transfer Personality (BlackCard) from Provinces list to Army list */
            pl.getArmy()->splice(pl.getArmy()->begin(), *(pl.getProvinces()), prov);
          }
          else if(tc.getHolding(*prov)!=NULL){ /* Holding */
            /* with splice: transfer Holding (BlackCard) from hand Provinces list  to Holdings list */
            tc.getHolding(*prov)->setIsTapped(true); /* Player will use this new holding card to the next round */
            pl.getHoldings()->splice(pl.getHoldings()->begin(), *(pl.getProvinces()), prov);
            connectHoldings(pl.getHoldings()); /* make connections for the new added holding */

          }

          pl.setMoney(pl.getMoney()-(*prov)->getCost());
          pl.getStats()->setMoneySpent(pl.getStats()->getMoneySpent()+(*prov)->getCost());    //statistics

          auto dd=pl.getDynastyDeck()->begin();
          auto provChanged=pl.getProvinces()->begin();
          /* replace the space of bought card in Provinces list  */
          for(int i=0;i<provincecard-1;i++)
            provChanged++;
          /* with splice: transfer a BlackCard from dynastyDeck list to Provinces list */
          pl.getProvinces()->splice(provChanged, *(pl.getDynastyDeck()), dd);
        }
        else{
          cout << ">Not enough money, please try another card..." <<endl<<endl;
          sleep(1);
        }
        cout<<endl <<">Lost Money : "<<pl.getMoney()<<endl<<endl;
        pl.getStats()->setMoneyLost(pl.getStats()->getMoneyLost()+pl.getMoney());    //statistics
        sleep(1);
        pl.setMoney(0);
      }
  }
}

bool GameBoard::finalPhase(){
  for (auto pp=playersList->begin(); pp!=playersList->end();pp++){
    Player& pl=*(*pp);
    cout <<endl<<endl<< "---------------------------------" << '\n';
    cout<<"     >Final Phase"<<endl;
    cout << "---------------------------------" << '\n';
    cout<<">Player: "<<pl.getName()<<" plays."<< endl;
    sleep(2);
    if(pl.getHand()->size()<=MAXHAND){      //check if the player reached the maximum number of cards in his hand
      cout<<">You don't need to discard any card."<<endl;
      sleep(2);
    }
      while(pl.getHand()->size()>MAXHAND){        // dicard the extra cards
        cout<<endl<<"       ** "<<pl.getName()<<" **"<<endl;
        cout<<"** You have a lot of cards in your hand. **"<<endl;
        pl.printHand();     //print all the cards in hand
        cout<<">Select a card to discard:"<<endl<<">> ";
        int card;   //index to the selected card (from input)
        while(!(cin >> card) || (card < 1 || card > (signed) pl.getHand()->size())){    //check if input is valid
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Invalid input. Please, try again: ";
        }
        cin.ignore();
        int count=1;
        for (auto p=pl.getHand()->begin(); p!=pl.getHand()->end();p++){
              if(count==card){    //find the selecetd card
                delete *p;
                pl.getHand()->erase(p);     //delete the selecetd card
                break;
              }
              count++;
        }
        if(pl.getHand()->size()>MAXHAND)
          cout<<">You need to remove "<<pl.getHand()->size()-MAXHAND<<" more card"<<endl;
        else
          cout<<">OK, you don't need to discard more cards"<<endl;
      }

      pl.getStats()->setFinalArmy(pl.getArmy()->size());      //set the final values for the statistics
  }
  for (auto p=playersList->begin(); p!=playersList->end();p++){     //for every player
    cout<<endl<<endl<<"______________________________________________________________________"<<endl;
    cout<<endl<<"               *****************  "<<(*p)->getName()<<"  *****************"<<endl;
    cout<<"______________________________________________________________________"<<endl;
    sleep(1);
    if(!(*p)->printProvinces()){      //print his provinces
      cout << "-> There aren't available provinces! <-" << '\n';
    }
    (*p)->printHand();      //print his hand
    (*p)->printAllHoldings();   //print his holdings
    printArena(*(*p));
    cout<<endl<<endl << ">Press ENTER to continue." << '\n';
    getchar();

  }
  printGameStatistics();      //print the statistics of the round
  Player *winner=checkWinningCondition();     //check if a player won  (pointer to the winner or NULL if no one won)
  if(winner!=NULL){
    cout<<"*********   Winner:  "<<winner->getName()<<" *********"<<endl;
    return true;
  }else{
    return false;
  }
  sleep(4);
}

void GameBoard::printArena(Player& pl)const{
  cout <<endl<< "                     ---------------------------------" << '\n';
  cout<<"                           Printing Arena of "<<pl.getName()<<endl;
  cout << "                     ---------------------------------" << '\n';
  if(pl.getArmy()->empty()){
    cout<<"                ****   "<<pl.getName()<<" has no army!   ****"<<endl;
    return;
  }

  for (auto p=pl.getArmy()->begin(); p!=pl.getArmy()->end(); p++){        //print the army of the player (personalities and followers/items)
    cout << "-----------------------------------------------------" << '\n';
    cout<<"    Personality: "<<endl;
    (*p)->print();          //print a personality
    cout << "-----------------------------------------------------" << '\n';
    TypeConverter tc;
    if (tc.getPersonality(*p)==NULL)
      continue;
    if(tc.getPersonality(*p)->getEquipList()->empty()){     //if this personality has no Followers/Items
      continue;
    }
      cout<<"  * * * * * * * * * * * * * * * * * * * * *"<<endl;
    cout<<"   "<<(*p)->getName()<<"'s followers/Items"<<endl;     //printing the Personality's  Followers/Items
    for (auto p2=tc.getPersonality(*p)->getEquipList()->begin(); p2!=tc.getPersonality(*p)->getEquipList()->end(); p2++){
      cout << "- - - - - - - - - - - - - - - - - - - - - - " << '\n';
      (*p2)->print();
      cout << "- - - - - - - - - - - - - - - - - - - - - - " << '\n';
    }
  }
}

Player *GameBoard::checkWinningCondition() const{
  auto temp=playersList->begin();
  for (auto p=playersList->begin(); p!=playersList->end();){
    temp=p;
    temp++;
    if((*p)->getProvinces()->size()==0){    // if a player has no provinces is eliminated
      cout<<endl<<"****  Player: "<<(*p)->getName()<<" lost all his provinces ****"<<endl;
      cout<<"****** "<<(*p)->getName()<<" is eliminated! ******"<<endl;
      delete *p;
      playersList->erase(p);
      sleep(2);
    }
    p=temp;
  }
  if(playersList->size()<=1){     // if there is only 1 player left with provinces, he is the winner
    return *(playersList->begin());
  }else{
    return NULL;
  }
}

void GameBoard::printGameStatistics()const{
  cout<<"_____________________________ GAME STATISTICS _____________________________"<<endl;
  for (auto p=playersList->begin(); p!=playersList->end();p++){     //for every player
        cout<<endl<<"               ______ "<<(*p)->getName()<<"______"<<endl<<endl;
        if((*p)->getStats()->getInitialArmy()==0 || (*p)->getStats()->getFinalArmy()==0){     //army stats
          cout<<"- Your army size went from "<<(*p)->getStats()->getInitialArmy()<<" to "<<(*p)->getStats()->getFinalArmy()<<"    (cannot calculate percentage with 0 values)"<<endl;
        }else if((*p)->getStats()->getInitialArmy()>(*p)->getStats()->getFinalArmy()){
            cout<<"- Your army was decreased by  "<<(*p)->getStats()->armyPercentage()<<"% in this round"<<endl;
        }else if((*p)->getStats()->getInitialArmy()<(*p)->getStats()->getFinalArmy()){
          cout<<"- Your army was increased by  "<<(*p)->getStats()->armyPercentage()<<"% in this round"<<endl;
        }else{
          cout<<"- Your army's size remained the same as the previous round"<<endl;
        }

        if((*p)->getStats()->getArmyLost()==0)      //army lost in battle
          cout<<"- You didn't lose any of your initial army (your army at the start of the round) in batlle"<<endl;
        else if((*p)->getStats()->getInitialArmy()==(*p)->getStats()->getArmyLost())
          cout<<"- You lost all of your initial army on battlePhase, 100% of your army was lost during battles. "<<endl;
        else
          cout<<"- You lost "<<(*p)->getStats()->armyLostPercentage()<<" % of your intial army (your army at the start of the round) in battle"<<endl;

        if((*p)->getStats()->getMoneySpent()==0)      //army lost in battle
          cout<<"- You didn't spend any of your money in this round"<<endl;
        else
          cout<<"- You spent "<<(*p)->getStats()->getMoneySpent()<<" coins during equip and economy phase"<<endl;

        if((*p)->getStats()->getMoneyLost()==0)      //army lost in battle
          cout<<"- You haven't lost any money yet"<<endl;
        else
          cout<<"- You lost "<<(*p)->getStats()->getMoneyLost()<<" coins during this game"<<endl;

        cout<<"- You gained "<<(*p)->getStats()->getAttackBonus()<<" attack bonus from follower/items in this round"<<endl;
        cout<<"- You gained "<<(*p)->getStats()->getDefenceBonus()<<" defence bonus from follower/items in this round"<<endl;

  }

  cout<<endl<<endl << ">Press ENTER to continue." << '\n';
  getchar();

}

void GameBoard::gameplay(){
 cout<<endl << ">Gameplay Begins.<" << endl;
 for(;;){
      startingPhase();
      equipPhase();
      battlePhase();
      economyPhase();
      if(finalPhase())  /* we have a winner, game over. */
        return;
 }
}
