#include <bits/stdc++.h>
#include "print.h"
#include "word.h"
#include "game.h"

using namespace std;

void loadSavedGame()
{
    Game game(1);
    string continueAgain;
    while (game.startGame())
    {
        cout << "[0] - CONTINUE\n[1] - EXIT\n\nEnter Your choice:  ";
        cin >> continueAgain;
        while (continueAgain != "0" && continueAgain != "1")
        {
            cout << "Invalid option Enter Again:  ";
            cin >> continueAgain;
        }
        if (continueAgain == "1")
        {
            return;
        }
        game.resetGame();
    }
}

void newGame()
{
    string userName;
    cout << "Enter user Name:  ";
    cin >> userName;
    while (checkUserName(userName))
    {
        cout << "User name already Taken\nEnter Again:  ";
        cin >> userName;
    }
    Game game(userName);
    string continueAgain;
    while (game.startGame())
    {
        cout << "[0] - CONTINUE\n[1] - EXIT\n\nEnter Your choice:  ";
        cin >> continueAgain;
        while (continueAgain != "0" && continueAgain != "1")
        {
            cout << "Invalid option Enter Again:  ";
            cin >> continueAgain;
        }
        if (continueAgain == "1")
        {
            return;
        }
        game.resetGame();
    }
    // game.startGame();
}

int main()
{
    char gameOption;
    cout << "Welcome to the Game HANGMAN" << endl;
    printHangmanStatus(0);
    while (1)
    {
        cout << endl
             << "[0] - New Game\n[1] - Load Game\n[2] - Exit\nEnter Your choice:  ";
        cin >> gameOption;
        switch (gameOption)
        {
            case '0':
                newGame();
                break;
            case '1':
                loadSavedGame();
                break;
            case '2':
                break;
            default:
                break;
        }
        break;
    }
}