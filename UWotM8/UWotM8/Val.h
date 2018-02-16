#pragma once
#include <memory>
#include <vector>
#include <string>

enum ValKind {
	Num,
	Vec,
};

class Val
{
public:
	Val(const ValKind kind);
	virtual ~Val();

	virtual std::string toString() = 0;

	virtual std::shared_ptr<Val> add(std::shared_ptr<Val> rhs) = 0;

	virtual std::shared_ptr<Val> sub(std::shared_ptr<Val> rhs) = 0;

	virtual std::shared_ptr<Val> mul(std::shared_ptr<Val> rhs) = 0;

	virtual std::shared_ptr<Val> div(std::shared_ptr<Val> rhs) = 0;

	virtual std::shared_ptr<Val> sum() = 0;

	virtual std::shared_ptr<Val> sums() = 0;

	const ValKind kind;

	static std::vector<float> addVecNum(const std::vector<float> &vec, const float val);

	static std::vector<float> addVecVec(const std::vector<float> &lhs, const std::vector<float> &rhs);

	static std::vector<float> subVecNum(const std::vector<float> &vec, const float val);

	static std::vector<float> subNumVec(const std::vector<float> &vec, const float val);

	static std::vector<float> subVecVec(const std::vector<float> &lhs, const std::vector<float> &rhs);

	static std::vector<float> mulVecNum(const std::vector<float> &vec, const float val);

	static std::vector<float> mulNumVec(const std::vector<float> &vec, const float val);

	static std::vector<float> mulVecVec(const std::vector<float> &lhs, const std::vector<float> &rhs);

	static std::vector<float> divNumVec(const std::vector<float> &vec, const float val);

	static std::vector<float> divVecNum(const std::vector<float> &vec, const float val);

	static std::vector<float> divVecVec(const std::vector<float> &lhs, const std::vector<float> &rhs);
};

