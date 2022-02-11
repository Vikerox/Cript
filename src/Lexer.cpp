#include "include/Lexer.hpp"

Lexer::Lexer ( const std::string& data )
{
	contents = data;
	i = 0;
	c = contents[i];
}

Lexer::~Lexer ()
{}

void Lexer::advance ()
{
	if ( c != '\0' && i < contents.length () )
	{
		++i;
		c = contents[i];
	}
}

void Lexer::skip_whitespace ()
{
	while ( c == ' ' || c == 10 || c == '\t' )
	{
		advance ();
	}
}

auto Lexer::get_next_token () -> Token*
{
	while ( c != '\0' && i < contents.length() )
	{
		if ( c == ' ' || c == 10 || c == '\t' )
			skip_whitespace ();

		if ( isalnum ( c ) )
			return collect_id ();

		if ( c == '"' )
			return collect_string ();

		switch ( c )
		{
		case '=':
			return advance_with_token ( new Token ( Token_Type::TOKEN_EQUALS, get_current_char_as_string () ) );
			break;
		case ';':
			return advance_with_token ( new Token ( Token_Type::TOKEN_SEMI, get_current_char_as_string () ) );
			break;
		case '(':
			return advance_with_token ( new Token ( Token_Type::TOKEN_LPAREN, get_current_char_as_string () ) );
			break;
		case ')':
			return advance_with_token ( new Token ( Token_Type::TOKEN_RPAREN, get_current_char_as_string () ) );
			break;
		case ',':
			return advance_with_token ( new Token ( Token_Type::TOKEN_COMMA, get_current_char_as_string () ) );
			break;
		}
	}
	return new Token ( Token_Type::TOKEN_EOF, "\0" );
}

auto Lexer::collect_string () -> Token*
{
	advance ( );
	std::string value = "";
	while ( c != '"' )
	{
		auto s = get_current_char_as_string ();
		value += s;
		advance ();
	}

	advance ();

	return new Token ( Token_Type::TOKEN_STRING, value.data () );
}

auto Lexer::collect_id () -> Token*
{
	std::string value = "";
	while ( isalnum ( c ) )
	{
		auto s = get_current_char_as_string ();
		value += s;
		advance ();
	}

	return new Token ( Token_Type::TOKEN_ID, value.data () );
}

auto Lexer::advance_with_token ( Token* token ) -> Token*
{
	advance ();

	return token;
}

auto Lexer::get_current_char_as_string () -> std::string
{
	std::string str = "";
	str += c;
	return str;
}
