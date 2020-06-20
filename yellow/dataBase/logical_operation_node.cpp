#include "logical_operation_node.h"

LogicalOperationNode::LogicalOperationNode(const LogicalOperation op, const shared_ptr<Node>& lhs_node, const shared_ptr<Node>& rhs_node)
        : op_(op), lhs_node_(lhs_node), rhs_node_(rhs_node) {};

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) {
    switch (op_) {
        case LogicalOperation::Or:
            return lhs_node_->Evaluate(date, event) || rhs_node_->Evaluate(date, event);
        case LogicalOperation::And:
            return lhs_node_->Evaluate(date, event) && rhs_node_->Evaluate(date, event);
    }
}