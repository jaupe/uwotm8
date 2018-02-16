#include "stdafx.h"
#include "VecExpr.h"
#include "VecVal.h"


VecExpr::VecExpr(const std::vector<float> &&vec) : Expr(ExprKind::Vec), vec(vec)
{
}


VecExpr::~VecExpr()
{
}

std::string VecExpr::prettyPrint()
{
	std::string s = "";
	for (auto val : vec) {
		s += std::to_string(val) + " ";
	}
	return s;
}

std::shared_ptr<Val> VecExpr::eval()
{
	return std::make_shared<VecVal>(vec);
}

std::shared_ptr<Expr> VecExpr::alloc(std::vector<float>&& vec)
{
	return std::make_shared<VecExpr>(std::move(vec));
}
