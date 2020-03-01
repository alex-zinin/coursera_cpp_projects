#include<iostream>
#include <algorithm>
#include <string>
#include <vector>
#include"profile.h"
#include<set>

using namespace std;

//ostream& operator<<(ostream& os, vector<string> v)
//{
//    os << "{ ";
//    for(auto &x: v)
//    {
//        os << x << ", ";
//    }
//    os << "}";
//    return os;
//}


class Learner {
private:
    vector<string> dict;
    set<string> str;
public:
    int Learn(const vector<string>& words) {
        LOG_DURATION("exp:");
        int newWords = 0;
       // int sizeb = dict.size();
       vector<string> word = words;
       //cout << word << endl;
//        for(auto &x: word)
//        {//cout << "ччт";
//            if(dict.empty())
//            {//cout << "first";
//                dict.push_back(x);
//                newWords = newWords + 1;
//                continue;
//            }
//            if(find(dict.rbegin(), dict.rend(), x) == dict.rend())
//            {//cout << " wegsdfzd";
//                dict.push_back(x);
//                newWords = newWords + 1;
//            }
//        }
    for(auto &x: word)
        if(str.count(x) == 0)
        {
            str.insert(x);
            dict.push_back(x);
            newWords++;
        }
       // vector<string> word = words;
//        for(auto &x: words)
//        {
//            auto it = lower_bound(word.begin(), word.end(), x);
//            if(it == word.end())
//            {
//                word.push_back(x);
//                continue;
//            }
//            if(*it == x)
//                continue;
//            else
//                word.insert(it, x);
//        }
//        if(word.empty())
//            return 0;
        // sort(words.begin(), words.end());
      //   cout << "vector= " << word << endl;
       // cout << "base=" << dict << endl;
       // vector<string>::iterator itq = dict.begin();
//        auto itrb = dict.begin();
//        auto itre = dict.begin();
//        const string fword = *(word.begin());
//        const string lword = *word.rbegin();//cout << fword << " " << lword << endl;
//       if(dict.empty())
//            itrb = dict.begin();
//       else
      //      itrb = lower_bound(dict.begin(), dict.end(), fword);
//        if(dict.empty())
//            itre = itrb;
//        else
           // itre = lower_bound(itrb, dict.end(), lword);
    //    int steps = itre - itrb;
        //cout << steps << "=steps+" << word.size() << endl;
       // if(itre != dict.end())
       //     cout << *(itre);
      //  cout << dict << "=dict0" << endl;
      //  const auto itrp = dict.insert(itrb, word.begin(), word.end());
       // cout << *itrp;

        //cout << "itrp=" << *itrp << " " << "itre="   << endl;

           // sort(itrp, itrp+steps+word.size());
     //   sort(itrp, dict.end());
       // cout << dict << "=dict1" << endl;cout << *(itrp);
    //    auto last = unique(dict.begin(), dict.end());
        //cout << *last;
        //cout << dict << "=dict2" << endl;
    //    dict.erase(last, dict.end());

      //  int sizee = dict.size();
        //cout << *itrp;
       // auto iter = itre;
       // cout << *itrp << endl;

       // for(auto it = word.begin(); it < word.end(); it++) {
           // if(itq != dict.begin() && itq-1 != dict.begin() )
                //itq--;

          //  iter = dict.insert(iter, *it);
           // cout << "base=" << dict << endl;
            // it = itr;
           // if(itr != dict.end())
           // cout << *itr << "hey";
//

        //}
       // newWords = sizee-sizeb;
        return newWords;
    }

    vector<string>& KnownWords() {
        sort(dict.begin(), dict.end());
        dict.erase(unique(dict.begin(), dict.end()), dict.end());
        return dict;
    }
};