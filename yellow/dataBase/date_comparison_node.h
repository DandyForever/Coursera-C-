#pragma once

#include "node.h"

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp, const Date& date);
    bool Evaluate(const Date& date, const string& event) override;

private:
    const Comparison cmp_;
    const Date date_;
};