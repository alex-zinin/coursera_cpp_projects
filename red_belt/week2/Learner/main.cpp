#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include"ma.cpp"
#include<fstream>

using namespace std;

int main() {
    Learner learner;
    string line;
    //int p = 0;
    ifstream fp;
    fp.open("Lucas.txt");
    while (getline(cin, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }
        cout << learner.Learn(words) << "\n";
        //p = p + 1;
//        if(p > 10)
//            break;
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
        cout << word << "\n";
    }
}