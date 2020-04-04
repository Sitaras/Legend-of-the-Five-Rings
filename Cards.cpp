#include "Cards.hpp"

const unsigned int MAXEQUIP=3;
const unsigned int MAXHAND=6;

///////////////////  CARD  ///////////////////////////

Card::Card():name("NoName"),cost(0),isTapped(false),type(-1)
{}

Card::Card(string nam,int cos,int t,int k)
:name(nam),cost(cos),isTapped(false),type(t),kind(k){

}

int Card::getCost() const{
  return cost;
}

string Card::getName() const{
  return name;
}

void Card::setIsTapped(bool b){
  isTapped=b;
}

bool Card::getIsTapped() const{
  return isTapped;
}

Card::~Card(){

}


///////////////////  GREENCARD  ///////////////////////////////

GreenCard::GreenCard()
:attackBonus(0),
defenceBonus(0),
minimumHonour(0),
effectCost(0),
effectBonus(0),
UsingEffectBonus(false),
cardText("EMPTY")
{}

GreenCard::GreenCard(string nam,int cos,int t,int k,int attackBonus2,int defenceBonus2,string cardText2,int effectCost2,int effectBonus2,int minimumHonour2)
:Card(nam,cos,t,k),
attackBonus(attackBonus2),
defenceBonus(defenceBonus2),
minimumHonour(minimumHonour2),
effectCost(effectCost2),
effectBonus(effectBonus2),
cardText(cardText2)
{

}

int GreenCard::getMinimumHonour() const{
  return minimumHonour;
}

int GreenCard::getAttackBonus() const{
  return attackBonus;
}
int GreenCard::getDefenceBonus() const{
  return defenceBonus;
}

int GreenCard::getEffectBonus() const{
  return effectBonus;
}

int GreenCard::getEffectCost() const{
  return effectCost;
}

bool GreenCard::getUsingEffectBonus() const {
  return UsingEffectBonus;
}

void GreenCard::setUsingEffectBonus(bool b) {
  UsingEffectBonus=b;
}

GreenCard::~GreenCard(){}
///////////////// BLACKCARD  /////////////////////////////////

BlackCard::BlackCard()
:isReleaved(false){}

BlackCard::BlackCard(string nam,int cos,int t,int k)
:Card(nam,cos,t,k),isReleaved(false){}

BlackCard::~BlackCard() {
}

void BlackCard::setIsReleaved(bool b){
  isReleaved=b;
}

bool BlackCard::getIsReleaved() const{
  return isReleaved;
}

////////////////  FOLLOWER  //////////////////////////////////

Follower::Follower(string nam,int cos,int k, int attackBonus2,int defenceBonus2,int minimumHonour2,int effectCost2,int effectBonus2,string cardText2)
:GreenCard(nam,cos,FOLLOWER,k,attackBonus2,defenceBonus2,cardText2,effectCost2,effectBonus2,minimumHonour2)
{}

Follower::~Follower(){

}


int Follower::getType() const{
  return type;
}


Footsoldier::Footsoldier(string nam)
:Follower(nam,0,FOOTSOLDIER,2,0,1,1,2," "){

}


Footsoldier::~Footsoldier(){

}

  void Footsoldier::print() const{
    cout<<"-Card's Name: "<<name<<endl;
    cout<<"-Cost: "<<cost<<endl;
    cout<<"-Attack Bonus: "<<attackBonus<<endl;
    cout<<"-Defence Bonus: "<<defenceBonus<<endl;
    cout<<"-Minimum Honour: "<<minimumHonour<<endl;
    cout<<"-Effect Cost: "<<effectCost<<endl;
    cout<<"-Effect Bonus: "<<effectBonus<<endl;
  }

  int Footsoldier::getKind() const{
   return kind;
  }

Archer::Archer(string nam)
:Follower(nam,0,ARCHER,0,2,1,1,2," "){

}
Archer::~Archer(){}

int Archer::getKind() const{
 return kind;
}

void Archer::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack Bonus: "<<attackBonus<<endl;
  cout<<"-Defence Bonus: "<<defenceBonus<<endl;
  cout<<"-Minimum Honour: "<<minimumHonour<<endl;
  cout<<"-Effect Cost: "<<effectCost<<endl;
  cout<<"-Effect Bonus: "<<effectBonus<<endl;
}


