#include "stdafx.h"
#include "Lexer.h"
#include "OpToken.h"
#include "NumToken.h"

#include <cctype>
#include <iostream>

Lexer::Lexer(const std::string &cmd) : cmd(cmd), pos(0)
{
}


Lexer::~Lexer()
{
}

void Lexer::skipWhitespace() {
	//std::cout << "skipWhitespace()" << std::endl;
	while (cur() == ' ') {
		pos += 1;
	}
}

std::shared_ptr<Token> Lexer::next()
{
	//std::cout << "Lexer::next()" << std::endl;
	if (pos >= cmd.size()) {
		//std::cout << "eof" << std::endl;
		return nullptr;
	}
	lastPos = pos;
	skipWhitespace();
	auto c = cur();
	std::cout << "cur char = " << c << std::endl;
	pos += 1;
	if (c == '/') {
		return OpToken::fslash();
	}
	else if (c == '\\') {
		return OpToken::bslash();
	}
	else if (c == '+') {
		return OpToken::plus();
	}
	else if (c == '-') {
		if (isdigit(cur())) {
			return OpToken::neg();
		}
		return OpToken::minus();
	}
	else if (c == '*') {
		return OpToken::asterix();
	}
	else if (c == '.') {
		return OpToken::dot();
	}
	else if (std::isdigit(c)) {
		pos--;
		return lexNum();
	}
	return nullptr;
}

std::shared_ptr<Token> Lexer::peek()
{
	auto i = pos;
	auto tok = next();
	pos = i;
	return tok;
}

std::shared_ptr<Token> Lexer::peek(size_t n)
{
	const auto lastPos = pos;
	for (auto i = 0; i < n-1; i++) {
		auto tok = next();
	}
	auto tok = next();
	pos = lastPos;
	return tok;
}

void Lexer::reverse()
{
	//std::cout << "reversed " << std::endl;
	pos = lastPos;
}

char Lexer::cur()
{
	auto c = cmd[pos];
	return c;
}

char Lexer::peekNext()
{
	return cmd[pos+1];
}

std::shared_ptr<Token> Lexer::lexNum()
{
	std::string s;
	auto c = cur();
	std::cout << "s =" << s << std::endl;
	while (true) {
		if (!isdigit(c) && c != '.' || iswspace(c)) {
			break;
		}
		s += c;
		pos++;
		c = cur();
	}
	std::cout << "converting " << s << std::endl;
	const float val = std::stof(s);
	return NumToken::alloc(val);
}
