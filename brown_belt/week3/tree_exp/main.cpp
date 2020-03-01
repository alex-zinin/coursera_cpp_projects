#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;


class Value_Expression : public Expression
{
public:
    Value_Expression(): value(0) {}
    Value_Expression(const int& val): value(val) {}

    int Evaluate() const
    {
        return value;
    }

    std::string ToString() const
    {
        return std::to_string(value);
    }


private:
    int value;
};



class Sum_Expression : public Expression
{
public:
    Sum_Expression(ExpressionPtr lf, ExpressionPtr rg): left(move(lf)), right(move(rg)) {}

    int Evaluate() const
    {
        return left->Evaluate() + right->Evaluate();
    }

    std::string ToString() const
    {
        return "("+left->ToString() + ")" "+" + "(" + right->ToString() +")";
    }

private:
    ExpressionPtr left;
    ExpressionPtr right;

};


class Product_Expression : public Expression
{
public:
    Product_Expression(ExpressionPtr lf, ExpressionPtr rg): left(move(lf)), right(move(rg)) {}

    int Evaluate() const
    {
        return left->Evaluate() * right->Evaluate();
    }

    std::string ToString() const
    {
        return "("+left->ToString()+ ")" + "*" + "(" + right->ToString() +")";
    }
private:
    ExpressionPtr left;
    ExpressionPtr right;

};

// Функции для формирования выражения
ExpressionPtr Value(int value)
{
    return std::make_unique<Value_Expression>(value);
}


ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right)
{
    return std::make_unique<Sum_Expression>(move(left), move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right)
{
    return std::make_unique<Product_Expression>(move(left), move(right));
}

string Print(const Expression* e) {
    if (!e) {
        return "Null expression provided";
    }
    stringstream output;
    output << e->ToString() << " = " << e->Evaluate();
    return output.str();
}

void Test() {
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

    ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);
    return 0;
}