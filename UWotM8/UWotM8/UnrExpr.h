#pragma once
#include <memory>
#include "Expr.h"

enum UnrOp {
	Sum,
	Sums,
};

class UnrExpr :
	public Expr
{
public:
	UnrExpr(UnrOp op, std::shared_ptr<Expr> arg);
	~UnrExpr();

	virtual std::string prettyPrint() override;

	virtual std::shared_ptr<Val> eval() override;

	const std::shared_ptr<Expr> arg;

	const UnrOp op;

	static std::shared_ptr<Expr> sums(std::shared_ptr<Expr> arg);

	static std::shared_ptr<Expr> sum(std::shared_ptr<Expr> arg);

	
};

