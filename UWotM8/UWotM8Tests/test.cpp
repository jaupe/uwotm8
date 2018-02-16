#include "pch.h"
#include <iostream>
#include "../UWotM8/Lexer.h"
#include "../UWotM8/Parser.h"
#include "../UWotM8/OpToken.h"
#include "../UWotM8/NumToken.h"
#include "../UWotM8/Expr.h"
#include "../UWotM8/NumExpr.h"
#include "../UWotM8/UnrExpr.h"
#include "../UWotM8/VecExpr.h"
#include "../UWotM8/BinExpr.h"
#include "../UWotM8/UWotM8.h"
#include "../UWotM8/NumVal.h"

void testNum(Lexer &lexer, const float val) {
	auto tok = lexer.next();
	EXPECT_TRUE(tok->isNum());
	auto numTok = std::static_pointer_cast<NumToken>(tok);
	EXPECT_EQ(numTok->val, val);
}

void testOp(Lexer &lexer, const Op op) {
	auto tok = lexer.next();
	EXPECT_TRUE(tok->isOp());
	auto opTok = std::static_pointer_cast<OpToken>(tok);
	EXPECT_EQ(opTok->op, op);
}

TEST(Lexer, LexBinMinus) {
	Lexer lexer("1-2");
	testNum(lexer, 1);
	testOp(lexer, Op::Neg);
	testNum(lexer, 2);
}

TEST(Lexer, LexBinMinus2) {
	Lexer lexer("1 - 2");
	testNum(lexer, 1);
	testOp(lexer, Op::Minus);
	testNum(lexer, 2);
}

TEST(Lexer, LexVec2) {
	Lexer lexer("1 -2");
	testNum(lexer, 1);
	testOp(lexer, Op::Neg);
	testNum(lexer, 2);
}


TEST(Lexer, LexInteger) {
	Lexer lexer("20");
	testNum(lexer, 20);
}

TEST(Lexer, LexRational) {
	Lexer lexer("20.1234");
	testNum(lexer, 20.1234f);
}

TEST(Lexer, LexNegInteger) {
	Lexer lexer("-20");
	testOp(lexer, Op::Neg);
	testNum(lexer, 20);
}

TEST(Lexer, LexNegRational) {
	Lexer lexer("-20.1234");
	testOp(lexer, Op::Neg);
	testNum(lexer, 20.1234f);
}

TEST(Lexer, LexVec) {
	Lexer lexer("1 22 -333 -4444.1234");
	testNum(lexer, 1);
	testNum(lexer, 22);
	testOp(lexer, Op::Neg);
	testNum(lexer, 333);
	testOp(lexer, Op::Neg);
	testNum(lexer, 4444.1234);
}

TEST(Lexer, LexSumOfVec) {
	Lexer lexer("/+1 22 -333 -4444.1234");
	testOp(lexer, Op::FSlash);
	testOp(lexer, Op::Plus);
	testNum(lexer, 1);
	testNum(lexer, 22);
	testOp(lexer, Op::Neg);
	testNum(lexer, 333);
	testOp(lexer, Op::Neg);
	testNum(lexer, 4444.1234f);
}

TEST(Lexer, LexSumsOfVec) {
	Lexer lexer("\\+1 22 -333 -4444.1234");
	testOp(lexer, Op::BSlash);
	testOp(lexer, Op::Plus);
	testNum(lexer, 1);
	testNum(lexer, 22);
	testOp(lexer, Op::Neg);
	testNum(lexer, 333);
	testOp(lexer, Op::Neg);
	testNum(lexer, 4444.1234f);
}

TEST(Lexer, Lexify) {
	Lexer lexer("\\+1 2 3-1*23/4");
	testOp(lexer, Op::BSlash);
	testOp(lexer, Op::Plus);
	testNum(lexer, 1);
	testNum(lexer, 2);
	testNum(lexer, 3);
	testOp(lexer, Op::Neg);
	testNum(lexer, 1);
	testOp(lexer, Op::Asterix);
	testNum(lexer, 23);
	testOp(lexer, Op::FSlash);
	testNum(lexer, 4);
}

TEST(Parser, parseNegInt) {
	Parser parser("-1234");
	auto expr = parser.parse();
	EXPECT_TRUE(expr->isNum());
	auto numExpr = std::dynamic_pointer_cast<NumExpr>(expr);
	EXPECT_EQ(numExpr->val, -1234.0f);
}

TEST(Parser, parseNegFloat) {
	Parser parser("-12.02");
	auto expr = parser.parse();
	EXPECT_TRUE(expr->isNum());
	auto numExpr = std::dynamic_pointer_cast<NumExpr>(expr);
	EXPECT_EQ(numExpr->val, -12.02f);
}

