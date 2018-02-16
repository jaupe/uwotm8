#pragma once

#include  "Expr.h"
#include  "Lexer.h"
#include  "OpToken.h"

class Parser
{
public:
	Parser(const std::string &cmd);
	~Parser();
	std::shared_ptr<Expr> parse();
private:
	std::shared_ptr<Expr> parseVec(const float val);
	std::shared_ptr<Expr> parseNum(const float val);
	std::shared_ptr<Expr> parseNegNum();
	std::shared_ptr<Expr> parseOp(Op op);
	std::shared_ptr<Expr> parseExpr();
	bool peekNum();
	Lexer lexer;
};

