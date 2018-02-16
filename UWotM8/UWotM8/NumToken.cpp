#include "stdafx.h"
#include "NumToken.h"


NumToken::NumToken(const float val) : Token(TokenKind::Num), val(val)
{
}


NumToken::~NumToken()
{
}

std::shared_ptr<Token> NumToken::alloc(const float val)
{
	return std::shared_ptr<Token>(new NumToken(val));
}


std::string NumToken::prettyPrint() {
	return std::to_string(val);
}