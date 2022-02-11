#include "include/Parser.hpp"
#include <iostream>

Parser::Parser ( Lexer* l )
{
	lexer = l;
	current_token = lexer->get_next_token ();
	prev_token = current_token;
}

auto Parser::eat ( Token_Type token ) -> void
{
	if ( current_token->type == token )
	{
		prev_token = current_token;
		current_token = lexer->get_next_token ();
	}
	else
	{
		std::cout << "Unexpected token: '" << current_token->value << "'\n"
			<< "Is " << static_cast<int>(current_token->type) << "\tShould be " << static_cast<int>(token) << std::endl;
		exit ( 1 );
	}
}

auto Parser::parse () -> AST*
{
	return parse_statements ();
}

auto Parser::parse_statement () -> AST*
{
	switch ( current_token->type )
	{
	case Token_Type::TOKEN_ID:
		return parse_id ( );
		break;
	default:
		return new AST ( AST_Type::AST_NOOP );
		break;
	}
}

auto Parser::parse_statements () -> AST*
{
	AST* compound = new AST ( AST_Type::AST_COMPOUND );

	AST* ast_statement = parse_statement ( );

	compound->compound_value.push_back ( ast_statement );

	while ( current_token->type == Token_Type::TOKEN_SEMI )
	{
		eat ( Token_Type::TOKEN_SEMI );

		AST* ast_statement = parse_statement ();

		if ( ast_statement )
		{
			compound->compound_value.push_back ( ast_statement );
		}
	}

	return compound;
}

auto Parser::parse_expr () -> AST*
{
	switch ( current_token->type )
	{
	case Token_Type::TOKEN_STRING:
		return parse_string ();
		break;
	case Token_Type::TOKEN_ID:
		return parse_id ();
		break;
	default:
		return new AST ( AST_Type::AST_NOOP );
		break;
	}
}

auto Parser::parse_factor () -> AST*
{
	return new AST ( AST_Type::AST_NOOP );
}

auto Parser::parse_term () -> AST*
{
	return new AST ( AST_Type::AST_NOOP );
}

auto Parser::parse_function_call () -> AST*
{
	AST* function_call = new AST ( AST_Type::AST_FUNCTION_CALL );

	function_call->function_call_name = prev_token->value;
	eat ( Token_Type::TOKEN_LPAREN );

	AST* ast_expr = parse_expr ( );

	function_call->function_call_arguments.push_back ( ast_expr );

	while ( current_token->type == Token_Type::TOKEN_COMMA )
	{
		eat ( Token_Type::TOKEN_COMMA );

		AST* ast_expr = parse_expr ();

		function_call->function_call_arguments.push_back ( ast_expr );
	}
	eat ( Token_Type::TOKEN_RPAREN );

	return function_call;
}

auto Parser::parse_variable_definition () -> AST*
{
	eat ( Token_Type::TOKEN_ID ); // var
	std::string variable_name = current_token->value;
	eat ( Token_Type::TOKEN_ID ); // var name
	eat ( Token_Type::TOKEN_EQUALS ); // var name = 

	AST* variable_value = parse_expr ( );

	AST* variable_definition = new AST ( AST_Type::AST_VARIABLE_DEFINITION );
	variable_definition->variable_definition_variable_name = variable_name;
	variable_definition->variable_definition_value = variable_value;

	return variable_definition;
}

auto Parser::parse_variable () -> AST*
{
	std::string token_value = current_token->value;
	eat ( Token_Type::TOKEN_ID ); // var name or function call name
	if ( current_token->type == Token_Type::TOKEN_LPAREN )
		return parse_function_call ();

	AST* ast_variable = new AST ( AST_Type::AST_VARIABLE );
	ast_variable->variable_name = token_value;

	return ast_variable;
}

auto Parser::parse_string () -> AST*
{
	AST* ast_string = new AST ( AST_Type::AST_STRING );
	ast_string->string_value = current_token->value;

	eat ( Token_Type::TOKEN_STRING );

	return ast_string;
}

auto Parser::parse_id () -> AST*
{
	if ( current_token->value == "var" )
		return parse_variable_definition ( );
	else
		return parse_variable ( );
}
