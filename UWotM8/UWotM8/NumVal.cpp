#include "stdafx.h"
#include <sstream>
#include "NumVal.h"
#include "VecVal.h"

NumVal::NumVal(const float val) : Val(ValKind::Num), val(val)
{
}


NumVal::~NumVal()
{
}

std::string NumVal::toString()
{
	std::ostringstream os;
	os << val;
	return os.str();
}

std::shared_ptr<Val> NumVal::add(std::shared_ptr<Val> rhs)
{
	switch (rhs->kind) {
	case ValKind::Num: {
		auto numVal = std::static_pointer_cast<NumVal>(rhs);
		return std::make_shared<NumVal>(val + numVal->val);
	}
	case ValKind::Vec: {
		auto vecVal = std::static_pointer_cast<VecVal>(rhs);
		auto vec = addVecNum(vecVal->vec, val);
		return std::make_shared<VecVal>(std::move(vec));
	}
	}
	return nullptr;
}

std::shared_ptr<Val> NumVal::sub(std::shared_ptr<Val> rhs)
{
	switch (rhs->kind) {
	case ValKind::Num: {
		auto numVal = std::static_pointer_cast<NumVal>(rhs);
		return std::make_shared<NumVal>(val - numVal->val);
	}
	case ValKind::Vec: {
		auto vecVal = std::static_pointer_cast<VecVal>(rhs);
		auto vec = subNumVec(vecVal->vec, val);
		return std::make_shared<VecVal>(std::move(vec));
	}
	}
	return nullptr;
}

std::shared_ptr<Val> NumVal::mul(std::shared_ptr<Val> rhs)
{
	if (rhs == nullptr) {
		return nullptr;
	}
	switch (rhs->kind) {
	case ValKind::Num: {
		auto numVal = std::static_pointer_cast<NumVal>(rhs);
		return std::make_shared<NumVal>(val * numVal->val);
	}
	case ValKind::Vec: {
		auto vecVal = std::static_pointer_cast<VecVal>(rhs);
		auto vec = mulVecNum(vecVal->vec, val);
		return std::make_shared<VecVal>(std::move(vec));
	}
	}
	return nullptr;
}

std::shared_ptr<Val> NumVal::div(std::shared_ptr<Val> rhs)
{
	switch (rhs->kind) {
	case ValKind::Num: {
		auto numVal = std::static_pointer_cast<NumVal>(rhs);
		return std::make_shared<NumVal>(val / numVal->val);
	}
	case ValKind::Vec: {
		auto vecVal = std::static_pointer_cast<VecVal>(rhs);
		auto vec = divNumVec(vecVal->vec, val);
		return std::make_shared<VecVal>(std::move(vec));
	}
	}
	return nullptr;
}

std::shared_ptr<Val> NumVal::sum()
{
	return NumVal::alloc(val);
}

std::shared_ptr<Val> NumVal::sums()
{
	return NumVal::alloc(val);
}


std::shared_ptr<Val> NumVal::alloc(const float val)
{
	return std::make_shared<NumVal>(val);
}
