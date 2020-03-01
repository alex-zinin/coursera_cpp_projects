#include "test_runner.h"
#include "profile.h"
#include<mutex>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <random>
#include<future>

using namespace std;



template <typename K, typename V>
class ConcurrentMap {
public:
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");
    mutex g_lock;
    struct Map
    {
        mutex m;
        map<K, V> thMap;
    };

    map<K, int> keys;
    vector<Map> maps;

    struct Access {
        //Access(V& ptr): ref_to_value(ptr) {}
        V &ref_to_value;
        unique_lock<mutex>&& lock;

    };


    explicit ConcurrentMap(size_t bucket_count): maps(bucket_count), num(bucket_count) {}

    Access operator[](const K& key)
    {
        g_lock.lock();
        int k = (key > 0 ? key : -key) % num;
        auto &value = maps[k];
        unique_lock l(value.m);
        g_lock.unlock();
        return {value.thMap[key], move(l)};
    }


    map<K, V> BuildOrdinaryMap()
    {
        vector<unique_lock<mutex>> v;
        for(auto& x: maps)
        {
            v.emplace_back(unique_lock(x.m));
        }
        map<K, V> result;
        for(auto& x: maps)
        {
            for(auto& y: x.thMap)
                result[y.first] = y.second;
        }
        return result;
    }


    int size, num;
};

void RunConcurrentUpdates(
        ConcurrentMap<int, int>& cm, size_t thread_count, int key_count
) {
    auto kernel = [&cm, key_count](int seed) {
        vector<int> updates(key_count);
        iota(begin(updates), end(updates), -key_count / 2);
        shuffle(begin(updates), end(updates), default_random_engine(seed));

        for (int i = 0; i < 2; ++i) {
            for (auto key : updates) {
                cm[key].ref_to_value++;
            }
        }
    };
//cout << "ok" << endl;
    vector<future<void>> futures;
    for (size_t i = 0; i < thread_count; ++i) {
        futures.push_back(async(kernel, i));
    }
}

void TestConcurrentUpdate() {
    const size_t thread_count = 3;
    const size_t key_count = 50;

    ConcurrentMap<int, int> cm(thread_count);
    RunConcurrentUpdates(cm, thread_count, key_count);

    const auto result = cm.BuildOrdinaryMap();
    ASSERT_EQUAL(result.size(), key_count);
    for (auto& [k, v] : result) {
        AssertEqual(v, 6, "Key = " + to_string(k));
    }
    //cout << "oks" << endl;
}

void TestReadAndWrite() {
    ConcurrentMap<size_t, string> cm(5);

    auto updater = [&cm] {
        for (size_t i = 0; i < 50000; ++i) {
            cm[i].ref_to_value += 'a';
        }
    };
    auto reader = [&cm] {
        vector<string> result(50000);
        for (size_t i = 0; i < result.size(); ++i) {
            result[i] = cm[i].ref_to_value;
        }
        return result;
    };

    auto u1 = async(updater);
    auto r1 = async(reader);
    auto u2 = async(updater);
    auto r2 = async(reader);

    u1.get();
    u2.get();

    for (auto f : {&r1, &r2}) {
        auto result = f->get();
        ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
            return s.empty() || s == "a" || s == "aa";
        }));
    }
}

void TestSpeedup() {
    {
        ConcurrentMap<int, int> single_lock(1);

        LOG_DURATION("Single lock");
        RunConcurrentUpdates(single_lock, 4, 50000);
    }
    {
        ConcurrentMap<int, int> many_locks(100);

        LOG_DURATION("100 locks");
        RunConcurrentUpdates(many_locks, 4, 50000);
    }
}
void Test_ConcurrentClass_Test()
{
    int thread_count = 10;
    ConcurrentMap<int, int> cm(thread_count);
    for(int i = 0; i < 10; i++)
        cm[i].ref_to_value = i;

    for(int i = 0; i < 10; i++)
        cm[i].ref_to_value++;



    ConcurrentMap<size_t, string> c(5);

    auto updater = [&c] {
        for (size_t i = 0; i < 50000; ++i) {
            c[i].ref_to_value += 'a';
        }
    };
    auto reader = [&c] {
        vector<string> result(50000);
        for (size_t i = 0; i < result.size(); ++i) {
            result[i] = c[i].ref_to_value;
        }
        return result;
    };

    for(int i = 0; i < 5; i++)
    {
        auto u1 = async(updater);
        auto r1 = async(reader);
    }
}
int main() {
    TestRunner tr;
    RUN_TEST(tr, Test_ConcurrentClass_Test);
    RUN_TEST(tr, TestConcurrentUpdate);
    RUN_TEST(tr, TestReadAndWrite);
    RUN_TEST(tr, TestSpeedup);
}