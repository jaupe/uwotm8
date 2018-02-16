#include "stdafx.h"
#include "OpToken.h"


OpToken::OpToken(Op op) : Token(TokenKind::Op), op(op)
{
}

OpToken::~OpToken()
{
}

std::string OpToken::prettyPrint() {
	switch (op) {
	case Op::Asterix:
		return "*";
	case Op::BSlash:
		return "\\";
	case Op::FSlash:
		return "/";
	case Op::Minus:
		return "-";
	case Op::Neg:
		return "-";
	case Op::Plus:
		return "+";
	case Op::Period:
		return ".";
	}
}

bool OpToken::isFSlash() const
{
	return op == Op::FSlash;
}

bool OpToken::isBSlash() const
{
	return op == Op::BSlash;
}

bool OpToken::isAsterix() const
{
	return Op::Asterix == op;
}

bool OpToken::isPlus() const
{
	return op == Op::Plus;
}

bool OpToken::isMinus() const
{
	return op == Op::Minus;
}

bool OpToken::isNeg() const
{
	return op == Op::Neg;
}

std::shared_ptr<Token> OpToken::alloc(const Op op)
{
	return std::make_shared<OpToken>(op);
}

std::shared_ptr<Token> OpToken::fslash() {
	return alloc(Op::FSlash);
}

std::shared_ptr<Token> OpToken::bslash() {
	return alloc(Op::BSlash);
}

std::shared_ptr<Token> OpToken::plus() {
	return alloc(Op::Plus);
}

std::shared_ptr<Token> OpToken::minus() {
	return alloc(Op::Minus);
}

std::shared_ptr<Token> OpToken::asterix() {
	return alloc(Op::Asterix);
}

std::shared_ptr<Token> OpToken::dot() {
	return alloc(Op::Period);
}

std::shared_ptr<Token> OpToken::neg()
{
	return alloc(Op::Neg);
}


