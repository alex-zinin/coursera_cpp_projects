#pragma once

#include <cstdlib>
#include<iostream>

using namespace std;

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector(): size(0u), capacity(0u), bptr(nullptr), eptr(nullptr) {}
    explicit SimpleVector(size_t sizel): size(sizel), capacity(sizel)
    {
        bptr = new T[size];
        eptr = bptr + size;
        for(int i = 0; i < size; i++)
        {
            T obj;
            *(bptr+i) = obj;
        }

    }
    ~SimpleVector()
    {
        delete[] bptr;
    }

    T& operator[](size_t index)
    {
        return *(bptr+index);
    }

    T* begin()
    {
        return bptr;
    };
    T* end()
    {
        return eptr;
    };
    const T* begin() const
    {
        return bptr;
    };

    const T* end() const
    {
        return eptr;
    };

    size_t Size() const
    {
        return size;
    };
    size_t Capacity() const
    {
        return capacity;
    };

    void PushBack(const T& value)
    {
        if(capacity == 0)
        {
            bptr = new T[1];
            capacity = 1;
            eptr = bptr + 1;
            *bptr = value;
            size = 1;
        }
        else
            {
            if (capacity == size) {
                T* btr = new T[capacity * 2];
                T* ptr = btr;
                T* pt = bptr;
                capacity = capacity * 2;
                for (size_t i = 0; i < size; i++) {
                    *ptr = *pt;
                    ptr++;
                    pt++;
                }
                delete[] bptr;
                bptr = btr;
                eptr = bptr + size;
            }
            *eptr = value;
            size++;
            eptr = bptr + size;
        }
    }

    const T& operator[](size_t index) const
    {
        return *(bptr+index);
    }
private:
    T* bptr;
    T* eptr;
    size_t size;
    size_t capacity;
    // Добавьте поля для хранения данных вектора
};










