#pragma once

#include "node.h"
#include "token.h"
#include "empty_node.h"
#include "date_comparison_node.h"
#include "event_comparison_node.h"
#include "logical_operation_node.h"

#include <memory>
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();