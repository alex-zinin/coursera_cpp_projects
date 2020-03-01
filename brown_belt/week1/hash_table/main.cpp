#include "test_runner.h"

#include <forward_list>
#include <iterator>

using namespace std;

template <typename Type, typename Hasher>
class HashSet {
public:
    using BucketList = forward_list<Type>;
    vector<BucketList> base;
    const Hasher hasher;
    const size_t num;
public:
    explicit HashSet(
            size_t num_buckets,
            const Hasher& hashe = {}
    ): base(num_buckets), hasher(hashe), num(num_buckets) {}

    void Add(const Type& value)
    {
        for(auto it = base[hasher(value) % num].begin(); it != base[hasher(value) % num].end(); it++)
        {
           // cout << hasher(value) << " " << base.size()<< endl;
            if(*it == value)
                return;
        }
        base[hasher(value) % num].push_front(value);
    }

    bool Has(const Type& value) const
    {
        for(auto it = base[hasher(value) % num].begin(); it != base[hasher(value) % num].end(); it++)
        {
            if(*it == value)
                return true;
        }
        return false;
    }

    void Erase(const Type& value)
    {
        auto previt = base[hasher(value) % num].begin();
        for(auto it = base[hasher(value) % num].begin(); it != base[hasher(value) % num].end(); it++)
        {
            if(*it == value && it == base[hasher(value) % num].begin())
            {
                base[hasher(value) % num].pop_front();
                return;
            }
            else
                if(*it == value)
                {
                    base[hasher(value) % num].erase_after(previt);
                    return;
                }
            previt = it;
        }
    }
    const BucketList& GetBucket(const Type& value) const
    {
        return base[hasher(value) % num];
    }
};

struct IntHasher {
    size_t operator()(int value) const {
        // Это реальная хеш-функция из libc++, libstdc++.
        // Чтобы она работала хорошо, std::unordered_map
        // использует простые числа для числа бакетов
        return value;
    }
};

struct TestValue {
    int value;

    bool operator==(TestValue other) const {
        return value / 2 == other.value / 2;
    }
};

struct TestValueHasher {
    size_t operator()(TestValue value) const {
        return value.value / 2;
    }
};

void TestSmoke() {
    HashSet<int, IntHasher> hash_set(2);
    hash_set.Add(3);
    hash_set.Add(4);

    ASSERT(hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(!hash_set.Has(5));

    hash_set.Erase(3);

    ASSERT(!hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(!hash_set.Has(5));

    hash_set.Add(3);
    hash_set.Add(5);

    ASSERT(hash_set.Has(3));
    ASSERT(hash_set.Has(4));
    ASSERT(hash_set.Has(5));
}

void TestEmpty() {
    HashSet<int, IntHasher> hash_set(10);
    for (int value = 0; value < 10000; ++value) {
        ASSERT(!hash_set.Has(value));
    }
}

void TestIdempotency() {
    HashSet<int, IntHasher> hash_set(10);
    hash_set.Add(5);
    ASSERT(hash_set.Has(5));
    hash_set.Add(5);
    ASSERT(hash_set.Has(5));
    hash_set.Erase(5);
    ASSERT(!hash_set.Has(5));
    hash_set.Erase(5);
    ASSERT(!hash_set.Has(5));
}

void TestEquivalence() {
    HashSet<TestValue, TestValueHasher> hash_set(10);
    hash_set.Add(TestValue{2});
    hash_set.Add(TestValue{3});

    ASSERT(hash_set.Has(TestValue{2}));
    ASSERT(hash_set.Has(TestValue{3}));

    const auto& bucket = hash_set.GetBucket(TestValue{2});
    const auto& three_bucket = hash_set.GetBucket(TestValue{3});
    ASSERT_EQUAL(&bucket, &three_bucket);

    ASSERT_EQUAL(1, distance(begin(bucket), end(bucket)));
    ASSERT_EQUAL(2, bucket.front().value);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSmoke);
    RUN_TEST(tr, TestEmpty);
    RUN_TEST(tr, TestIdempotency);
    RUN_TEST(tr, TestEquivalence);
    return 0;
}