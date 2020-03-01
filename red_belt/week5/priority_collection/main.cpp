#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include<map>


using namespace std;


template <typename T>
class PriorityCollection {
public:
    using Priority = int;
    using Id = int;/* тип, используемый для идентификаторов */;
   // PriorityCollection(): current(0){}
    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object)
    {
        data[current] = make_pair(0, move(object));
        ptr[0].insert(current);
        current++;
        return current - 1;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin)
    {
        auto itr = ids_begin;
        for(auto it = make_move_iterator(range_begin); it != make_move_iterator(range_end); it++)
        {
            *itr = Add(move(*it));
            itr++;
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const
    {
        auto it = data.find(id);
        return it != data.end();
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const
    {
        return data.at(id).second;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id)
    {
        auto priority = data[id].first;
        data[id].first++;
        (ptr[priority]).erase(id);
        if(ptr.at(priority).empty())
            ptr.erase(priority);
        ptr[priority + 1].insert(id);
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const
    {
        auto idval = *ptr.rbegin();
        int pr = idval.first;
        return {data.at(*(idval.second).rbegin()).second, pr};

    }
    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax()
    {
        auto idval = *ptr.rbegin(); // пара с сетом с максимальным приоритетом
        int pr = idval.first;    // макс приоритет
        int idv = *(idval.second).rbegin(); // id последнего с макс приоритетом
      //  cout << idv << endl;
      //  cout << data << endl;
        ((*ptr.rbegin()).second).erase(idv);
        if((*ptr.rbegin()).second.empty())
            ptr.erase(pr);
        auto obj = move(data.at(idv).second);
        data.erase(idv);
        return {move(obj), pr};
    }

private:
    map<Id, pair<Priority,T>> data;
    Id current;
    map<Priority, set<Id>> ptr;
    // Приватные поля и методы
};


class StringNonCopyable : public string {
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");
   // cout << strings.data << endl;
   // cout << strings.ptr << endl;
    strings.GetMax();
    strings.IsValid(0);
    strings.Get(0);
    vector<StringNonCopyable> v;
    vector<int> i(100);
    strings.Add(v.begin(), v.end(), i.begin());
    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
      //  cout <<"ptr:" <<  strings.ptr  << endl << "data: " << strings.data << "@@" << endl;

        // cout << strings.data << endl;
        //cout << strings.data  << item.first  << "@@" << endl;
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
        //cout << strings.ptr  << item.first  << "@@" << endl;

    }
    {     //   cout << strings.data  << "@@" << endl;

    const auto item = strings.PopMax();
       // cout <<"ptr:" <<  strings.ptr  << endl << "data: " << strings.data << "@@" << endl;

        //cout << strings.data  << item.second  << "@@" << endl;
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        //cout <<"ptr:" <<  strings.ptr  << endl << "data: " << strings.data << "@@" << endl;

        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}