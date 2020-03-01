#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;



template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if(range_end - range_begin < 2)
        return;
    int size = (range_end-range_begin)/3;
    vector<typename RandomIt::value_type> vect1;
    for(auto it = range_begin; it < range_begin + size; it++)
        vect1.push_back(move(*it));
    vector<typename RandomIt::value_type> vect2;
    for(auto it = range_begin + size; it < range_begin + 2*size; it++)
        vect2.push_back(move(*it));
    vector<typename RandomIt::value_type> vect3;
    for(auto it = range_begin + size*2; it < range_end; it++)
        vect3.push_back(move(*it));
    MergeSort(vect1.begin(), vect1.end());
    MergeSort(vect2.begin(), vect2.end());
    MergeSort(vect3.begin(), vect3.end());
    vector<typename RandomIt::value_type> vect;
    merge(make_move_iterator(vect1.begin()), make_move_iterator(vect1.end()), make_move_iterator(vect2.begin()), make_move_iterator(vect2.end()), back_inserter(vect));
    merge(make_move_iterator(vect.begin()), make_move_iterator(vect.end()), make_move_iterator(vect3.begin()), make_move_iterator(vect3.end()), range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
   // vector<NoncopyableInt> v(10);
    //MergeSort(v.begin(), v.end());
    return 0;
}