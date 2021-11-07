#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

class ValueExpression : public Expression {
public:
    ValueExpression(int value): value(value){}
    int Evaluate() const override {
        return value;
    }

    std::string ToString() const override {
        return to_string(value);
    }
private:
    int value;
};

class SumExpression : public Expression {
public:
    SumExpression(ExpressionPtr left, ExpressionPtr right): left(std::move(left)), right(std::move(right)){}
    int Evaluate() const override {
        return left->Evaluate() + right->Evaluate();
    }

    std::string ToString() const override {
        string s("(");
        s.insert(s.size(), left->ToString());
        s.push_back(')');
        s.push_back('+');
        s.push_back('(');
        s.insert(s.size(), right->ToString());
        s.push_back(')');
        return s;
    };

private:
    ExpressionPtr left;
    ExpressionPtr right;
};

class ProductExpression : public Expression {
public:
    ProductExpression(ExpressionPtr left, ExpressionPtr right): left(std::move(left)), right(std::move(right)){}
    int Evaluate() const override {
        return left->Evaluate() * right->Evaluate();
    }

    std::string ToString() const override {
        string s("(");
        s.insert(s.size(), left->ToString());
        s.push_back(')');
        s.push_back('*');
        s.push_back('(');
        s.insert(s.size(), right->ToString());
        s.push_back(')');
        return s;
    };

private:
    ExpressionPtr left;
    ExpressionPtr right;
};

ExpressionPtr Value(int value) {
    return make_unique<ValueExpression>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<SumExpression>(std::move(left), std::move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<ProductExpression>(std::move(left), std::move(right));
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