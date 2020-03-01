#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
private:
    T* ptr_value;
public:
    UniquePtr() : ptr_value(nullptr) {}

    UniquePtr(T * ptr): ptr_value(ptr) {}

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other): ptr_value(other.Get())
    {
        other.ptr_value = nullptr;
    }

    UniquePtr& operator = (const UniquePtr&) = delete;

    UniquePtr& operator = (nullptr_t)
    {
        delete ptr_value;
        ptr_value = nullptr;
        return  *this;
    }

    UniquePtr& operator = (UniquePtr&& other)
    {
        ptr_value = other.Get();
        other.ptr_value = nullptr;
        return *this;
    }

    ~UniquePtr()
    {
        delete ptr_value;
        ptr_value = nullptr;
    }

    T& operator * () const
    {
        return *ptr_value;
    }

    T * operator -> () const
    {
        return ptr_value;
    }

    T * Release()
    {
        auto ptr = ptr_value;
        ptr_value = nullptr;
        return ptr;
    }

    void Reset(T * ptr)
    {
        delete ptr_value;
        ptr_value = ptr;
    }

    void Swap(UniquePtr& other)
    {
        auto ptr = ptr_value;
        ptr_value = other.Get();
        other.ptr_value = ptr;
    }

    T * Get() const
    {
        return ptr_value;
    }
};


struct Item {
    static int counter;
    int value;
    Item(int v = 0): value(v) {
        ++counter;
    }
    Item(const Item& other): value(other.value) {
        ++counter;
    }
    ~Item() {
        --counter;
    }
};

int Item::counter = 0;


void TestLifetime() {
    Item::counter = 0;
    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        ptr.Reset(new Item);
        ASSERT_EQUAL(Item::counter, 1);
    }
    ASSERT_EQUAL(Item::counter, 0);

    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        auto rawPtr = ptr.Release();
        ASSERT_EQUAL(Item::counter, 1);

        delete rawPtr;
        ASSERT_EQUAL(Item::counter, 0);
    }
    ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
    UniquePtr<Item> ptr(new Item(42));
    ASSERT_EQUAL(ptr.Get()->value, 42);
    ASSERT_EQUAL((*ptr).value, 42);
    ASSERT_EQUAL(ptr->value, 42);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestLifetime);
    RUN_TEST(tr, TestGetters);
}