#pragma once

#include <memory>
#include <string>
#include "Expr.h"
#include "Val.h"

enum class ExprKind {
	Num,
	Unr,
	Bin,
	Vec,
};

class Expr
{
public:
	Expr(const ExprKind kind);
	virtual ~Expr();

	virtual std::string prettyPrint() = 0;

	virtual std::shared_ptr<Val> eval() = 0;

	bool isNum();

	bool isUnr();

	bool isBin();

	bool isVec();

	const ExprKind kind;
};

