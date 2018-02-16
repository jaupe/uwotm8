#include "stdafx.h"
#include "Expr.h"

Expr::Expr(const ExprKind kind) : kind(kind)
{
}

Expr::~Expr()
{
}

bool Expr::isNum()
{
	return kind == ExprKind::Num;
}

bool Expr::isUnr()
{
	return kind == ExprKind::Unr;
}

bool Expr::isBin()
{
	return kind == ExprKind::Bin;
}

bool Expr::isVec()
{
	return kind == ExprKind::Vec;
}
