//class definitions
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Move.h"

Move::Move(char (&pieces)[64]) {
  for (int i = 0; i < 64; ++i) {
    ps[i] = pieces[i];
  }
  indexFrom = -1;
  indexTo = -1;
}

void Move::UpdateMoveIt(char (&pieces)[64]) {
  for (int i = 0; i < 64; ++i) {
    ps[i] = pieces[i];
  }  
}

bool Move::isLegalMove(string s, int moveColor) {
  bool legal = false;
  string checkS = "";
  int indexFrom, indexTo;
  char charFrom, charTo;
  
  //cout << "...still validating: " << s << endl;
  /*conversion step*/
  for (int i = 0; i < 2; ++i) {checkS += s[i];}
  indexFrom = Move::gridConvert(checkS);
  checkS = "";
  for (int i = s.size() - 2; i < s.size(); ++i) {checkS += s[i];}
  indexTo = Move::gridConvert(checkS);
  /*conversion step*/

  this->indexFrom = indexFrom;
  this->indexTo = indexTo;
  
  /*check legal move step*/ //using indexFrom and indexTo
  //cout << "moving from index: " << indexFrom;
  //cout << " to index: " << indexTo << endl;

  charFrom = ps[indexFrom];
  charTo = ps[indexTo];
  //cout << "charFrom: " << charFrom << " and charTo: " << charTo << endl;


  if (charFrom == 'N' || charFrom == 'n') {
    legal = Move::KnightReader(indexFrom, indexTo, moveColor);
  }
  else if (charFrom == 'B' || charFrom == 'b') {
    legal = Move::BishopReader(indexFrom, indexTo, moveColor);
  }

  
  return legal;
}

//have it store the move as an int to be grabbed by the Game class
int Move::gridConvert(string s) { //takes in two char string (ex: a1) as column and row
  int col = -1;
  int row = -1;
  int index = -1;
  //column
       if (s[0] == 'a') {col = 0;}
  else if (s[0] == 'b') {col = 1;}
  else if (s[0] == 'c') {col = 2;}
  else if (s[0] == 'd') {col = 3;}
  else if (s[0] == 'e') {col = 4;}
  else if (s[0] == 'f') {col = 5;}
  else if (s[0] == 'g') {col = 6;}
  else if (s[0] == 'h') {col = 7;}
  //row
       if (s[1] == '1') {row = 0;}
  else if (s[1] == '2') {row = 1;}
  else if (s[1] == '3') {row = 2;}
  else if (s[1] == '4') {row = 3;}
  else if (s[1] == '5') {row = 4;}
  else if (s[1] == '6') {row = 5;}
  else if (s[1] == '7') {row = 6;}
  else if (s[1] == '8') {row = 7;}  

  index = (row * 8) + col;
  
  return index;
}

int Move::getIndexFrom() {
  return indexFrom;
}
int Move::getIndexTo() {
  return indexTo;
}




/*TESTS IF MOVING THE KNIGHT IS LEGAL - RETURNS A BOOL*/
bool Move::KnightReader(int iFrom, int iTo, int color) {
  bool theMove = false;
  vector<int> canMove;

  canMove.push_back(iFrom + 15);
  canMove.push_back(iFrom + 17);
  canMove.push_back(iFrom + 6);
  canMove.push_back(iFrom + 10);
  canMove.push_back(iFrom - 6);
  canMove.push_back(iFrom - 10);
  canMove.push_back(iFrom - 15);
  canMove.push_back(iFrom - 17);

  // cout << "index piece being moved to: " << iTo << endl;
  // cout << "possible indeces to move to: ";
  // for (unsigned int i = 0; i < canMove.size(); ++i) {
  //   cout << canMove.at(i) << ", ";
  // } 
  //cout << endl;
  /*check if the square the knight is moving to is legal*/
  for (int i = 0; i < canMove.size(); ++i) {
    if (canMove.at(i) == iTo) {
      // cout << "The knight can move to a valid square" << endl;
      /*check if the iTo square is an opposite color piece*/
      if (color == 0) {
        //if space
        if (ps[iTo] == ' ') {theMove = true;}
        //if black piece is being taken by white knight
        else if (ps[iTo] >= 'a') {theMove = true;}
      }
      else if (color == 1) {
        //if space
        if (ps[iTo] == ' ') {theMove = true;}
        //if white piece is being taken by black knight
        else if (ps[iTo] <= 'Z') {theMove = true;}    
      }
    }
  }

  return theMove;
}

/*TESTS IF MOVING THE BISHOP IS LEGAL - RETURNS A BOOL*/
bool Move::BishopReader(int iFrom, int iTo, int color) {
  bool theMove = false;
  int diagonal;
  bool notBlocked;
  vector<int> canMove;
  
  /*create a vector of possible moves (and takes)*/
  /*checking four possible diagonal directions of movement*/
  for (int i = 0; i < 4; ++i) {
    diagonal = iFrom;
    notBlocked = true;
    /*for that direction specified by i*/
    for (int j = 0; j < 7; ++j) {
      if (notBlocked) {  
        if (diagonal % 8 != 0 && (diagonal + 1) % 8 != 0) {
          if      (i == 0) {diagonal = diagonal + 7;}
          else if (i == 1) {diagonal = diagonal + 9;}
          else if (i == 2) {diagonal = diagonal - 9;}
          else if (i == 3) {diagonal = diagonal - 7;}
    
          if (diagonal >= 0 && diagonal <= 63) {
            //white
            if (color == 0) {
              //if space
              if (ps[diagonal] == ' ') {canMove.push_back(diagonal);}
              //if white piece is not being taken by white bishop
              else if (ps[diagonal] >= 'a') {
                canMove.push_back(diagonal);
                notBlocked = false; //found an enemy piece
              }
              else if (ps[diagonal] <= 'Z') {
                notBlocked = false; //if bishop is blocked by its own color        
              }              
            }
            //black
            else if (color == 1) {
              //if space
              if (ps[diagonal] == ' ') {canMove.push_back(diagonal);}
              //if black piece is not being taken by black bishop
              else if (ps[diagonal] <= 'Z') {
                canMove.push_back(diagonal);
                notBlocked = false; //found an enemy piece
              }
              else if (ps[diagonal] >= 'a') {
                notBlocked = false; //if bishop is blocked by its own color            
              }
            }
          }
        }
      }
    }
  }
  // cout << "index piece being moved from: " << iFrom << endl;
  // cout << "index piece being moved to: " << iTo << endl;
  // cout << "possible indeces to move to: ";
  for (unsigned int i = 0; i < canMove.size(); ++i) {
    // cout << canMove.at(i) << ", ";
    if (iTo == canMove.at(i)) {
      theMove = true;
    }
  } 
  // cout << endl;

    
  return theMove;
}