TEST(Parser, parseNum) {
	Parser parser("1234");
	auto expr = parser.parse();
	EXPECT_TRUE(expr->isNum());
	auto numExpr = std::dynamic_pointer_cast<NumExpr>(expr);
	EXPECT_EQ(numExpr->val, 1234.0f);
}

TEST(Parser, parseVecOfPosInts) {
	Parser parser("1 2 3 4");
	auto expr = parser.parse();
	EXPECT_TRUE(expr->isVec());
	auto vecExpr = std::dynamic_pointer_cast<VecExpr>(expr);
	EXPECT_EQ(vecExpr->vec.size(), 4);
	auto v = std::vector<float>{ 1, 2, 3, 4 };
	EXPECT_EQ(vecExpr->vec, v);
}

TEST(Parser, parseVecOfNegInts) {
	Parser parser("-1 -2 -3 -4");
	auto expr = parser.parse();
	EXPECT_TRUE(expr->isVec());
	auto vecExpr = std::dynamic_pointer_cast<VecExpr>(expr);
	EXPECT_EQ(vecExpr->vec.size(), 4);
	auto v = std::vector<float>{ -1, -2, -3, -4 };
	EXPECT_EQ(vecExpr->vec, v);
}

TEST(Parser, parseVecOfVariadicNums) {
	Parser parser("1 -2 33.33 -44.444 100");
	auto expr = parser.parse();
	EXPECT_TRUE(expr->isVec());
	auto vecExpr = std::dynamic_pointer_cast<VecExpr>(expr);
	EXPECT_EQ(vecExpr->vec.size(), 5);
	auto v = std::vector<float>{ 1, -2, 33.33f, -44.444f, 100};
	EXPECT_EQ(vecExpr->vec, v);
}

TEST(Parser, parseSums) {
	try {
		Parser parser("/+1 2 3");
		auto expr = parser.parse();
		EXPECT_EQ(expr->kind, ExprKind::Unr);
		auto unrExpr = std::dynamic_pointer_cast<UnrExpr>(expr);
		EXPECT_EQ(unrExpr->op, UnrOp::Sums);

		auto arg = unrExpr->arg;
		EXPECT_TRUE(arg->isVec());
		auto vecArg = std::static_pointer_cast<VecExpr>(arg);
		std::vector<float> vec = vecArg->vec;
		std::vector<float> exp = { 1, 2, 3 };
		EXPECT_EQ(vec, exp);
	}
	catch (std::string &e) {
		std::cout << e << std::endl;
	}
}

TEST(Parser, parseSum) {
	try {
		Parser parser("\\+1 2 3");
		auto expr = parser.parse();
		EXPECT_EQ(expr->kind, ExprKind::Unr);
		auto unrExpr = std::dynamic_pointer_cast<UnrExpr>(expr);
		EXPECT_EQ(unrExpr->op, UnrOp::Sum);

		auto arg = unrExpr->arg;
		EXPECT_TRUE(arg->isVec());
		auto vecArg = std::static_pointer_cast<VecExpr>(arg);
		std::vector<float> vec = vecArg->vec;
		std::vector<float> exp = { 1, 2, 3 };
		EXPECT_EQ(vec, exp);
	}
	catch (std::string &e) {
		std::cout << e << std::endl;
	}
}

TEST(Parser, parseBinAddVecNum) {
	Parser parser("1 2 3+4");
	auto expr = parser.parse();
	EXPECT_EQ(expr->kind, ExprKind::Bin);
	auto binExpr = std::static_pointer_cast<BinExpr>(expr);
	auto lhs = binExpr->lhs;
	auto rhs = binExpr->rhs;
	EXPECT_EQ(lhs->kind, ExprKind::Vec);
	EXPECT_EQ(rhs->kind, ExprKind::Num);
	EXPECT_EQ(binExpr->op, BinOp::Add);

	auto lhsVec = std::static_pointer_cast<VecExpr>(lhs);
	std::vector<float> exp = { 1, 2, 3 };
	EXPECT_EQ(lhsVec->vec, exp);

	auto rhsNum = std::static_pointer_cast<NumExpr>(rhs);
	EXPECT_EQ(rhsNum->val, 4);
}

