#include "test_runner.h"

#include <functional>
#include <string>
using namespace std;

template <typename T>
class LazyValue {
public:
    explicit LazyValue(std::function<T()> init) : init_func(init), value_ptr(nullptr){}

    bool HasValue() const
    {
        return value_ptr != nullptr;
    }
    const T& Get() const
    {
        if(value_ptr == nullptr)
        {
            value_ptr = new T(init_func());
            return *value_ptr;
        }
        else
            return *value_ptr;
    }

private:
    std::function<T()> init_func;
    mutable T* value_ptr;
};

void UseExample() {
    const string big_string = "Giant amounts of memory";

    LazyValue<string> lazy_string([&big_string] { return big_string; });

    ASSERT(!lazy_string.HasValue());
    ASSERT_EQUAL(lazy_string.Get(), big_string);
    ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled() {
    bool called = false;

    {
        LazyValue<int> lazy_int([&called] {
            called = true;
            return 0;
        });
    }
    ASSERT(!called);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, UseExample);
    RUN_TEST(tr, TestInitializerIsntCalled);
    return 0;
}