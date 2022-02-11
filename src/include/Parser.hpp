#pragma oncelexer_T
#include "Lexer.hpp"
#include "AST.hpp"

class Parser
{
public:
	Lexer* lexer;
	Token* current_token;
	Token* prev_token;

	Parser ( Lexer* l );

	auto eat ( Token_Type token ) ->void;

	auto parse (  )->AST*;

	auto parse_statement (  )->AST*;

	auto parse_statements (  )->AST*;

	auto parse_expr (  )->AST*;

	auto parse_factor (  )->AST*;

	auto parse_term (  )->AST*;

	auto parse_function_call (  )->AST*;

	auto parse_variable_definition (  )->AST*;

	auto parse_variable (  )->AST*;

	auto parse_string (  )->AST*;

	auto parse_id (  )->AST*;
};