Sieger::Sieger(string nam)
:Follower(nam,5,SIEGER,3,3,2,2,3," "){
}
Sieger::~Sieger(){

}

void Sieger::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack Bonus: "<<attackBonus<<endl;
  cout<<"-Defence Bonus: "<<defenceBonus<<endl;
  cout<<"-Minimum Honour: "<<minimumHonour<<endl;
  cout<<"-Effect Cost: "<<effectCost<<endl;
  cout<<"-Effect Bonus: "<<effectBonus<<endl;
}

int Sieger::getKind() const{
 return kind;
}


Cavalry::Cavalry(string nam)
:Follower(nam,2,CAVALRY,4,2,3,3,4," "){

}
Cavalry::~Cavalry(){
}

void Cavalry::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack Bonus: "<<attackBonus<<endl;
  cout<<"-Defence Bonus: "<<defenceBonus<<endl;
  cout<<"-Minimum Honour: "<<minimumHonour<<endl;
  cout<<"-Effect Cost: "<<effectCost<<endl;
  cout<<"-Effect Bonus: "<<effectBonus<<endl;
}

int Cavalry::getKind() const{
 return kind;
}


Atakebune::Atakebune(string nam)
:Follower(nam,3,NAVAL,2,4,3,3,4," "){

}

Atakebune::~Atakebune(){

}


void Atakebune::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack Bonus: "<<attackBonus<<endl;
  cout<<"-Defence Bonus: "<<defenceBonus<<endl;
  cout<<"-Minimum Honour: "<<minimumHonour<<endl;
  cout<<"-Effect Cost: "<<effectCost<<endl;
  cout<<"-Effect Bonus: "<<effectBonus<<endl;
}

int Atakebune::getKind() const{
 return kind;
}

Bushido::Bushido(string nam)
:Follower(nam,8,BUSHIDO,8,8,6,3,8," "){

}

Bushido::~Bushido(){

}

void Bushido::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack Bonus: "<<attackBonus<<endl;
  cout<<"-Defence Bonus: "<<defenceBonus<<endl;
  cout<<"-Minimum Honour: "<<minimumHonour<<endl;
  cout<<"-Effect Cost: "<<effectCost<<endl;
  cout<<"-Effect Bonus: "<<effectBonus<<endl;
}

int Bushido::getKind() const{
 return kind;
}

///////////////////  ITEM  ////////////////////////////////

Item::Item(string nam,int cos,int k,int attackBonus2,int defenceBonus2,int minimumHonour2,int effectCost2,int effectBonus2,int dur,string cardText2)
:GreenCard(nam,cos,ITEM,k,attackBonus2,defenceBonus2,cardText2,effectCost2,effectBonus2,minimumHonour2),
durability(dur){

}

Item::~Item(){

}

int Item::getType() const{
  return type;
}



int Item::getDurability()const{
  return durability;
}

void Item::setDurability(int x){
   durability=x;
}

Katana::Katana(string nam)
:Item(nam,0,KATANA,2,0,1,1,2,3," "){
}

Katana::~Katana(){

}

void Katana::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack Bonus: "<<attackBonus<<endl;
  cout<<"-Defence Bonus: "<<defenceBonus<<endl;
  cout<<"-Minimum Honour: "<<minimumHonour<<endl;
  cout<<"-Effect Cost: "<<effectCost<<endl;
  cout<<"-Effect Bonus: "<<effectBonus<<endl;
  cout<<"-Durability: "<<durability<<endl;

}

int Katana::getKind() const{
 return kind;
}

Spear::Spear(string nam)
:Item(nam,0,SPEAR,0,2,1,1,2,3," "){
}

Spear::~Spear(){

}

void Spear::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack Bonus: "<<attackBonus<<endl;
  cout<<"-Defence Bonus: "<<defenceBonus<<endl;
  cout<<"-Minimum Honour: "<<minimumHonour<<endl;
  cout<<"-Effect Cost: "<<effectCost<<endl;
  cout<<"-Effect Bonus: "<<effectBonus<<endl;
  cout<<"-Durability: "<<durability<<endl;

}

int Spear::getKind() const{
 return kind;
}

