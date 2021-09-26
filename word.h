#include <bits/stdc++.h>

using namespace std;

class selectWords{
    private:
        vector<string> words;
    public:
        selectWords(){
            fstream wordFile("./game_data/words.txt");
            string word;
            while(getline(wordFile, word)){
                words.push_back(word);
            }
            wordFile.close();
        }
        string getWord(int seed){
            srand(seed);
            return words[rand()%words.size()];
        }
};