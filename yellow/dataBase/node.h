#pragma once

#include "date.h"

enum class Comparison {
    Less,
    LessOrEqual,
    Equal,
    GreaterOrEqual,
    Greater,
    NotEqual
};

enum LogicalOperation {
    And,
    Or
};


class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) = 0;
};