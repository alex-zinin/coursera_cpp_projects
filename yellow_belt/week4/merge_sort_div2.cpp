#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


//ostream& operator<<(ostream& stream, vector<int> v)
//{
//    stream << "{";
//    for(int i = 0; i < v.size(); i++)
//    {
//
//        stream << v[i] << " ";
//    }
//    stream << "}";
//    return stream;
//
//}
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);


template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if(range_end-range_begin < 2)
    {

    }
    else{
        RandomIt it = range_begin+(range_end-range_begin)/2;
        vector<typename RandomIt::value_type> vect1(range_begin, it);
        vector<typename RandomIt::value_type> vect2(it, range_end);
        MergeSort(begin(vect1), end(vect1));
        MergeSort(begin(vect2), end(vect2));
        merge(begin(vect1), end(vect1), begin(vect2), end(vect2),range_begin);
    }


}
