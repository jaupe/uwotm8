#pragma once
#include <vector>
#include "Val.h"
class NumVal :
	public Val
{
public:
	NumVal(const float val);

	virtual ~NumVal();

	virtual std::string toString() override;

	virtual std::shared_ptr<Val> add(std::shared_ptr<Val> rhs) override;

	virtual std::shared_ptr<Val> sub(std::shared_ptr<Val> rhs) override;

	virtual std::shared_ptr<Val> mul(std::shared_ptr<Val> rhs) override;

	virtual std::shared_ptr<Val> div(std::shared_ptr<Val> rhs) override;

	virtual std::shared_ptr<Val> sum() override;

	virtual std::shared_ptr<Val> sums() override;

	const float val;

	static std::shared_ptr<Val> alloc(const float val);
};
