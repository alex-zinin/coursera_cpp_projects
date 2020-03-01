#pragma once
#include<iostream>
#include <typeinfo>

using namespace std;



class Person
{
public:
    Person(const string& name);
    virtual void Walk(const string& destination) = 0;
public:
    string Name;
};

class Teacher: public Person
{
public:
    Teacher(const string& name, const string& subject);
    void Teach();
    void Walk(const string& destination) override;

public:
    string Subject;
};


class Student: public Person
{
public:
    Student(const string& name, const string& favouriteSong);
    void Learn();
   void Walk(const string& destination) override;
    void SingSong();
public:
    string FavouriteSong;
};


class Policeman: public Person {
public:
    explicit Policeman(const string& name);
    template<class T> void Check(const T& t);
    void Walk(const string& destination) override ;
};


Person::Person(const string& name): Name(name){}
//virtual void Person::Walk(const string& destination) = 0;

Student::Student(const string& name, const string& favouriteSong): Person(name)
{
    this->FavouriteSong = favouriteSong;
}

void Student::Learn()
{
    cout << "Student: " << this->Name << " learns" << endl;
}

void Student::Walk(const string& destination)
{
    cout << "Student: " << this->Name << " walks to: " << destination << endl;
    cout << "Student: " << this->Name << " sings a song: " << this->FavouriteSong << endl;
}

void Student::SingSong()
{
    cout << "Student: " << this->Name << " sings a song: " << this->FavouriteSong << endl;
}


Teacher::Teacher(const string& name, const string& subject): Person(name)
{
    this->Subject = subject;
}



void Teacher::Teach()
{
    cout << "Teacher: " << this->Name << " teaches: " << this->Subject << endl;
}



void Teacher::Walk(const string& destination)
{
    cout << "Teacher: " << this->Name << " walks to: " << destination << endl;
}

Policeman::Policeman(const string& name): Person(name){}

template<class T>
void Policeman::Check(const T& t)
{
    string str = typeid(T).name();
    str.erase(0, 1);
    cout << "Policeman: " << t.Name << " checks " << str << ". " << str << "'s name is: " << t.Name << endl;
}

void Policeman::Walk(const string& destination)
{
    cout << "Policeman: " << this->Name << " walks to: " << destination << endl;
}