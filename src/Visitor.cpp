#include "include/Visitor.hpp"
#include <iostream>

static auto builtin_function_print(Visitor &visitor, std::vector<std::shared_ptr<AST>> args) -> std::shared_ptr<AST>
{
	for (auto it : args)
	{
		auto visited_ast = visitor.visit(it);

		switch (visited_ast->type)
		{
		case AST_Type::AST_STRING:
			std::cout << visited_ast->string_value;
			break;

		default:
			std::cout << "unkown data Type at " << visited_ast << std::endl;
			exit(1);
			break;
		}
	}
	return std::shared_ptr<AST>(new AST(AST_Type::AST_NOOP));
}

Visitor::Visitor()
{
	variable_definitions = {};
}

Visitor::~Visitor()
{
}

auto Visitor::visit(std::shared_ptr<AST> node) -> std::shared_ptr<AST>
{
	switch (node->type)
	{
	case AST_Type::AST_VARIABLE_DEFINITION:
		return visit_variable_definition(node);
		break;
	case AST_Type::AST_VARIABLE:
		return visit_variable(node);
		break;
	case AST_Type::AST_FUNCTION_CALL:
		return visit_function_call(node);
		break;
	case AST_Type::AST_STRING:
		return visit_string(node);
		break;
	case AST_Type::AST_COMPOUND:
		return visit_compound(node);
		break;
	case AST_Type::AST_NOOP:
		return node;
		break;
	default:
		std::cout << "Unkown ast node with type " << static_cast<int>(node->type) << std::endl;
		exit(1);
		return std::shared_ptr<AST>(new AST(AST_Type::AST_NOOP));
		break;
	}
}

auto Visitor::visit_variable_definition(std::shared_ptr<AST> node) -> std::shared_ptr<AST>
{
	variable_definitions.push_back(node);
	return node;
}

auto Visitor::visit_variable(std::shared_ptr<AST> node) -> std::shared_ptr<AST>
{
	for (auto it : variable_definitions)
	{
		if (it->variable_definition_variable_name == node->variable_name)
			return visit(it->variable_definition_value);
	}
	std::cout << "variable " + node->variable_name + " not defined" << std::endl;
	exit(1);
	return std::shared_ptr<AST>(new AST(AST_Type::AST_NOOP));
}

auto Visitor::visit_function_call(std::shared_ptr<AST> node) -> std::shared_ptr<AST>
{
	if (node->function_call_name == "print")
	{
		return builtin_function_print(*this, node->function_call_arguments);
	}
	else
	{
		std::cout << "undefined method " + node->function_call_name << std::endl;
		exit(1);
	}
	return std::shared_ptr<AST>(new AST(AST_Type::AST_NOOP));
}

auto Visitor::visit_string(std::shared_ptr<AST> node) -> std::shared_ptr<AST>
{
	return node;
}

auto Visitor::visit_compound(std::shared_ptr<AST> node) -> std::shared_ptr<AST>
{
	for (auto &it : node->compound_value)
	{
		visit(it);
	}

	return std::shared_ptr<AST>(new AST(AST_Type::AST_NOOP));
}
