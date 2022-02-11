#pragma once
#include <string>

enum class Token_Type
{
	TOKEN_ID,
	TOKEN_EQUALS,
	TOKEN_STRING,
	TOKEN_SEMI,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_COMMA,
	TOKEN_EOF
};

class Token
{
public:
	Token_Type type;

	std::string value;

	Token ( Token_Type t, std::string v );
};

