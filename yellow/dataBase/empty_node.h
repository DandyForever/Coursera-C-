#pragma once

#include "node.h"
#include "date.h"

class EmptyNode : public Node {
public:
    bool Evaluate(const Date& date, const string& event) override;
};