#include <iomanip>
#include <iostream>
#include<algorithm>
#include <vector>
#include <utility>
#include<set>
#include<map>

//#include "profile.h"
using namespace std;

//ostream& operator<<(ostream& os, vector<int> v)
//{
//    for(auto &x: v)
//    {
//
//        os << x << " ";
//    }
//    return os;
//}
//bool operator<(const std::pair<const int, int> lhs, const std::pair<int, int> rhs)
//{
//    return lhs.second < rhs.second;
//}

class ReadingManager {
public:
    ReadingManager()
            : pages(MAX_USER_COUNT_+1, -1),
            user_page_counts_(MAX_USER_COUNT_ + 1, 0),
              sorted_users_(),
              userids(),
              user_positions_(MAX_USER_COUNT_ + 1, -1),
              pagesrating(1000, 0),
              size(0){}

    void Read(int user_id, int page_count)
    {
        if(pages[user_id] == -1)
        {   //pagesrating[page_count]++;
            for(auto it = pagesrating.begin()+page_count; it < pagesrating.end(); it++)
                (*it)++;
            size++;
        } else
        {
            for(auto it = pagesrating.begin()+pages[user_id]; it < pagesrating.end(); it++)
                (*it)--;
            //pagesrating[page_count]++;
            for(auto it = pagesrating.begin()+page_count; it < pagesrating.end(); it++)
                (*it)++;
        }
      //  cout << pagesrating << endl;
        pages[user_id] = page_count;
    }


    double Cheer(int user_id)  {
        if(pages[user_id] == -1)
            return 0;
        if(size == 1)
            return 1;
        //cout << pagesrating << endl;
        //cout << pagesrating[pages[user_id]] << "=a" << endl;
        //cout << pages << endl;
       // cout << userids << " " << *it << user_id << endl;

        // По умолчанию деление целочисленное, поэтому
        // нужно привести числитель к типу double.
        // Простой способ сделать это — умножить его на 1.0.
        return pagesrating[pages[user_id]-1] * 1.0 / (size - 1);
        //return (it-userids.begin()) * 1.0 / (userids.size()-1);
    }

private:
    // Статическое поле не принадлежит какому-то конкретному
    // объекту класса. По сути это глобальная переменная,
    // в данном случае константная.
    // Будь она публичной, к ней можно было бы обратиться снаружи
    // следующим образом: ReadingManager::MAX_USER_COUNT.
    static const int MAX_USER_COUNT_ = 100'000;

    vector<int> user_page_counts_;//[id]
    vector<int> sorted_users_;   // id ... отсортированы по убыванию количества страниц
    vector<int> user_positions_; // [id]... позиции в векторе sorted_users_
    vector<int> pages;
    vector<int> userids;
    vector<int> pagesrating;
    int size;
    int GetUserCount() const {
        return sorted_users_.size();
    }
    void AddUser(int user_id) {
        sorted_users_.push_back(user_id);// O(const)
        user_positions_[user_id] = sorted_users_.size() - 1; // O(const)
    }
    void SwapUsers(int lhs_position, int rhs_position) {
        const int lhs_id = sorted_users_[lhs_position];
        const int rhs_id = sorted_users_[rhs_position];
        swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
        swap(user_positions_[lhs_id], user_positions_[rhs_id]);
    }
};


int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}