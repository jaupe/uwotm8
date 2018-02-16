#include "stdafx.h"
#include <iostream>
#include "UWotM8.h"


UWotM8::UWotM8()
{
}


UWotM8::~UWotM8()
{
}

std::string UWotM8::interpret(const std::string & cmd)
{
	Parser parser(cmd);
	auto expr = parser.parse();
	if (expr == nullptr) {
		return "problem parsing: " + cmd;
	}
	std::cout << "parsed" << std::endl;
	std::cout << expr->prettyPrint() << std::endl;
	auto val = expr->eval();
	if (val == nullptr) {
		return "problem evaluating: " + cmd;
	}
	return val->toString();
}