TEST(Parser, parseBinAddVecVec) {
	try {
		Parser parser("1 2 3+4 5 6");
		auto expr = parser.parse();
		EXPECT_EQ(expr->kind, ExprKind::Bin);
		auto binExpr = std::static_pointer_cast<BinExpr>(expr);
		auto lhs = binExpr->lhs;
		auto rhs = binExpr->rhs;
		EXPECT_EQ(lhs->kind, ExprKind::Vec);
		EXPECT_EQ(rhs->kind, ExprKind::Vec);
		EXPECT_EQ(binExpr->op, BinOp::Add);

		auto lhsVec = std::static_pointer_cast<VecExpr>(lhs);
		std::vector<float> exp = { 1, 2, 3 };
		EXPECT_EQ(lhsVec->vec, exp);

		auto rhsVec = std::static_pointer_cast<VecExpr>(rhs);
		exp = { 4, 5, 6 };
		EXPECT_EQ(rhsVec->vec, exp);
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}

// Test primitives
TEST(UWotM8, evalNum) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("1");
	EXPECT_EQ(val, "1");
	val = uwotm8.interpret("0.5");
	EXPECT_EQ(val, "0.5");

	val = uwotm8.interpret("-2");
	EXPECT_EQ(val, "-2");

	val = uwotm8.interpret("2.5");
	EXPECT_EQ(val, "2.5");

	val = uwotm8.interpret("-5.1234");
	EXPECT_EQ(val, "-5.1234");
}

// Add tests
TEST(UWotM8, evalVec) {
	UWotM8 uwotm8;
	//auto val = uwotm8.interpret("1 2 3 4 5");
	//EXPECT_EQ(val, "1 2 3 4 5");
	
	auto val = uwotm8.interpret("1 2.5 -3 -4.5 5.1234");
	EXPECT_EQ(val, "1 2.5 -3 -4.5 5.1234");

	//val = uwotm8.interpret("1 22 333 4444 55555");
	//EXPECT_EQ(val, "1 22 333 4444 55555");
}

// Add tests
TEST(UWotM8, evalAddNumNum) {
	UWotM8 uwotm8;		
	auto val = uwotm8.interpret("1+4");
	EXPECT_EQ(val, "5");	
}

TEST(UWotM8, evalAddNumVec) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("1+1 2 3 4");
	EXPECT_EQ(val, "2 3 4 5");
}

TEST(UWotM8, evalAddVecNum) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("1 2 3 4+1");
	EXPECT_EQ(val, "2 3 4 5");
}

TEST(UWotM8, evalAddVecVec) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("1 2 3 + 1 1 1");
	EXPECT_EQ(val, "2 3 4");
}

//Sub tests
TEST(UWotM8, evalSubNumNum) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("1-4");
	EXPECT_EQ(val, "-3");
	val = uwotm8.interpret("4-4");
	EXPECT_EQ(val, "0");
	val = uwotm8.interpret("10-4");
	EXPECT_EQ(val, "6");
}

TEST(UWotM8, evalSubNumVec) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("1+1 2 3 4");
	EXPECT_EQ(val, "2 3 4 5");
}

TEST(UWotM8, evalSubVecNum) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("1 2 3 4+1");
	EXPECT_EQ(val, "2 3 4 5");
}

TEST(UWotM8, evalSubVecVec) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("1 2 3 + 1 1 1");
	EXPECT_EQ(val, "2 3 4");
}

TEST(UWotM8, evalSumVec) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("\\+1 2 3");
	EXPECT_EQ(val, "6");
}

TEST(UWotM8, evalSumsVecs) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("/+1 2 3");
	EXPECT_EQ(val, "1 3 6");
}

TEST(UWotM8, evalAddSumSumsVecs) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("/+1 2 3+\\+1 2 3");
	EXPECT_EQ(val, "7 9 12");
}

TEST(UWotM8, evalMulNumNum) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("2*3");
	EXPECT_EQ(val, "6");
}

TEST(UWotM8, evalMulNumVec) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("2*3 4 5");
	EXPECT_EQ(val, "6 8 10");
}

TEST(UWotM8, evalMulVecNum) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("3 4 5*2");
	EXPECT_EQ(val, "6 8 10");
}

TEST(UWotM8, evalMulVecVec) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("1 2 3*2 2 2");
	EXPECT_EQ(val, "2 4 6");
}

TEST(UWotM8, evalDivNumVec) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("1 2 4 8/2");
	EXPECT_EQ(val, "0.5 1 2 4");
}

TEST(UWotM8, evalDivVecNum) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("2/1 2 4 8");
	EXPECT_EQ(val, "2 1 0.5 0.25");
}

TEST(UWotM8, evalDivVecVec) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("8 8 8 8/1 2 4 8");
	EXPECT_EQ(val, "8 4 2 1");
}

/*
TEST(UWotM8, evalMulNumVec) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("2*3 4 5");
	EXPECT_EQ(val, "6 8 10");
}

TEST(UWotM8, evalMulVecNum) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("3 4 5*2");
	EXPECT_EQ(val, "6 8 10");
}

TEST(UWotM8, evalMulVecVec) {
	UWotM8 uwotm8;
	auto val = uwotm8.interpret("1 2 3*2 2 2");
	EXPECT_EQ(val, "2 4 6");
}
*/