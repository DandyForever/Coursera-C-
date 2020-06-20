#pragma once

#include <memory>
#include "node.h"

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation op, const shared_ptr<Node>& lhs_node, const shared_ptr<Node>& rhs_node);

    bool Evaluate(const Date& date, const string& event) override;

private:
    const LogicalOperation op_;
    shared_ptr<Node> lhs_node_;
    shared_ptr<Node> rhs_node_;
};