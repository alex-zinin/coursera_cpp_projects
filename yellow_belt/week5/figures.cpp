#include <iostream>
#include<iostream>
#include<vector>
#include<memory>
#include<sstream>
#include<iomanip>
#include<cmath>

using namespace std;

class Figure
{
public:
    Figure(string nam): Names(nam) {}
    virtual string Name() = 0;
    virtual double Perimeter() = 0;
    virtual double Area() = 0;

public:
    string Names;
};

class Triangle: public Figure
{
public:
Triangle(int a1, int a2, int a3): Figure("TRIANGLE"),a(a1), b(a2), c(a3){}
     string Name() override
    {
        return Names;
    }

     double Perimeter() override
    {
        return(a+b+c);
    }
    double Area() override
    {
        double p = (this->Perimeter())/2;
        return sqrt(p*(p-a)*(p-b)*(p-c));
    }
public:
    int a, b, c;
};

class Rect: public Figure
{
public:
Rect(int a1, int a2): Figure("RECT"), a(a1), b(a2){}
    string Name() override
    {
        return Names;
    }

    double Perimeter() override
    {
        return(2*(a+b));
    }
    double Area() override
    {
        return a*b;
    }
public:
    int a, b;
};

class Circle: public Figure
{
public:
    Circle(int R): Figure("CIRCLE"), r(R){}

string Name() override
    {
        return Names;
    }

    double Perimeter() override
    {
        return(2*3.14*r);
    }
    double Area() override
    {
        return 3.14*r*r;
    }
public:
    int r;
};

shared_ptr<Figure> CreateFigure(istringstream& is)
{
    string trash, name;
    int a, b,c;
    is  >> name;
    if(name == "TRIANGLE")
    {
        is >> a >> b >> c;
        shared_ptr<Triangle> cr = make_shared<Triangle>(a, b, c);
                return cr;
    }
    if(name == "RECT")
    {
        is >> a >> b;
        shared_ptr<Rect> cr = make_shared<Rect>(a,b);
        return cr;
    }
    if(name == "CIRCLE")
    {
        is >> a;
        shared_ptr<Circle> cr = make_shared<Circle>(a);
        return cr;
    }
    //cerr << trash << name <<  "AAAAAAAAAAAAAAAAAAAA";
}

int main() {
    vector<shared_ptr<Figure>> figures;
    //string line, stat, note;
//    int val;

    //istringstream is(line);
//    is >> stat >> note;
//    is >> val;
//    cout << stat << " " << note << endl << val << endl;






    for (string line; getline(cin, line); ) {
        istringstream is(line);
        //cout << line;


        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));

        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}
