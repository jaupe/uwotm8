#include "stdafx.h"
#include "Val.h"


Val::Val(const ValKind kind) : kind(kind)
{
}


Val::~Val()
{
}

std::vector<float> Val::addVecNum(const std::vector<float> &vec, const float val) {
	const auto n = vec.size();
	std::vector<float> out(n);
	for (int i = 0; i < n; i++) {
		out[i] = vec[i] + val;
	}
	return out;
}

std::vector<float> Val::addVecVec(const std::vector<float> &lhs, const std::vector<float> &rhs) {
	const auto n = lhs.size();
	std::vector<float> out(n);
	for (auto i = 0; i < n; i++) {
		out[i] = lhs[i] + rhs[i];
	}
	return out;
}

std::vector<float> Val::subVecNum(const std::vector<float> &vec, const float val) {
	const auto n = vec.size();
	std::vector<float> out(n);
	for (int i = 0; i < n; i++) {
		out[i] = vec[i] - val;
	}
	return out;
}

std::vector<float> Val::subNumVec(const std::vector<float> &vec, const float val) {
	const auto n = vec.size();
	std::vector<float> out(n);
	for (int i = 0; i < n; i++) {
		out[i] = val - vec[i];
	}
	return out;
}

std::vector<float> Val::subVecVec(const std::vector<float> &lhs, const std::vector<float> &rhs) {
	const auto n = lhs.size();
	std::vector<float> out(n);
	for (auto i = 0; i < n; i++) {
		out[i] = lhs[i] - rhs[i];
	}
	return out;
}

std::vector<float> Val::mulVecNum(const std::vector<float> &vec, const float val) {
	const auto n = vec.size();
	std::vector<float> out(n);
	for (int i = 0; i < n; i++) {
		out[i] = val * vec[i];
	}
	return out;
}

std::vector<float> Val::mulNumVec(const std::vector<float> &vec, const float val) {
	const auto n = vec.size();
	std::vector<float> out(n);
	for (int i = 0; i < n; i++) {
		out[i] = val * vec[i];
	}
	return out;
}

std::vector<float> Val::mulVecVec(const std::vector<float> &lhs, const std::vector<float> &rhs) {
	const auto n = lhs.size();
	std::vector<float> out(n);
	for (auto i = 0; i < n; i++) {
		out[i] = lhs[i] * rhs[i];
	}
	return out;
}

std::vector<float> Val::divNumVec(const std::vector<float> &vec, const float val) {
	const auto n = vec.size();
	std::vector<float> out(n);
	for (int i = 0; i < n; i++) {
		out[i] = val / vec[i];
	}
	return out;
}

std::vector<float> Val::divVecNum(const std::vector<float> &vec, const float val) {
	const auto n = vec.size();
	std::vector<float> out(n);
	for (int i = 0; i < n; i++) {
		out[i] = vec[i] / val;
	}
	return out;
}

std::vector<float> Val::divVecVec(const std::vector<float> &lhs, const std::vector<float> &rhs) {
	const auto n = lhs.size();
	std::vector<float> out(n);
	for (auto i = 0; i < n; i++) {
		out[i] = lhs[i] / rhs[i];
	}
	return out;
}