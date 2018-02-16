#pragma once
#include <memory>
#include <string>
#include "Token.h"
class NumToken :
	public Token
{
public:
	NumToken(const float val);
	virtual ~NumToken();

	virtual std::string prettyPrint() override;
	static std::shared_ptr<Token> alloc(const float val);

	const float val;
};

