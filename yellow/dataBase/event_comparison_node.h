#pragma once

#include "node.h"

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const string& event);
    bool Evaluate(const Date& date, const string& event) override;

private:
    const Comparison cmp_;
    const string event_;
};