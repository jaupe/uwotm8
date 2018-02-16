#pragma once
#include <memory>
#include <string>
#include "Token.h"

class Lexer
{
public:
	Lexer(const std::string &cmd);
	~Lexer();

	std::shared_ptr<Token> next();
	
	std::shared_ptr<Token> peek();

	std::shared_ptr<Token> peek(size_t n);
	
	void reverse();

	char cur();
private:
	void skipWhitespace();

	char peekNext();
	std::shared_ptr<Token> lexNum();
	std::string cmd;
	size_t pos;
	size_t lastPos;
};

