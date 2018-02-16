#pragma once
#include <memory>
#include "Expr.h"

enum BinOp {
	Add,
	Sub,
	Mul,
	Div,
};

class BinExpr :
	public Expr
{
public:
	BinExpr(const std::shared_ptr<Expr> lhs, const BinOp op, const std::shared_ptr<Expr> rhs);
	~BinExpr();

	virtual std::string prettyPrint() override;

	virtual std::shared_ptr<Val> eval() override;

	static std::shared_ptr<Expr> add(const std::shared_ptr<Expr> lhs, const std::shared_ptr<Expr> rhs);
	static std::shared_ptr<Expr> sub(const std::shared_ptr<Expr> lhs, const std::shared_ptr<Expr> rhs);
	static std::shared_ptr<Expr> mul(const std::shared_ptr<Expr> lhs, const std::shared_ptr<Expr> rhs);
	static std::shared_ptr<Expr> div(const std::shared_ptr<Expr> lhs, const std::shared_ptr<Expr> rhs);
	const std::shared_ptr<Expr> lhs;
	const BinOp op;
	const std::shared_ptr<Expr> rhs;

private:
	static std::shared_ptr<Expr> alloc(const std::shared_ptr<Expr> lhs, const BinOp op, const std::shared_ptr<Expr> rhs);
};

