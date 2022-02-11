#pragma once
#include "Token.hpp"
#include <string>

class Lexer
{
public:
	char c;
	unsigned int i;
	std::string contents;

	Lexer( const std::string& data );
	~Lexer ();

	void advance ();

	void skip_whitespace ();

	auto get_next_token ( )->Token*;

	auto collect_string ()->Token*;

	auto collect_id ()->Token*;

	auto advance_with_token (Token* token )->Token*;

	auto get_current_char_as_string ()->std::string;
};

