#pragma once
#include "AST.hpp"
#include <vector>
class Visitor;
static auto builtin_function_print(Visitor &visitor, std::vector<AST *> args) -> AST *;

class Visitor
{
public:
	std::vector<AST *> variable_definitions;

	Visitor();
	~Visitor();

	auto visit(AST *node) -> AST *;

	auto visit_variable_definition(AST *node) -> AST *;

	auto visit_variable(AST *node) -> AST *;

	auto visit_function_call(AST *node) -> AST *;

	auto visit_string(AST *node) -> AST *;

	auto visit_compound(AST *node) -> AST *;
};
