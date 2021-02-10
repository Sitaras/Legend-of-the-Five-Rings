#include "Player.hpp"
#include "TypeConverter.hpp"

Player::~Player(){

  list<GreenCard *>::iterator it1=hand->begin(); /* delete hand */
  while(!hand->empty()){
    delete *it1;
    it1=hand->erase(it1);
  }
  delete hand;

  list<BlackCard *>::iterator it2=holdings->begin(); /* delete holdings */
  while(!holdings->empty()){
    delete *it2;
    it2=holdings->erase(it2);
  }
  delete holdings;

  list<BlackCard *>::iterator it3=provinces->begin();

  while(!provinces->empty()){ /* delete provinces */
    delete *it3;
    it3=provinces->erase(it3);
  }
  delete provinces;

  list<BlackCard *>::iterator it4=army->begin();/* delete army */
  while(!army->empty()){
    delete *it4;        //destructor of personalities deletes the equipList (followers/items)
    it4=army->erase(it4);
  }

 delete army;

 delete stats;

}


Player::Player(string n)
:name(n),
hand(new list<GreenCard*>()),
holdings(new list<BlackCard*>),
army(new list<BlackCard*>),
provinces(new list<BlackCard*>),
sh(new Stronghold()),
numberOfProvinces(4),
money(0),
honour(sh->get_startingHonour()),
stats(new Statistics())
{
holdings->push_front(sh); /* Stronghold is the first holding of the Player (basic money source) */
}

string Player::getName() const {
  return name;
}

Stronghold* Player::getSh() const{
  return sh;
}

int Player::getNumberOfProvinces() const{
  return numberOfProvinces;
}

int Player::getMoney() const {
  return money;
}

int Player::getHonour() const{
  return honour;
}

list<BlackCard*>* Player::getProvinces() const{
  return provinces;
}

list<BlackCard*>* Player::getArmy() const{
  return army;
}

list<BlackCard*>* Player::getDynastyDeck() const{
  return dynastyDeck;
}

list<GreenCard*>* Player::getFateDeck() const{
  return fateDeck;
}

list<GreenCard*>* Player::getHand() const{
  return hand;
}

list<BlackCard*>* Player::getHoldings() const{
  return holdings;
}

Statistics *Player::getStats()const{
  return stats;
}

void Player::setDynastyDeck(list<BlackCard*>* dynasty){
  dynastyDeck=dynasty;
}

void Player::setFateDeck(list<GreenCard*>* fate){
 fateDeck=fate;
}

void Player::setMoney(int m) {
  money=m;
}

void Player::setHonour(int h){
  honour=h;
}

void Player::untapEverything(){

  for(auto hl=holdings->begin(); hl!=holdings->end(); hl++){
    (*hl)->setIsTapped(false);
  }

  for(auto ar=army->begin(); ar!=army->end(); ar++){
    (*ar)->setIsTapped(false);
  }

}

void Player::drawFateCard() {

  hand->splice(hand->begin(), *fateDeck, fateDeck->begin());

}

void Player::revealProvinces(){
  for(auto prov=provinces->begin();prov!=provinces->end();prov++)
    (*prov)->setIsReleaved(true);
}

void Player::printHand() const{
  cout << "---------------------------------" << '\n';
  cout<<">Money: "<<money<<endl;
  cout<<">Hand: "<<endl;
  cout << "---------------------------------" << '\n';
  int i=1;
  for(auto h=hand->begin(); h!=hand->end();h++){
      cout << "Card no."<< i << endl;
      cout << "________________________" << '\n';
      (*h)->print();
      cout << "________________________" << '\n';
      i++;
  }
}

int Player::printProvinces() const{
  cout << "---------------------------------" << '\n';
  cout<<">Provinces: "<<endl;
  cout << "---------------------------------" << '\n';
  int i=1,ok=0;
  for(auto pr=provinces->begin(); pr!=provinces->end();pr++){
    if((*pr)->getIsReleaved()){
      ok=1;
      cout << "Card no."<< i << endl;
      cout << "________________________" << '\n';
      (*pr)->print();
      cout << "________________________" << '\n';
    }
    i++;
  }

  return ok;
}

void Player::AvailableProvinces() const{
  cout << "---------------------------------" << '\n';
  cout<<">Provinces: "<<endl;
  cout << "---------------------------------" << '\n';
  int i=1;
  for(auto pr=provinces->begin(); pr!=provinces->end();pr++){
    cout << "~Province Card: no."<< i << "  Defence: "<<sh->get_initialDefence()<< endl<<endl;
    i++;
  }
}

int Player::printHoldings() const{
  cout << "---------------------------------" << '\n';
  cout<<">Money: "<<money<<endl;
  cout<<">Holdings: "<<endl;
  cout << "---------------------------------" << '\n';
  int i=1;
  int ok=0;
  for(auto hol=holdings->begin(); hol!=holdings->end();hol++){
    if((*hol)->getIsTapped()==false){
      ok=1;
      cout << "Card no."<< i << endl;
      cout << "________________________" << '\n';
      (*hol)->print();
      cout << "________________________" << '\n';
    }
    i++;
  }

    return ok;


}

void Player::printAllHoldings() const{
  cout << "---------------------------------" << '\n';
  cout<<">Money: "<<money<<endl;
  cout<<">Holdings: "<<endl;
  cout << "---------------------------------" << '\n';
  int i=1;
  for(auto hol=holdings->begin(); hol!=holdings->end();hol++){
      cout << "Card no."<< i << endl;
      cout << "________________________" << '\n';
      (*hol)->print();
      cout << "________________________" << '\n';
    i++;
  }
}

void Player::printArmy() const{
  cout << "---------------------------------" << '\n';
  cout<<">Army: "<<endl;
  cout << "---------------------------------" << '\n';
  int i=1;
  for(auto ar=army->begin(); ar!=army->end();ar++){
      cout << "Card no."<< i << endl;
      cout << "________________________" << '\n';
      (*ar)->print();
      cout << "________________________" << '\n';
      i++;
  }

}

int Player::printUntappedArmy() const{
  cout << "---------------------------------" << '\n';
  cout<<">Untapped Army: "<<endl;
  cout << "---------------------------------" << '\n';
  int count=0;
  int i=1;
  for(auto ar=army->begin(); ar!=army->end();ar++){
    if((*ar)->getIsTapped()==false){
        cout << "Card no."<< i << endl;
        cout << "________________________" << '\n';
        (*ar)->print();
        count++;
    }
    i++;
    cout << "________________________" << '\n';
  }
  return count;
}

int Player::untappedArmy()const{
  int count=0;
  for(auto ar=army->begin(); ar!=army->end();ar++){
      if((*ar)->getIsTapped()==false)
        count++;
  }
  return count;
}

int Player::maxHarvestMoney() const{
    TypeConverter tc;
    int sum=0;
    for(auto hol=holdings->begin(); hol!=holdings->end();hol++){
      if(!(*hol)->getIsTapped())
        sum+=tc.getHolding(*hol)->getHarvestValue();
    }
    return sum;
}
