#include "stdafx.h"
#include "UnrExpr.h"


UnrExpr::UnrExpr(UnrOp op, std::shared_ptr<Expr> arg) : Expr(ExprKind::Unr), op(op), arg(arg)
{
}


UnrExpr::~UnrExpr()
{
}

std::string UnrExpr::prettyPrint()
{
	std::string s = "";
	switch (op) {
	case UnrOp::Sum:
		s = "sum(";
		break;
	case UnrOp::Sums:
		s = "sums(";
		break;
	}
	s += arg->prettyPrint() + ")";
	return s;
}

std::shared_ptr<Val> UnrExpr::eval()
{
	auto val = arg->eval();
	switch (op) {
	case UnrOp::Sum:
		return val->sum();
	case UnrOp::Sums:
		return val->sums();
	}
}

std::shared_ptr<Expr> UnrExpr::sum(std::shared_ptr<Expr> arg)
{
	return std::make_shared<UnrExpr>(UnrOp::Sum, arg);
}

std::shared_ptr<Expr> UnrExpr::sums(std::shared_ptr<Expr> arg)
{
	return std::make_shared<UnrExpr>(UnrOp::Sums, arg);
}
