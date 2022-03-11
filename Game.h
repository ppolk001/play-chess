//class declarations 
#ifndef __GAME_HEADER__
#define __GAME_HEADER__

#include <iostream>
using namespace std;

#include "Move.h"

class Game {
  private:
    int gameNum;
    
  public:
    Game(int);
    ~Game();
    void const printGameNumber();
    void Visualize();
    void Start();
    void MakeMoves();

    char pieces[64];
};
#endif
