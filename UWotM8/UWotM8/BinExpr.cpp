#include "stdafx.h"
#include "BinExpr.h"

std::string opString(const BinOp op) {
	switch (op) {
	case BinOp::Add:
		return "Add";
	case BinOp::Div:
		return "Div";
	case BinOp::Mul:
		return "Mul";
	case BinOp::Sub:
		return "Sub";
	}
}

BinExpr::BinExpr(const std::shared_ptr<Expr> lhs, const BinOp op, const std::shared_ptr<Expr> rhs) 
	: Expr(ExprKind::Bin), lhs(lhs), op(op), rhs(rhs)
{
}

BinExpr::~BinExpr()
{
}

std::string BinExpr::prettyPrint()
{
	return opString(op) + "(" + lhs->prettyPrint() + ", " + rhs->prettyPrint() + ")";
}

std::shared_ptr<Val> BinExpr::eval()
{
	auto lhsVal = lhs->eval();
	if (lhsVal == nullptr) {
		return nullptr;
	}
	auto rhsVal = rhs->eval();
	if (rhsVal == nullptr) {
		return nullptr;
	}
	switch (op) {
	case BinOp::Add:
		return lhsVal->add(rhsVal);
	case BinOp::Sub:
		return lhsVal->sub(rhsVal);
	case BinOp::Mul:
		return lhsVal->mul(rhsVal);
	case BinOp::Div:
		return lhsVal->div(rhsVal);
	}	
	return nullptr;
}

std::shared_ptr<Expr> BinExpr::add(const std::shared_ptr<Expr> lhs, const std::shared_ptr<Expr> rhs)
{
	return alloc(lhs, BinOp::Add, rhs);
}

std::shared_ptr<Expr> BinExpr::sub(const std::shared_ptr<Expr> lhs, const std::shared_ptr<Expr> rhs)
{
	return alloc(lhs, BinOp::Sub, rhs);
}

std::shared_ptr<Expr> BinExpr::mul(const std::shared_ptr<Expr> lhs, const std::shared_ptr<Expr> rhs)
{
	return alloc(lhs, BinOp::Mul, rhs);
}

std::shared_ptr<Expr> BinExpr::div(const std::shared_ptr<Expr> lhs, const std::shared_ptr<Expr> rhs)
{
	return alloc(lhs, BinOp::Div, rhs);
}

std::shared_ptr<Expr> BinExpr::alloc(const std::shared_ptr<Expr> lhs, const BinOp op, const std::shared_ptr<Expr> rhs)
{
	return std::make_shared<BinExpr>(lhs, op, rhs);
}


