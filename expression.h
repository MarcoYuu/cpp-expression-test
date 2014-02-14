#pragma once

#include <memory>
#include <string>

class Expression;
class Operator;
class Function;

class ExpressionParser;

typedef std::shared_ptr<Expression> ExpressionPointer;

//---------------------------------------------------------------------------
//éÆ
//---------------------------------------------------------------------------
class Expression{
public:
	Expression(){}
	virtual ~Expression(){}

	virtual double evaluate(double x) const=0;
};

//---------------------------------------------------------------------------
//ä÷êî
//---------------------------------------------------------------------------
class Function :public Expression{
private:
	const ExpressionPointer argument_;
protected:
	const ExpressionPointer argument() const{return argument_;}
public:
	Function(const ExpressionPointer argument):argument_(argument){}
	virtual ~Function(){}

	double operator()(double x) const{return evaluate(x);}
};

class Function2 :public Function{
private:
	const ExpressionPointer argument2_;
protected:
	const ExpressionPointer argument2() const{return argument2_;}
public:
	Function2(const ExpressionPointer argument1,const ExpressionPointer argument2)
		:Function(argument1)
		,argument2_(argument2){}
	virtual ~Function2(){}
};

//---------------------------------------------------------------------------
//ââéZéq
//---------------------------------------------------------------------------
class Operator :public Expression{
private:
	const ExpressionPointer lhs_;
	const ExpressionPointer rhs_;

protected:
	const ExpressionPointer left() const{return lhs_;}
	const ExpressionPointer right() const{return rhs_;}

public:
	Operator(const ExpressionPointer lhs, const ExpressionPointer rhs)
		:lhs_(lhs),rhs_(rhs){}
	virtual ~Operator(){}
};

//---------------------------------------------------------------------------
//éÆâêÕ
//---------------------------------------------------------------------------
class ExpressionParser{
public:
	ExpressionParser();
	ExpressionParser(const std::string &expression);

	void setExpression(const std::string &expression);
	const ExpressionPointer parse() const;

private:
	const ExpressionPointer analyzeAddition(int &index) const;
	const ExpressionPointer analyzeMultiplication(int &index) const;
	const ExpressionPointer analyzeBracket(int &index) const;
	const ExpressionPointer analyzeFunction(int &index) const;

	const ExpressionPointer createLogFunc(int &index) const;
	template<class T> 
	const ExpressionPointer createTrigFunc(int &index) const{
		index+=3;
		if(expression_[index] == '^'){
			++index;
			ExpressionPointer expr2 =analyzeAddition(index);
			ExpressionPointer expr =analyzeBracket(index);
			return Power::create(T::create(expr),expr2);
		}else{
			ExpressionPointer expr =analyzeBracket(index);
			return T::create(expr);
		}
	}
	
	std::string expression_;
};

#include "operators.h"
#include "functions.h"
