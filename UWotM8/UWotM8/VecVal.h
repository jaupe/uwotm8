#pragma once
#include <vector>
#include "Val.h"
class VecVal :
	public Val
{
public:
	VecVal(const std::vector<float> &vec);
	VecVal(std::vector<float>&& vec);
	virtual ~VecVal();

	virtual std::string toString() override;

	virtual std::shared_ptr<Val> add(std::shared_ptr<Val> rhs) override;

	virtual std::shared_ptr<Val> sub(std::shared_ptr<Val> rhs) override;

	virtual std::shared_ptr<Val> mul(std::shared_ptr<Val> rhs) override;

	virtual std::shared_ptr<Val> div(std::shared_ptr<Val> rhs) override;

	virtual std::shared_ptr<Val> sum() override;

	virtual std::shared_ptr<Val> sums() override;

	const std::vector<float> vec;
};

