#include "stdafx.h"
#include <iostream>
#include <vector>
#include "NumExpr.h"
#include "NumToken.h"
#include "Parser.h"
#include "Token.h"
#include "UnrExpr.h"
#include "VecExpr.h"
#include "BinExpr.h"

Parser::Parser(const std::string &cmd) : lexer(cmd) 
{
}

Parser::~Parser()
{
}

std::shared_ptr<Expr> Parser::parse()
{
	//std::cout << "parse()" << std::endl;
	auto lhs = parseExpr();
	if (lhs == nullptr) {
		return nullptr;
	}

	//std::cout << "checkking nextTok" << std::endl;
	std::cout << "lhs = " << lhs->prettyPrint() << std::endl;
	auto tok = lexer.next();
	if (tok == nullptr) {
		return lhs;
	}
	std::cout << "bin tok = " << tok->prettyPrint() << std::endl;
	if (tok->isOp()) {
		auto opTok = std::static_pointer_cast<OpToken>(tok);
		//std::cout << "opTok = " << opTok->prettyPrint() << std::endl;
		auto rhs = parseExpr();
		if (rhs == nullptr) {
			throw "expected rhs";
		}
		std::cout << "rhs = " << rhs->prettyPrint() << std::endl;
		switch (opTok->op) {
		case Op::Plus: {
			return BinExpr::add(lhs, rhs);
		}
		case Op::Asterix: {
			return BinExpr::mul(lhs, rhs);
		}
		case Op::Neg: {
			return BinExpr::sub(lhs, rhs);
		}
		case Op::Minus: {
			return BinExpr::sub(lhs, rhs);
		}
		case Op::FSlash: {
			std::cout << "div" << std::endl;
			return BinExpr::div(lhs, rhs);
		}
		default:
			throw "dodgy op;";
		}
		return nullptr;
	}
	throw "dodgy tok";
}

std::shared_ptr<Expr> Parser::parseOp(Op op)
{
	//std::cout << "parseOp" << std::endl;
	auto nextTok = lexer.next();
	if (nextTok == nullptr) {
		return nullptr;
	}
	if (!nextTok->isOp()) {
		throw "expected op";
	}
	auto nextOp = std::static_pointer_cast<OpToken>(nextTok);
	switch (op) {
	case Op::FSlash: {
		//std::cout << "FSlash" << std::endl;
		switch (nextOp->op) {
		case Op::Plus: {
			auto arg = parseExpr();
			return UnrExpr::sums(arg);
		}
		default:
			throw "nyi";
		}
	}
	case Op::BSlash: {
		//std::cout << "BSlash" << std::endl;
		switch (nextOp->op) {
		case Op::Plus: {
			auto arg = parseExpr();
			return UnrExpr::sum(arg);
		}
		default:
			throw "nyi";
		}
	}
	default:
		throw "dodgy token";
	}
	return nullptr;
}

std::shared_ptr<Expr> Parser::parseVec(const float val)
{
	//std::cout << "parseVec(" << val << ")" <<std::endl;
	auto tok = lexer.next();
	if (tok == nullptr) {
		return nullptr;
	}
	std::vector<float> vec;
	vec.push_back(val);
	bool neg = false;
	while (tok->isNum() || tok->isOp()) {
		if (tok->isOp()) {
			auto opTok = std::static_pointer_cast<OpToken>(tok);
			std::cout << "opTok = " << opTok->prettyPrint() << std::endl;
			if (!opTok->isNeg()) {
				break;
			}
			tok = lexer.next();
			if (tok->isNum() == false) {
				throw "expected num";
			}
			neg = true;
		}
		auto numTok = std::static_pointer_cast<NumToken>(tok);
		auto val = neg ? numTok->val * -1 : numTok->val; 
		std::cout << "pushing " << val << std::endl;
		vec.push_back(val);
		tok = lexer.next();
		if (tok == nullptr) {
			break;
		}
		neg = false;
	}
	if (tok != nullptr) {
		lexer.reverse();
	}
	std::cout << "vec parsed" << std::endl;
	return VecExpr::alloc(std::move(vec));
}

std::shared_ptr<Expr> Parser::parseNum(const float val) {
	std::cout << "parseNum(" << val << ")" << std::endl;


	if (peekNum()) {
		return parseVec(val);
	}
	//std::cout << "return num: " << val << std::endl;
	return NumExpr::alloc(val);
}

bool Parser::peekNum() {
	if (!iswspace(lexer.cur())) {
		return false;
	}
	auto tok = lexer.peek();
	//std::cout << "peeking at tok" << std::endl;
	
	if (tok == nullptr) {
		return false;
	}
	if (tok->isNum()) {
		return true;
	}
	auto opTok = std::static_pointer_cast<OpToken>(tok);
	if (!opTok->isMinus() && !opTok->isNeg()) {
		return false;
	}
	auto nextTok = lexer.peek(2);
	if (nextTok == nullptr) {
		return false;
	}
	return nextTok->isNum();
}

std::shared_ptr<Expr> Parser::parseNegNum()
{
	auto tok = lexer.next();
	if (!tok->isNum()) {
		throw "expected number";
	}
	auto numTok = std::static_pointer_cast<NumToken>(tok);
	return NumExpr::alloc(-(numTok->val));
}

std::shared_ptr<Expr> Parser::parseExpr()
{
	std::cout << "parseExpr" << std::endl;
	auto tok = lexer.next();
	if (tok == nullptr) {
		return nullptr;
	}
	switch (tok->kind) {
	case TokenKind::Num: {
		auto numTok = std::static_pointer_cast<NumToken>(tok);
		return parseNum(numTok->val);
	}
	case TokenKind::Op: {
		auto opTok = std::static_pointer_cast<OpToken>(tok);
		if (opTok->isMinus() || opTok->isNeg()) {
			auto nxtTok = lexer.next();
			if (nxtTok == nullptr || nxtTok->isNum() == false) {
				throw "expected num";
			}
			auto numTok = std::static_pointer_cast<NumToken>(nxtTok);
			return parseNum(-1 * numTok->val);
		}
		return parseOp(opTok->op);
	}
	}
}
