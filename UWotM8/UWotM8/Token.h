#pragma once

#include <string>

enum class TokenKind {
	Num,
	Op,
};

class Token
{
public:
	Token(TokenKind kind);
	virtual ~Token();

	virtual std::string prettyPrint() = 0;

	const TokenKind kind;

	bool isOp() const;

	bool isNum() const;
};

