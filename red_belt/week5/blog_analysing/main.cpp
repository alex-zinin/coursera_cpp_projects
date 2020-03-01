#include "test_runner.h"
#include "profile.h"
#include<future>
#include <map>
#include <string>
#include<functional>
#include<mutex>
#include<utility>
#include<set>

using namespace std;


struct Stats {
public:
    Stats(): word_frequences(){}
    Stats(const map<string, int> &m): word_frequences(m){}
    map<string, int> word_frequences;

    void operator+=(const Stats& other)
    {
        for(auto it = other.word_frequences.begin(); it != other.word_frequences.end(); it++)
            word_frequences[it->first] = word_frequences[it->first] + it->second;
    }

    ~Stats()
    {
        word_frequences.clear();
    }


};




Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats stat;
    string word;
    stringstream input(line);
    while(!input.eof())
    {
        input >> word;
        if(key_words.find(word) != key_words.end())
        {
            stat.word_frequences[word]++;
        }
    }
    return stat;
}

Stats ExploreKeyWordsSingleThread(
         map<string, int>& key_words, istream& input
) {
    LOG_DURATION("Time3");
   //Stats result;
    //for(auto& x: key_words)
       // result.word_frequences[x] = 0;
    for (string line; getline(input, line,' ');) {
        //result += ExploreLine(key_words, line);
        auto it = key_words.find(line);
        if(it != key_words.end())
        {
            mutex m;
            {
                lock_guard<mutex> g(m);
             //   stat += f.get();
                (it->second)++;
            }

        }
    }
    //return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    LOG_DURATION("Time");
    Stats stat;
    for(auto& x: key_words)
        stat.word_frequences[x];
    if(key_words.empty())
        return stat;
    int size_buf = 8;
    int ncores = 4;
    //string s[size_buf];
    int size, sizel = 0;
    int i = 0;
    string str;//LOG_DURATION("Time3");
    stringstream ss[size_buf];
    while(getline(input, str))
    {
        size++;
        //s[i] = s[i] + " " + str;
        ss[i] << " " << move(str);
        i++;
        if(i >= ncores)
        {
            sizel = ncores;
            i = 0;
            size = 0;
        }
    }
    if(size <= sizel)
        size = sizel;
    LOG_DURATION("Time2");
    for(int i = 0; i < size; i++)
    {
        //stringstream ss(s[i]);
       // LOG_DURATION("Time4");
        future<Stats> f = async(ExploreKeyWordsSingleThread, ref(stat.word_frequences), ref(ss[i]));

    }
    for(auto& x: stat.word_frequences)
        if(x.second == 0)
            stat.word_frequences.erase(x.first);

    return stat;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
            {"yangle", 6},
            {"rocks", 2},
            {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}


void Test_Run_Time() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all", "best", "fdsfds","klw;fsa","lk;dss"};
   // LOG_DURATION("Time");
    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    for(int i = 0; i < 50000; i++)
    {
        ss << "10 reasons why yangle is the best IT company\n";
        ss << "yangle rocks others suck\n";
        ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
    }
   // LOG_DURATION("Time");
    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
            {"yangle", 6},
            {"rocks", 2},
            {"sucks", 1}
    };
   // ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
    RUN_TEST(tr, Test_Run_Time);
}