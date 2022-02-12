#pragma once
#include "AST.hpp"
#include <vector>
class Visitor;
static auto builtin_function_print(Visitor &visitor, std::vector<std::shared_ptr<AST>> args) -> std::shared_ptr<AST>;

class Visitor
{
public:
	std::vector<std::shared_ptr<AST>> variable_definitions;

	Visitor();
	~Visitor();

	auto visit(std::shared_ptr<AST> node) -> std::shared_ptr<AST>;

	auto visit_variable_definition(std::shared_ptr<AST> node) -> std::shared_ptr<AST>;

	auto visit_variable(std::shared_ptr<AST> node) -> std::shared_ptr<AST>;

	auto visit_function_call(std::shared_ptr<AST> node) -> std::shared_ptr<AST>;

	auto visit_string(std::shared_ptr<AST> node) -> std::shared_ptr<AST>;

	auto visit_compound(std::shared_ptr<AST> node) -> std::shared_ptr<AST>;
};
