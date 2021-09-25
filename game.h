#include <bits/stdc++.h>
// #include "word.h"

using namespace std;

bool checkUserName(string name){
    fstream file(name);
    return file.is_open() ? true : false;
}
class GameData{
    private:
        fstream userFile;
        selectWords words;
    public:
        int life;
        string gameWord, encryptedWord;
        vector<char> wrongGuess, correctGuess;
        GameData(string fileName, bool gameType){
            if(gameType){
                updateUserList(fileName);
                newGame(fileName);
            }
            else{
                loadGame();
            }
        }

        void newGame(string fileName){
                userFile.open(fileName+".txt", ios::trunc | ios::in | ios::out);
                int seed = time(0);
                userFile << "word: " + to_string(seed);
                userFile.close();
                initGame(words.getWord(seed), 8);
        }

        void loadGame(){
            fstream file("userList.txt", ios::in);
            vector<string> user;
            string dummy;
            for(int i=0; getline(file, dummy); i++){
                cout << "[ " + to_string(i) + " ] " + dummy << endl;
                user.push_back(dummy);
            }
            file.close();
            int option;
            cout << "Select the Game to Load:  ";
            cin >> option;
            while(option >= user.size()){
                cout << "xxxx INVALID CHOICE xxxx\n";
                cout << "Select the Game to Load:  ";
                cin >> option;
            }
            userFile.open(user[option]+".txt", ios::in | ios::out);
            userFile.seekg(6, ios::beg);
            string seed;
            getline(userFile, seed);
            
            initGame(words.getWord(stoi(seed)), 8);
        }

        void initGame(string gameWord, int life){
            this->gameWord = gameWord;
            this->life = life;
            encryptedWord = string(gameWord.size(), '*');
        }

        void printStatus(){
            cout << "____________________________________________________________________" << endl;
            printHangmanStatus(life-1);
            cout << "Word:  " << encryptedWord << endl;
            printWrongGuess();
            cout << "Enter the Guessed character [EXIT - TO EXIT THE GAME]:  ";
        }

        void printWrongGuess(){
            for(auto i: wrongGuess){
                cout << i << " ";
            }
            cout << endl;
        }

        void updateUserList(string name){
            fstream file("userList.txt", ios::app);
            file << name << "\n";
            file.close();
        }
};
class Game : protected GameData{
    public:
        Game(string fileName, bool gameType):GameData(fileName, gameType){
            cout << gameWord << endl;
        }

        void startGame(){
            string guessInput;
            bool pass;
            while(life!=1){
                pass = false;
                printStatus();
                cin >> guessInput;
                if(guessInput == "exit"){}
                auto it = find(correctGuess.begin(), correctGuess.end(), guessInput[0]); 
                while( 
                    (find(correctGuess.begin(), correctGuess.end(), guessInput[0]) != correctGuess.end()) 
                    || (find(wrongGuess.begin(), wrongGuess.end(), guessInput[0]) != wrongGuess.end())
                ){
                    cout << endl << "This Character You Guessed Already\nEnter Again:  ";
                    cin >> guessInput;
                }
                for(int chridx = 0; chridx < gameWord.size(); chridx++){
                    if(guessInput[0] == gameWord[chridx]){
                        encryptedWord[chridx] = guessInput[0];
                        correctGuess.push_back(guessInput[0]);
                        pass = true;
                    }
                }
                if(encryptedWord == gameWord){
                    cout << "Success";
                    return;
                }
                if(!pass){
                    wrongGuess.push_back(guessInput[0]);
                    life--;
                }
            }
        }
};