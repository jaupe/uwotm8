#pragma once
#include <memory>
#include "Token.h"

enum Op {
	FSlash,
	BSlash,
	Plus,
	Minus,
	Asterix,
	Period,
	Neg,
};

class OpToken :
	public Token
{
public:
	OpToken(Op op);
	virtual ~OpToken();

	virtual std::string prettyPrint() override;

	bool isFSlash() const;

	bool isBSlash() const;

	bool isAsterix() const;

	bool isPlus() const;

	bool isMinus() const;

	bool isNeg() const;

	static std::shared_ptr<Token> fslash();

	static std::shared_ptr<Token> bslash();

	static std::shared_ptr<Token> plus();

	static std::shared_ptr<Token> minus();

	static std::shared_ptr<Token> asterix();

	static std::shared_ptr<Token> dot();

	static std::shared_ptr<Token> neg();

	const Op op;
private:
	static std::shared_ptr<Token> alloc(Op op);
};

