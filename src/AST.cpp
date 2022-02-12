#include "include/AST.hpp"
#include <iostream>

AST::AST ( AST_Type t )
{
	type = t;

	variable_definition_variable_name = "";
	variable_definition_value = nullptr;

	variable_name = "";

	function_call_name = "";
	function_call_arguments = {};

	string_value = "";

	compound_value = {};
}

AST::~AST ()
{
	std::cout << "deleting " << static_cast<int>(type) << '\n';
}
