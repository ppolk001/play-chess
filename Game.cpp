//class definitions
#include <iostream>
#include <string>

using namespace std;

#include "Game.h"

Game::Game(int gameNumber) {
  for (int i = 0; i < 64; ++i) {
    if      (i == 0 || i == 7)   {pieces[i] = 'R';}
    else if (i == 1 || i == 6)   {pieces[i] = 'N';}
    else if (i == 2 || i == 5)   {pieces[i] = 'B';}
    else if (i == 3)             {pieces[i] = 'Q';}
    else if (i == 4)             {pieces[i] = 'K';}
    else if (i >= 8 && i <= 15)  {pieces[i] = 'P';}
      
    else if (i >= 16 && i <= 47) {pieces[i] = ' ';}
      
    else if (i >= 48 && i <= 55) {pieces[i] = 'p';}
    else if (i == 56 || i == 63) {pieces[i] = 'r';}
    else if (i == 57 || i == 62) {pieces[i] = 'n';}
    else if (i == 58 || i == 61) {pieces[i] = 'b';}
    else if (i == 59)            {pieces[i] = 'q';}
    else if (i == 60)            {pieces[i] = 'k';}
  }
  
  this->gameNum = gameNumber;
  cout << "=====================================\n";
  cout << "=------------Game started-----------=\n"; //3 then 33 so 18,19 is middle
  cout << "=====================================\n\n";
//cout << "1234567890123456789012345678901234567" << endl;
}
Game::~Game() {
  
}

void const Game::printGameNumber() {
  //      "       This is game 1... begin.     "
  cout << "       This is game " << gameNum << "... begin." << endl << endl;
  //cout << "   +---+---+---+---+---+---+---+---+\n";
  //cout << "   123456789012345678901234567890123" << endl;
}

void Game::Visualize() {
    int squares = 64;
    int row = 8;
    
    for (int i = 8; i > 0; --i) {
        row = squares / 8;
        cout << "   +---+---+---+---+---+---+---+---+\n";
        cout << " " << row << " |";
        for (int j = squares - 8; j <= squares - 1; ++j) {
          //if index is blank, print spaces
          if      (pieces[j] == ' ') {cout << "   ";}
          //if index is pawn, check color, print letter
          else if (pieces[j] == 'P') {cout << " P ";}
          else if (pieces[j] == 'p') {cout << " p ";}
          //if index is rook, check color, print letter  
          else if (pieces[j] == 'R') {cout << " R ";}
          else if (pieces[j] == 'r') {cout << " r ";}
          //if index is knight, check color, print letter  
          else if (pieces[j] == 'N') {cout << " N ";}
          else if (pieces[j] == 'n') {cout << " n ";}
          //if index is bishop, check color, print letter  
          else if (pieces[j] == 'B') {cout << " B ";}
          else if (pieces[j] == 'b') {cout << " b ";}
          //if index is queen, check color, print letter  
          else if (pieces[j] == 'Q') {cout << " Q ";}
          else if (pieces[j] == 'q') {cout << " q ";}
          //if index is king, check color, print letter  
          else if (pieces[j] == 'K') {cout << " K ";}
          else if (pieces[j] == 'k') {cout << " k ";}
      
          cout << "|";
        }
        cout << endl;
        squares -= 8;
    }
    cout << "   +---+---+---+---+---+---+---+---+\n";
    cout << "     a   b   c   d   e   f   g   h\n\n";
  }

void Game::Start() {
  //call the makeMoves function
  Game::MakeMoves();
}

/*PLAY THE GAME!*/
void Game::MakeMoves() {
  bool playGame = true;
  bool validMove = false;
  string myMove;
  int fromIndex, toIndex;
  int count = 0; //for testing until checkmate added
  
  Move *moveIt = new Move(pieces);

  while (playGame) {
    while (!validMove) { //while the valid move is false
      cout << "(notation: \"<col><row> to <col><row>\")" << endl << endl;
      cout << "        White's move:  ";
      getline(cin, myMove);
      cout << endl;
      //pass to iterator the move and the array and return true or false
      validMove = moveIt->isLegalMove(myMove, 0); //0 means its whites turn
      //validMove = true; //test bool
      if (validMove) {
        //change indexes to represent the new move
        fromIndex = moveIt->getIndexFrom();
        toIndex = moveIt->getIndexTo();
        // cout << "indexF: " << fromIndex << ", indexT: " << toIndex << endl;
        pieces[toIndex] = pieces[fromIndex];
        pieces[fromIndex] = ' ';
        moveIt->UpdateMoveIt(pieces); //update the iterator to move thru updated position
      }
      else if (!validMove) {
        cout << "            Illegal Move!" << endl << endl;
      }
    }
    Game::Visualize();
    //pass array to iterator to check if checkmake
    //if is checkmate
      //set playGame to false
    //else if is not checkmate
      validMove = false;
      while (!validMove) { //since no checkmate, ask black for a move
        cout << "(notation: \"<col><row> to <col><row>\")" << endl << endl;
        cout << "        Black's move:  ";
        getline(cin, myMove);
        cout << endl;
        //pass to visitor/iterator the move and the array and return true or false
        validMove = moveIt->isLegalMove(myMove, 1); //0 means its whites turn
        //validMove = true; //test bool
        if (validMove) {
          //change indexes to represent the new move
        fromIndex = moveIt->getIndexFrom();
        toIndex = moveIt->getIndexTo();
        // cout << "indexF: " << fromIndex << ", indexT: " << toIndex << endl;
        pieces[toIndex] = pieces[fromIndex];
        pieces[fromIndex] = ' ';
          moveIt->UpdateMoveIt(pieces); //update the iterator to move thru updated position
        }
        else if (!validMove) {
          cout << "            ILLEGAL MOVE!" << endl << endl;
        }
      }
      validMove = false;
      Game::Visualize();
      //pass array to iterator to check if checkmake
      //if is checkmate
      //set playGame to false

      //while checkmate is not implemented
      count += 1;
      if (count == 2) {
        playGame = false;
      }
  }  
  //delete moveIt; //delete at the end of all moves
}
  
