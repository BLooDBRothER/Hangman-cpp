#include <bits/stdc++.h>
#include "print.h"
#include "word.h"
#include "game.h"

using namespace std;

void loadGame(){
    Game game("_", false);
}

void newGame(){
    string userName;
    cout << "Enter user Name:  ";
    cin >> userName;
    while(checkUserName(userName+".txt")){
        cout << "xxxx USER NAME ALREADY TAKEN XXXX" << endl;
        cout << "Enter user Name:  ";
        cin >> userName;
    }
    Game game(userName, true);
}

int main(){
    int gameOption;
    cout << "Welcome to the Game HANGMAN" << endl;
    printStatus(0);
    cout << endl << "[1] - New Game\n[2] - Load Game\nEnter Your choice:  ";
    cin >> gameOption;
    switch (gameOption)
    {
    case 1:
        newGame();
        break;
    case 2:
        loadGame();
        break;
    default:
        break;
    }
}