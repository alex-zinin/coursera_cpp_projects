
#include <iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

vector<string> SplitIntoWords(const string& s)
{
    vector<char> word;
    vector<string> words;
    for(int i = 0; i < s.size(); i++)
        word.push_back(s[i]);
    
    string str;
    for(auto it = begin(word); it!= end(word); it = find(next(it), end(word), ' '))
    {
        if(it == begin(word))
            str.assign(it, find(next(it), end(word), ' '));
        else
            str.assign(next(it), find(next(it), end(word), ' '));
       
        words.push_back(str);
        
    }


    return(words);
}
