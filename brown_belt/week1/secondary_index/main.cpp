#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include<string>
#include<tuple>

using namespace std;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};


class Database {
public:
    bool Put(const Record& record)
    {
        auto idr = record.id;
        if(database.find(idr) == database.end())
        {
            auto it = database.insert(make_pair(idr, record)).first;
            auto itt = timestampbase.insert(make_pair(record.timestamp,it));
            auto itk = karma.insert(make_pair(record.karma,it));
            auto itu = user.insert(make_pair(record.user,it));
            base_iterators[record.id] = make_tuple(itt, itk, itu);
            return true;
        }
        else
            return false;
    }

    const Record* GetById(const string& id) const
    {
        auto it = database.find(id);
        if(it != database.end())
            return &(it->second);
        else
            return nullptr;
    }


    bool Erase(const string& id)
    {
        auto it = database.find(id);
        if(it != database.end())
        {
            auto tupl = base_iterators.at(id);
            auto itt = get<0>(tupl);
            auto itk = get<1>(tupl);
            auto itu = get<2>(tupl);
            timestampbase.erase(itt);
            user.erase(itu);
            karma.erase(itk);
            database.erase(it);
            return true;
        }
        else
            return false;

    }

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const
    {
        auto it = timestampbase.lower_bound(low);
        auto ite = timestampbase.upper_bound(high);
        auto val = high;
        bool flag = false;
        while(it != timestampbase.end())// && callback(it->second->second) == true)
        {
            if(it == ite)
                flag = true;
            if((it->second)->second.timestamp != val && flag)
            {
                break;
            }

            if(callback(it->second->second) != true)
                break;
            it++;

        }

    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const
    {
        auto it = karma.lower_bound(low);
        auto ite = karma.upper_bound(high);
        auto val = high;
        bool flag = false;
        while(it != karma.end())
        {
            if(it == ite)
                flag = true;
            if((it->second)->second.karma != val && flag)
            {
                break;
            }
            if(callback(it->second->second) != true)
                break;
            it++;
        }
    }

    template <typename Callback>
    void AllByUser(const string& users, Callback callback) const
    {
        auto it = user.find(users);
        if(it != user.end())
        while(it->second->second.user == users)
        {
            if(callback(it->second->second) != true)
                break;
            it++;
            if(it == user.end())
                break;
        }
    }

public:
    map<string, Record> database;
    multimap<int, map<string, Record>::iterator> timestampbase;
    multimap<int, map<string, Record>::iterator> karma;
    multimap<string, map<string, Record>::iterator> user;
    unordered_map<string, tuple<
            multimap<int, map<string, Record>::iterator>::iterator,
            multimap<int, map<string, Record>::iterator>::iterator,
            multimap<string, map<string, Record>::iterator>::iterator>> base_iterators;
};

void TestRangeBoundaries() {
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});
    db.Put({"id3", "O>>-<", "general2", 1536107260, 10000});

    int count = 0;
    db.RangeByKarma(bad_karma-1, good_karma+1, [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestRangeTime() {
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id0", "Hello there", "master", 1536107228, 10});
    db.Put({"id1", "Hello there", "master", 1536107230, 10});
    db.Put({"id2", "O>>-<", "general2", 1536107260, 10});
    db.Put({"id3", "O>>-<", "general2", 1536107279, 101});

    int count = 0;
    db.RangeByTimestamp(1536107229, 1536107261, [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}


void TestSameUser() {
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

    int count = 0;
    db.AllByUser("master", [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestReplacement() {
    const string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    auto stat = db.Erase("id");
    stat = db.Put({"id", final_body, "not-master", 1536107260, -10});
    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    RUN_TEST(tr, TestRangeTime);
    return 0;
}