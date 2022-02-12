#pragma oncelexer_T
#include "Lexer.hpp"
#include "AST.hpp"

class Parser
{
public:
	Lexer *lexer;
	Token *current_token;
	Token *prev_token;

	Parser(Lexer *l);

	auto eat(Token_Type token) -> void;

	auto parse() -> std::shared_ptr<AST>;

	auto parse_statement() -> std::shared_ptr<AST>;

	auto parse_statements() -> std::shared_ptr<AST>;

	auto parse_expr() -> std::shared_ptr<AST>;

	auto parse_factor() -> std::shared_ptr<AST>;

	auto parse_term() -> std::shared_ptr<AST>;

	auto parse_function_call() -> std::shared_ptr<AST>;

	auto parse_variable_definition() -> std::shared_ptr<AST>;

	auto parse_variable() -> std::shared_ptr<AST>;

	auto parse_string() -> std::shared_ptr<AST>;

	auto parse_id() -> std::shared_ptr<AST>;
};
