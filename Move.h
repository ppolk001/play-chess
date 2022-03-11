//class declarations
#ifndef __MOVE_HEADER__
#define __MOVE_HEADER__

#include <string>
using namespace std;
//iterator

class Move {
  private:
    char ps[64];
    int indexFrom;
    int indexTo;

    /*helpers*/
    bool KnightReader(int, int, int);
    bool BishopReader(int, int, int);
  
  public:
    Move(char (&pieces)[64]);
    void UpdateMoveIt(char (&pieces)[64]);
    bool isLegalMove(string, int);
    int gridConvert(string);
    int getIndexFrom();
    int getIndexTo();

};
#endif
