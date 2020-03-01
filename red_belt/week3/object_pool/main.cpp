#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include<queue>


using namespace std;

//ostream& operator<<(ostream& os, vector<string*> v)
//{
//    for(auto x: v)
//    {
//        os << *x << " ";
//    }
//    return os;
//}

template <class T>
class ObjectPool {

public:
    ObjectPool(): dedicated(), released(){}
  T* Allocate()
  {
      if(!released.empty())
      {
          T* ptr = released.front();
          dedicated.insert(released.front());
          released.pop();
          return ptr;
      } else
      {//cout << "ye" << endl;
          //T obj;
          T* ptr = new T;
          dedicated.insert(ptr);
          return ptr;
      }

  }

  T* TryAllocate()
  {
      T* ptr = nullptr;
      if(!released.empty())
      {
          T* ptr = released.front();
          dedicated.insert(released.front());
          released.pop();
          return ptr;
      }
      return nullptr;
  }

  void Deallocate(T* const object)
  {
        auto it = dedicated.find(object);
        if(it != dedicated.end()) {
            released.push(object);
            dedicated.erase(it);
        }
        else
                throw invalid_argument("error");


  }

  ~ObjectPool()
  {

        for(auto i = released.size();  i > 0; i--)
        {
            delete(released.front());
            released.pop();
        }
        for(auto it = dedicated.begin(); it != dedicated.end(); it++)
        {
            delete(*it);
        }
        //released.erase(released.begin(), released.end());
        dedicated.clear();
  }

private:
    set<T*> dedicated;
    queue<T*> released;
  // Добавьте сюда поля
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}