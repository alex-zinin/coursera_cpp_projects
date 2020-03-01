#include <iostream>
#include <string>
#include <vector>
#include "functions.cpp"
#include "persons.h"


using namespace std;



int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");
    s.Walk("aa");
    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}