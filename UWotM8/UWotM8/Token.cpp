#include "stdafx.h"
#include "Token.h"

Token::Token(TokenKind kind) : kind(kind)
{
}

Token::~Token()
{
}

bool Token::isOp() const
{
	return kind == TokenKind::Op;
}

bool Token::isNum() const
{
	return kind == TokenKind::Num;
}
