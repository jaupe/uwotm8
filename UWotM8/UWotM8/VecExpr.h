#pragma once
#include "Expr.h"
#include <memory>
#include <vector>
class VecExpr :
	public Expr
{
public:
	VecExpr(const std::vector<float> &&vec);
	virtual ~VecExpr();

	const std::vector<float> vec;

	virtual std::string prettyPrint() override;

	std::shared_ptr<Val> eval() override;

	static std::shared_ptr<Expr> alloc(std::vector<float> &&vec);
};

