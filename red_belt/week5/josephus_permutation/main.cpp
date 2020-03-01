#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include<utility>
#include<list>
#include<deque>

using namespace std;

template <typename RandomIt>
RandomIt Move_Iterator(RandomIt first, RandomIt last, RandomIt it, uint32_t step_size)
{
    auto itr = it;
    if(it + step_size >= last)
        itr = Move_Iterator(first, last, first, step_size - (last - itr));
    else
        itr = itr + step_size;
    return itr;
}

template <typename RandomIt>
RandomIt Move_Iterator_List(RandomIt first, RandomIt last, RandomIt itr, uint32_t step_size)
{
    auto it = itr;
    for(int i = 0; i < step_size; i++)
    {
        it++;
        if(it == last)
            it = first;
    }
    return it;
}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
//    for(auto it = first; it <= last; it++)
//        move(it);
    list<typename RandomIt::value_type> pool;

//    for(auto it = first; it < last; it++)
//        pool.push_back(move(*it));
    // vector<typename RandomIt::value_type> pool;
    //  (first, last);
    for(auto it = first; it < last; it++)
    {
        pool.push_back(move(*it));
    }
    size_t cur_pos = 0;
    //cout << "n" << step_size << endl;
    auto it = pool.begin();
    while (!pool.empty()) {
        //auto itr = Move_Iterator_List(it, pool.end(), step_size);
        *(first++) = move(*it);
        it = pool.erase(it);
        if (pool.empty()) {
            break;
        }

        //cout << *it << endl;
        if(it == pool.end())
            it = pool.begin();
       // cout << "after erase:" << *it <<  endl;
        it =  Move_Iterator_List(pool.begin(), pool.end(), it, step_size - 1);
       // cout << *it << endl;
        if (pool.empty()) {
            break;
        }
        cur_pos = (cur_pos + step_size - 1) % pool.size();
    }
//    auto itb = pool.begin() + 1;
//    for(auto it = pool.begin();; )
//    {
//        if(itb == pool.end())
//            break;
//        if(it + step_size < pool.end())
//            it = it + step_size;
//        else
//            it = itb + step_size - (pool.end() - it);
//        itb = 1 + pool.insert(itb, move(*it));
//        it = pool.erase(it);
//        if(itb == pool.end())
//            break;
//        if(it + step_size - 1 < pool.end())
//            it = it + step_size;
//        else
//            it = itb + step_size -1 - (pool.end() - it);
//        itb = 1 + pool.insert(itb, move(*it));
//        it = pool.erase(it);
//        //itb++;
//        if(itb == pool.end())
//            break;
//    }
//    for(auto& x: pool)
//        *(first++) = move(x);

}

vector<int> MakeTestVector() {
    vector<int> numbers(10);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector() {
    const vector<int> numbers = MakeTestVector();
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
    }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt {
    int value;

    NoncopyableInt(const NoncopyableInt&) = delete;
    NoncopyableInt& operator=(const NoncopyableInt&) = delete;

    NoncopyableInt(NoncopyableInt&&) = default;
    NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
    return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
    return os << v.value;
}

void TestAvoidsCopying() {
    vector<NoncopyableInt> numbers;
    numbers.push_back({1});
    numbers.push_back({2});
    numbers.push_back({3});
    numbers.push_back({4});
    numbers.push_back({5});

    MakeJosephusPermutation(begin(numbers), end(numbers), 2);

    vector<NoncopyableInt> expected;
    expected.push_back({1});
    expected.push_back({3});
    expected.push_back({5});
    expected.push_back({4});
    expected.push_back({2});

    ASSERT_EQUAL(numbers, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    return 0;
}