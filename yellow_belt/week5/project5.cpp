#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

template<class T>void VisitPlaces(const T& t, const vector<string> &places);



class Person
{
public:
    Person(const string& name): Name(name){}
    virtual void Walk(const string& destination) = 0;
public:
    string Name;
};

class Teacher: public Person
{
public:

    Teacher(const string& name, const string& subject): Person(name)
    {
        Subject = subject;
    }


    void Teach()
    {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }



    void Walk(const string& destination)
    {
        cout << "Teacher: " << Name << " walks to: " << destination << endl;
    }




public:
    string Subject;
};


class Student: public Person
{
public:

    Student(const string& name, const string& favouriteSong): Person(name)
    {
        FavouriteSong = favouriteSong;
    }
    void Learn()
    {
        cout << "Student: " << Name << " learns" << endl;
    }
    void Walk(const string& destination)
    {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }
    void SingSong()
    {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }
public:
    string FavouriteSong;
};


class Policeman: public Person {
public:
    Policeman(const string& name): Person(name){}

    void Walk(const string& destination)
    {
        cout << "Policeman: " << Name << " walks to: " << destination << endl;
    }

    template<class T>
    void Check(const T& t)
    {
        string str = typeid(T).name();//получает тип объекта, как строку
        str.erase(0, 1);
        cout << "Policeman: " << t.Name << " checks " << str << ". " << str << "'s name is: " << t.Name << endl;
    }


};


template<class T>
void VisitPlaces( T& t, const vector<string> &places)
{
    for (auto& p : places)
    {
        t.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
