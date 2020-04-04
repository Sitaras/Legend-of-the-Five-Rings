#include "Gameboard.hpp"

using namespace std;

extern const unsigned int MAXPLAYERS;

int main(){

  int num;

  cout<<endl << ">Insert number of players: ";
  while(!(cin >> num) || (num < 2 || (unsigned) num > MAXPLAYERS)){ /* max 8 players */
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please, try again: ";
  }

  GameBoard l5r(num);

  l5r.initializeGameBoard();
  l5r.printGameStatistics();


  l5r.gameplay();

  return 0;
}
