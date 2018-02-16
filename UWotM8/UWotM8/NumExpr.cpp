#include "stdafx.h"
#include "NumExpr.h"
#include "NumVal.h"

NumExpr::NumExpr(const float val) : Expr(ExprKind::Num), val(val)
{
}


NumExpr::~NumExpr()
{
}

std::string NumExpr::prettyPrint()
{
	return "Num(" + std::to_string(val) + ")";
}

std::shared_ptr<Val> NumExpr::eval()
{
	return std::make_shared<NumVal>(val);
}

std::shared_ptr<Expr> NumExpr::alloc(const float val)
{
	return std::make_shared<NumExpr>(val);
}
