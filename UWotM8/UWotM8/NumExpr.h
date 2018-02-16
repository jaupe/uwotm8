#pragma once
#include <memory>
#include "Expr.h"

class NumExpr :
	public Expr
{
public:
	NumExpr(const float val);

	virtual ~NumExpr();

	virtual std::string prettyPrint() override;

	virtual std::shared_ptr<Val> eval() override;

	const float val;

	static std::shared_ptr<Expr> alloc(const float val);
};

