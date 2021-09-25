#include <bits/stdc++.h>

using namespace std;

bool checkUserName(string name){
    fstream file(name);
    return file.is_open() ? true : false;
}
class GameData{
    private:
        int seed;
        string userName;
        fstream userFile;
        selectWords words;
    public:
        int life;
        string gameWord, encryptedWord;
        vector<char> wrongGuess, correctGuess;
        GameData(){
            loadGame();
        }
        GameData(string fileName){
            userName = fileName;
            updateUserList(fileName);
            newGame();
        }

        void newGame(){
                userFile.open(userName+".txt", ios::trunc | ios::in | ios::out);
                seed = time(0);
                userFile << "word: " + to_string(seed);
                userFile.close();
                wrongGuess.clear();
                correctGuess.clear();
                initGame(words.getWord(seed), 8);
        }

        void loadGame(){
            // Read and Display user List
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

            // Load the selected game data
            userName = user[option];
            userFile.open(user[option]+".txt", ios::in | ios::out);

            // Get the word
            userFile.seekg(6, ios::beg);
            string seed;
            getline(userFile, seed);
            this->seed = stoi(seed);

            // Get the Life
            userFile.seekg(6, ios::cur);
            string life;
            getline(userFile, life);

            // Get the wrong Guess
            userFile.seekg(7, ios::cur);
            string wrGuess;
            getline(userFile, wrGuess);
            for(auto i: wrGuess){
                if(i == ' ' || i == '\n'){
                    continue;
                }
                else{
                    wrongGuess.push_back(i);
                }
            }
            initGame(words.getWord(this->seed), stoi(life));

            // Update Encrypted test
            userFile.seekg(9, ios::cur);
            string crtGuess;
            getline(userFile, crtGuess);
            for(auto i: crtGuess){
                for(int j=0; j<gameWord.size(); j++){
                    if(gameWord[j] == i){
                        encryptedWord[j] = i;
                    }
                }
            }
            userFile.close();
        }

        void initGame(string gameWord, int life){
            transform(gameWord.begin(), gameWord.end(), gameWord.begin(), ::tolower);
            this->gameWord = gameWord;
            this->life = life;
            encryptedWord = string(gameWord.size(), '*');
        }

        void saveGame(){
            cout << "Saving .......";
            userFile.open(userName+".txt", ios::trunc | ios::in | ios::out);
            userFile << "seed: " + to_string(seed) << "\n";
            userFile << "life: " + to_string(life) << "\n";
            string wrGuess = "wrong: ";
            for(auto i : wrongGuess){
                wrGuess = wrGuess + i + ' ';
            }
            cout << wrGuess << endl;
            userFile << wrGuess << "\n";
            string crtGuess = "correct: ";
            for(auto i : correctGuess){
                crtGuess = crtGuess + i + ' ';
            }
            cout << crtGuess << endl;
            userFile << crtGuess << "\n";
            userFile.close();
            cout << "Completed" << endl;
        }

        void printStatus(){
            cout << "____________________________________________________________________" << endl;
            printHangmanStatus(life-1);
            cout << "Word:  " << encryptedWord << endl;
            printWrongGuess();
            cout << "Life:  " << life-1 << endl;
        }

        void printWrongGuess(){
            cout << "Previously Guessed words:  ";
            for(auto i: wrongGuess){
                cout << i << " ";
            }
            cout << endl;
        }

        void printLost(){
            printStatus();
            cout << "YOU RAN OUT OF LIFE" << endl;
            cout << "Word to save him/her from hanging is:  " << gameWord << endl;
            cout << "Better Luck Next Time" << endl;
            cout << "____________________________________________________________________" << endl;
        }
        void printWon(){
            printStatus();
            cout << "Hooray!!!!!!! You saved him/her from hanging" << endl;
            cout << "You took " << (8 - life) << " chance to save him/her" << endl;
            cout << "____________________________________________________________________" << endl;
        }

        void updateUserList(string name){
            fstream file("userList.txt", ios::app);
            file << name << "\n";
            file.close();
        }
};
class Game : protected GameData{
    public:
        Game(int load):GameData(){}
        Game(string fileName):GameData(fileName){}

        void resetGame(){
            newGame();
        }

        bool startGame(){
            cout << gameWord << endl;
            string guessInput;
            bool pass;
            while(life!=1){
                pass = false;
                printStatus();
                cout << "Enter the Guessed character [EXIT - TO EXIT THE GAME]:  ";
                cin >> guessInput;
                while(guessInput.size() > 1){
                    if(guessInput == "exit"){
                        return false;
                    }
                    cout << "Invalid Input Enter Again:  ";
                    cin >> guessInput;
                }
                while( 
                    (find(correctGuess.begin(), correctGuess.end(), guessInput[0]) != correctGuess.end()) 
                    || (find(wrongGuess.begin(), wrongGuess.end(), guessInput[0]) != wrongGuess.end())
                ){
                    cout << endl << "This Character You Guessed Already\nEnter Again:  ";
                    cin >> guessInput;
                }
                while(guessInput.size() > 1){
                    if(guessInput == "exit"){
                        return false;
                    }
                    cout << "Invalid Input Enter Again:  ";
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
                    printWon();
                    return true;
                }
                if(!pass){
                    wrongGuess.push_back(guessInput[0]);
                    life--;
                }
                saveGame();
            }
            printLost();
            return true;
        }
};