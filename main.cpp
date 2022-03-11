#include <iostream>
using namespace std;

/*for the chess engine, use piece objects that get the ID and then the 
  color to determine what peice it is and what color that piece is*/
#include "Game.h"
//#include "Piece.h"
//#include "Visualization.h"

int main() {    
  Game game1(1);
  game1.printGameNumber();
  game1.Visualize();
  game1.Start();
    
  return 0;
}
