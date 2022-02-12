#include <iostream>
#include <string>
#include <fstream>
#include "include/Lexer.hpp"
#include "include/Parser.hpp"
#include "include/Visitor.hpp"

std::string readFile(char *filepath);

int main(int argc, char **argv)
{
	std::string input = "var name = \"hello world!\n\";\n"
						"var cool = \"Hi\";\n"
						"print(name,\"\twhats up\t\", cool);\n";
	switch (argc)
	{
	case 1:
		std::cout << "here be help" << std::endl;
		// return 0;
		break;
	case 2:
		input = readFile(argv[1]);
		break;
	default:
		break;
	}
	Lexer *lexer = new Lexer(input);
	Token *token = nullptr;

	Parser *parser = new Parser(lexer);
	auto root = parser->parse();

	auto visitor = std::shared_ptr<Visitor>(new Visitor());
	visitor->visit(root);

	delete parser;
	delete lexer;
	return 0;
}

std::string readFile(char *filepath)
{
	std::ifstream file;
	file.open(filepath);
	if (file.fail())
	{
		std::cout << "Failed to open " << filepath;
		exit(1);
	}

	std::string retStr(std::istreambuf_iterator<char>{file}, {});

	return retStr;
}