Bow::Bow(string nam)
:Item(nam,2,BOW,2,2,2,3,4,5," "){

}

Bow::~Bow(){

}

void Bow::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack Bonus: "<<attackBonus<<endl;
  cout<<"-Defence Bonus: "<<defenceBonus<<endl;
  cout<<"-Minimum Honour: "<<minimumHonour<<endl;
  cout<<"-Effect Cost: "<<effectCost<<endl;
  cout<<"-Effect Bonus: "<<effectBonus<<endl;
  cout<<"-Durability: "<<durability<<endl;

}

int Bow::getKind() const{
 return kind;
}

Ninjato::Ninjato(string nam)
:Item(nam,4,NINJATO,3,3,3,2,2,4," "){
}

Ninjato::~Ninjato(){

}

void Ninjato::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack Bonus: "<<attackBonus<<endl;
  cout<<"-Defence Bonus: "<<defenceBonus<<endl;
  cout<<"-Minimum Honour: "<<minimumHonour<<endl;
  cout<<"-Effect Cost: "<<effectCost<<endl;
  cout<<"-Effect Bonus: "<<effectBonus<<endl;
  cout<<"-Durability: "<<durability<<endl;

}

int Ninjato::getKind() const{
 return kind;
}


Wakizashi::Wakizashi(string nam)
:Item(nam,8,WAKIZASHI,5,5,3,3,3,8," "){

}
Wakizashi::~Wakizashi(){

}


void Wakizashi::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack Bonus: "<<attackBonus<<endl;
  cout<<"-Defence Bonus: "<<defenceBonus<<endl;
  cout<<"-Minimum Honour: "<<minimumHonour<<endl;
  cout<<"-Effect Cost: "<<effectCost<<endl;
  cout<<"-Effect Bonus: "<<effectBonus<<endl;
  cout<<"-Durability: "<<durability<<endl;

}

int Wakizashi::getKind() const{
 return kind;
}




//////////////////  PERSONALITY  ////////////////////////////////


Personality::Personality(string nam, int cos,int k ,int att,int def,int hon)
:BlackCard(nam,cos,PERSONALITY,k),
attack(att),
defence(def),
honour(hon),
isDead(false),
equipList(new list<GreenCard*>),
isDefending(false){

}

Personality::~Personality(){
  list<GreenCard *>::iterator el=equipList->begin();
  while(!equipList->empty()){
      delete *el;
      el=equipList->erase(el);
    }

    delete equipList;
    equipList=NULL;
}

int Personality::getType() const{
  return type;
}

int Personality::getHonour() const{
  return honour;
}

void Personality::setHonour(int x) {
   honour=x;
}

int Personality::getAttack() const{
  return attack;
}

int Personality::getDefence() const{
  return defence;
}
bool Personality::getIsDefending()const{
  return isDefending;
}
void Personality::setIsDefending(bool x){
  isDefending=x;
}
void Personality::setAttack(int x) {
  attack=x;
}
void Personality::setDefence(int x) {
  defence=x;
}

list<GreenCard*>* Personality::getEquipList() const{
  return equipList;
}

void Personality::setIsDead(bool x){
  isDead=x;
}

bool Personality::getIsDead() const{
  return isDead;
}

void Personality::setIsTapped(bool b){
  isTapped=b;
  list<GreenCard*>* equip=this->getEquipList();
  for(auto eq=equip->begin(); eq!=equip->end(); eq++){
    (*eq)->setIsTapped(b);
  }
}


Attacker::Attacker(string nam)
:Personality(nam,5,ATTACKER,3,2,2){

}

Attacker::~Attacker(){

}

void Attacker::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack: "<<attack<<endl;
  cout<<"-Defence: "<<defence<<endl;
  cout<<"-Honor: "<<honour<<endl;
}

int Attacker::getKind() const{
 return kind;
}


Defender::Defender(string nam)
:Personality(nam,5,DEFENDER,2,3,2){

}

Defender::~Defender(){

}

void Defender::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack: "<<attack<<endl;
  cout<<"-Defence: "<<defence<<endl;
  cout<<"-Honor: "<<honour<<endl;
}

int Defender::getKind() const{
 return kind;
}

