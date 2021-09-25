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
        string gameWord;
        GameData(string fileName, bool newGame){
            if(newGame){
                updateUserList(fileName);
                userFile.open(fileName+".txt", ios::trunc | ios::in | ios::out);
                int seed = time(0);
                userFile << "word: " + to_string(seed);
                initGame(seed);
            }
            else{
                loadGame();
            }
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
            initGame(stoi(seed));
        }

        void initGame(int seed){
            gameWord = words.getWord(seed);
        }

        void updateUserList(string name){
            fstream file("userList.txt", ios::app);
            file << name << "\n";
            file.close();
        }
};
class Game : protected GameData{
    public:
        string encryptedWord;
        Game(string fileName, bool newGame):GameData(fileName, newGame){
            cout << gameWord;
            encryptedWord = string(89, '*');
            cout << gameWord << " " <<  encryptedWord ;
        }
};