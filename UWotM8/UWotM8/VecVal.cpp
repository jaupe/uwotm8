#include "stdafx.h"
#include <sstream>
#include <vector>
#include "NumVal.h"
#include "VecVal.h"

VecVal::VecVal(const std::vector<float> &vec) : Val(ValKind::Vec), vec(vec)
{
}

VecVal::VecVal(std::vector<float> &&vec) : Val(ValKind::Vec), vec(std::move(vec))
{
}

VecVal::~VecVal()
{
}

std::string VecVal::toString()
{
	std::ostringstream os;
	const size_t n = vec.size() - 1;
	for (size_t i = 0; i < n; i++) {
		os << vec[i] << " ";
	}
	os << vec[n];
	return os.str();
}

std::shared_ptr<Val> VecVal::add(std::shared_ptr<Val> rhs)
{
	std::vector<float> v;
	switch (rhs->kind) {
	case ValKind::Num: {
		auto rhsVal = std::static_pointer_cast<NumVal>(rhs);
		v = addVecNum(vec, rhsVal->val);
		break;
	}
	case ValKind::Vec: {
		auto rhsVec = std::static_pointer_cast<VecVal>(rhs);
		v = addVecVec(vec, rhsVec->vec);
		break;
	}
	}
	return std::make_shared<VecVal>(std::move(v));
}

std::shared_ptr<Val> VecVal::sub(std::shared_ptr<Val> rhs)
{
	std::vector<float> v;
	switch (rhs->kind) {
	case ValKind::Num: {
		auto rhsVal = std::static_pointer_cast<NumVal>(rhs);
		v = subVecNum(vec, rhsVal->val);
		break;
	}
	case ValKind::Vec: {
		auto rhsVec = std::static_pointer_cast<VecVal>(rhs);
		v = subVecVec(vec, rhsVec->vec);
		break;
	}
	}
	return std::make_shared<VecVal>(std::move(v));
}

std::shared_ptr<Val> VecVal::mul(std::shared_ptr<Val> rhs)
{
	std::vector<float> v;
	switch (rhs->kind) {
	case ValKind::Num: {
		auto rhsVal = std::static_pointer_cast<NumVal>(rhs);
		v = mulVecNum(vec, rhsVal->val);
		break;
	}
	case ValKind::Vec: {
		auto rhsVec = std::static_pointer_cast<VecVal>(rhs);
		v = mulVecVec(vec, rhsVec->vec);
		break;
	}
	}
	return std::make_shared<VecVal>(std::move(v));
}

std::shared_ptr<Val> VecVal::div(std::shared_ptr<Val> rhs)
{
	std::vector<float> v;
	switch (rhs->kind) {
	case ValKind::Num: {
		auto rhsVal = std::static_pointer_cast<NumVal>(rhs);
		v = divVecNum(vec, rhsVal->val);
		break;
	}
	case ValKind::Vec: {
		auto rhsVec = std::static_pointer_cast<VecVal>(rhs);
		v = divVecVec(vec, rhsVec->vec);
		break;
	}
	}
	return std::make_shared<VecVal>(std::move(v));
}

std::shared_ptr<Val> VecVal::sum()
{
	auto total = 0.0f;
	for (auto val : vec) {
		total += val;
	}
	return NumVal::alloc(total);
}

std::shared_ptr<Val> VecVal::sums()
{
	std::vector<float> v;
	auto total = 0.0f;
	for (auto val : vec) {
		total += val;
		v.push_back(total);
	}
	return std::make_shared<VecVal>(std::move(v));
}
