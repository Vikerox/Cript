#include "include/AST.hpp"

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
