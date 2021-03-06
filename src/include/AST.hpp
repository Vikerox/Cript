#pragma once
#include <string>
#include <vector>
#include <memory>

enum class AST_Type
{
	AST_VARIABLE_DEFINITION,
	AST_VARIABLE,
	AST_FUNCTION_CALL,
	AST_STRING,
	AST_COMPOUND,
	AST_NOOP
};

struct AST
{
public:
	AST_Type type;

	std::string variable_definition_variable_name;
	std::shared_ptr<AST> variable_definition_value;

	std::string variable_name;

	std::string function_call_name;
	std::vector<std::shared_ptr<AST>> function_call_arguments;

	std::string string_value;

	std::vector<std::shared_ptr<AST>> compound_value;

	AST (AST_Type t);
	~AST ();
};
