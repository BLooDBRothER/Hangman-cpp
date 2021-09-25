#include <bits/stdc++.h>
#include "word.h"

using namespace std;

bool checkUserName(string name){
    fstream file(name);
    return file.is_open() ? true : false;
}