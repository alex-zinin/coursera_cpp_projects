#include <iostream>
#include <vector>

using namespace std;


template<typename T>
class Deque
{
public:
    Deque(): size(0)
    {
        direct.clear();
        reverse.clear();
    }
    Deque(vector<T> v): direct(v), size(0)
    {
//        for(int i = 0; i < v.size(); i++)
//        {
//            reverse[i] = v[i];
//        }
    }

    bool Empty() const
    {
        if(direct.empty() && reverse.empty())
            return true;
        else
            return false;
    }

    int Size() const
    {
        return size;
    }

    T& operator[](size_t index)
    {
        if(index >= reverse.size())
        {
            T& s = direct[index-reverse.size()];
            return s;
        }
        else
        {
            T& s = reverse[reverse.size()-index-1];
            return s;
        }


    }

    const T& operator[](size_t index) const
    {
        if(index >= reverse.size())
        {
            const T &s = direct[index-reverse.size()];
            return s;
        }
        else
        {
            const T &s = reverse[reverse.size()-index-1];
            return s;
        }

    }

    T& At(size_t index)
    {
        if(index >= size)
            throw out_of_range("Error");
        if(index >= reverse.size())
        {
            T& s = direct[index-reverse.size()];
            return s;
        }
        else
        {
            T& s = reverse[reverse.size()-index-1];
            return s;
        }
    }

    T& At(size_t index) const
    {
        if(index >= size)
            throw out_of_range("Error");
        if(index >= reverse.size())
        {
            const T &s = direct[index-reverse.size()-1];
            return s;
        }
        else
        {
            const T &s = reverse[reverse.size()-index-1];
            return s;
        }
    }

    const T& Front() const
    {
        if(reverse.empty())
        {
            const T& s = direct[0];
            return s;
        }
        else
        {
            const T& s = reverse.back();
            return s;
        }
    }

    T& Front()
    {
        if(reverse.empty())
        {
            T& s = direct.front();
            return s;
        }
        else
        {
            T& s = reverse.back();
            return s;
        }
    }

    T& Back()
    {
        if(direct.empty())
        {
            T& s = reverse.front();
            return s;
        }
        else
        {
            T& s = direct.back();
            return s;
        }
    }

    const T& Back() const
    {
        if(direct.empty())
        {
            const T& s = reverse.front();
            return s;
        }
        else
        {
            const T& s = direct.back();
            return s;
        }
    }

    void PushFront(const T& x)
    {
        reverse.push_back(x);
        size = size + 1;
    }

    void PushBack(const T& x)
    {
        direct.push_back(x);
        size = size + 1;

    }

public:
    vector<T> direct;
    vector<T> reverse;
    int size;
};

int main() {
//    Deque<int> d;
//    d.PushBack(1);
//    d.PushBack(2);
//    d.PushFront(0);
//    d.PushFront(-1);
//    cout << d.Size() << endl;
    //cout << d[1];
    //std::cout << "Hello, World!" << std::endl;
    return 0;
}
