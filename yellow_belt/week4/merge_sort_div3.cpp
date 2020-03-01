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
    if(range_end-range_begin < 3)
    {

    }
    else{
        RandomIt it = range_begin+(range_end-range_begin)/3;
        vector<typename RandomIt::value_type> vect1(range_begin, it);
        RandomIt it2 = it+(range_end-it)/2;
        vector<typename RandomIt::value_type> vect2(it,it2);
        vector<typename RandomIt::value_type> vect3(it2, range_end);
        MergeSort(begin(vect1), end(vect1));
        MergeSort(begin(vect2), end(vect2));
        MergeSort(begin(vect3), end(vect3));
        vector<typename RandomIt::value_type> vect;
        merge(begin(vect1), end(vect1), begin(vect2), end(vect2),back_inserter(vect));
        merge(begin(vect), end(vect), begin(vect3), end(vect3), range_begin);
    }


}
