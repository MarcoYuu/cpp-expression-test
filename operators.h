#pragma once

#include "expression.h"

class Add :public Operator{
public:
	Add(const ExpressionPointer lhs, const ExpressionPointer rhs)
		:Operator(lhs, rhs)
	{}
	~Add(){}

	double evaluate(double x) const{
		return this->left()->evaluate(x)+this->right()->evaluate(x);
	}

	static const ExpressionPointer create(const ExpressionPointer lhs, const ExpressionPointer rhs){
		return ExpressionPointer(new Add(lhs,rhs));
	}
};

class Subtract :public Operator{
public:
	Subtract(const ExpressionPointer lhs, const ExpressionPointer rhs)
		:Operator(lhs, rhs)
	{}
	~Subtract(){}

	double evaluate(double x) const{
		return this->left()->evaluate(x)-this->right()->evaluate(x);
	}

	static const ExpressionPointer create(const ExpressionPointer lhs, const ExpressionPointer rhs){
		return ExpressionPointer(new Subtract(lhs,rhs));
	}
};

class Multiply :public Operator{
public:
	Multiply(const ExpressionPointer lhs, const ExpressionPointer rhs)
		:Operator(lhs, rhs)
	{}
	~Multiply(){}

	double evaluate(double x) const{
		return this->left()->evaluate(x)*this->right()->evaluate(x);
	}

	static const ExpressionPointer create(const ExpressionPointer lhs, const ExpressionPointer rhs){
		return ExpressionPointer(new Multiply(lhs,rhs));
	}
};

class Divide :public Operator{
public:
	Divide(const ExpressionPointer lhs, const ExpressionPointer rhs)
		:Operator(lhs, rhs)
	{}
	~Divide(){}

	double evaluate(double x) const{
		return this->left()->evaluate(x)/this->right()->evaluate(x);
	}

	static const ExpressionPointer create(const ExpressionPointer lhs, const ExpressionPointer rhs){
		return ExpressionPointer(new Divide(lhs,rhs));
	}
};