Shogun::Shogun(string nam)
:Personality(nam,15,SHOGUN,10,5,8){

}
Shogun::~Shogun(){

}

void Shogun::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack: "<<attack<<endl;
  cout<<"-Defence: "<<defence<<endl;
  cout<<"-Honor: "<<honour<<endl;
}

int Shogun::getKind() const{
 return kind;
}

Chancellor::Chancellor(string nam)
:Personality(nam,15,CHANCELLOR,5,10,8){

}
Chancellor::~Chancellor(){

}

void Chancellor::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack: "<<attack<<endl;
  cout<<"-Defence: "<<defence<<endl;
  cout<<"-Honor: "<<honour<<endl;
}

int Chancellor::getKind() const{
 return kind;
}

Champion::Champion(string nam)
:Personality(nam,30,CHAMPION,20,20,12){

}
Champion::~Champion(){

}

void Champion::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Attack: "<<attack<<endl;
  cout<<"-Defence: "<<defence<<endl;
  cout<<"-Honor: "<<honour<<endl;
}

int Champion::getKind() const{
 return kind;
}

//////////////////  HOLDING  ////////////////////////////////


Holding::Holding(string nam,int cos,int k,int har)
:BlackCard(nam,cos,HOLDING,k),
upperHolding(NULL),
subHolding(NULL),
harvestValue(har)
{}

Holding::~Holding(){

}

int Holding::getType() const{
  return type;
}

int Holding::getHarvestValue() const{
  return harvestValue;
}

void Holding::setHarvestValue(int v){
  harvestValue=v;
}

void Holding::setupperHolding(Holding *h){
  upperHolding=h;
}

void Holding::setsubHolding(Holding *h){
  subHolding=h;
}

Holding* Holding::getsubHolding() const {
  return subHolding;
}

Holding* Holding::getupperHolding() const {
  return upperHolding;
}



//////////////////////////////////////////////////
GiftsandFavour::GiftsandFavour(string nam)
:Holding(nam,2,SOLO,2){
}
int GiftsandFavour::getKind()const{
 return kind;
}
GiftsandFavour::~GiftsandFavour(){

}

void GiftsandFavour::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Harvest Value: "<<harvestValue<<endl;
}


Plain::Plain(string nam)
:Holding(nam,2,PLAIN,2){
}
int Plain::getKind()const{
 return kind;
}
Plain::~Plain(){

}

void Plain::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Harvest Value: "<<harvestValue<<endl;
}


Farmland::Farmland(string nam)
:Holding(nam,3,FARMS,4){

}
int Farmland::getKind()const{
 return kind;
}
Farmland::~Farmland(){

}

void Farmland::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Harvest Value: "<<harvestValue<<endl;
}


Mine::Mine(string nam)
:Holding(nam,5,MINE,3){

}
int Mine::getKind()const{
 return kind;
}
Mine::~Mine(){

}

void Mine::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Harvest Value: "<<harvestValue<<endl;
}

GoldMine::GoldMine(string nam)
:Holding(nam,7,GOLD_MINE,5){

}
int GoldMine::getKind()const{
 return kind;
}
GoldMine::~GoldMine(){

}

void GoldMine::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Harvest Value: "<<harvestValue<<endl;
}

CrystalMine::CrystalMine(string nam)
:Holding(nam,12,CRYSTAL_MINE,6){

}
int CrystalMine::getKind() const{
 return kind;
}
CrystalMine::~CrystalMine(){

}

void CrystalMine::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Cost: "<<cost<<endl;
  cout<<"-Harvest Value: "<<harvestValue<<endl;
}


Stronghold::Stronghold()
:Holding("Stronghold",0,STRONGHOLD,5),startingHonour(5),initialDefence(5){

}
int Stronghold::getKind() const{
 return kind;
}

void Stronghold::print() const{
  cout<<"-Card's Name: "<<name<<endl;
  cout<<"-Starting Honour: "<<startingHonour<<endl;
  cout<<"-initialDefence: "<<initialDefence<<endl;
  cout<<"-Harvest Value: "<<harvestValue<<endl;
}


int Stronghold::get_startingHonour() const{
  return startingHonour;
}

int Stronghold::get_initialDefence() const{
  return initialDefence;
}
