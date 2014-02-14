#pragma once

#include <cmath>
#include "expression.h"

class Value :public Function{
protected:
	class ZeroExpression :public Expression{
	public: 
		double evaluate(double x) const{return 0.0;}
	};
	static const ExpressionPointer zero_expression;

public:
	Value():Function(zero_expression){}
	~Value(){}
};

class Constant :public Value{
private:
	const double value_;

public:
	Constant(double value):Value(),value_(value){}
	~Constant(){}

	double evaluate(double x) const{
		return value_;
	}

	static const ExpressionPointer E;
	static const ExpressionPointer PI;

	static const ExpressionPointer create(double x){
		return ExpressionPointer(new Constant(x));
	}
};

class Variable :public Value{
public:
	Variable():Value(){}
	~Variable(){}

	double evaluate(double x) const{
		return x;
	}

	static const ExpressionPointer create(){
		return ExpressionPointer(new Variable());
	}
};

class Sin :public Function{
public:
	Sin(const ExpressionPointer argument):Function(argument){}
	~Sin(){}

	double evaluate(double x) const{
		return sin(this->argument()->evaluate(x));
	}

	static const ExpressionPointer create(const ExpressionPointer argument){
		return ExpressionPointer(new Sin(argument));
	}
};

class Cos :public Function{
public:
	Cos(const ExpressionPointer argument):Function(argument){}
	~Cos(){}

	double evaluate(double x) const{
		return cos(this->argument()->evaluate(x));
	}

	static const ExpressionPointer create(const ExpressionPointer argument){
		return ExpressionPointer(new Cos(argument));
	}
};

class Tan :public Function{
public:
	Tan(const ExpressionPointer argument):Function(argument){}
	~Tan(){}

	double evaluate(double x) const{
		return tan(this->argument()->evaluate(x));
	}

	static const ExpressionPointer create(const ExpressionPointer argument){
		return ExpressionPointer(new Tan(argument));
	}
};

class Exp :public Function{
public:
	Exp(const ExpressionPointer argument):Function(argument){}
	~Exp(){}

	double evaluate(double x) const{
		return exp(this->argument()->evaluate(x));
	}

	static const ExpressionPointer create(const ExpressionPointer argument){
		return ExpressionPointer(new Exp(argument));
	}
};

class Power :public Function2{
public:
	Power(const ExpressionPointer base, const ExpressionPointer exponent)
		:Function2(base,exponent){}
	~Power(){}

	double evaluate(double x) const{
		return pow(this->argument()->evaluate(x),this->argument2()->evaluate(x));
	}

	static const ExpressionPointer create(const ExpressionPointer base, const ExpressionPointer exponent){
		return ExpressionPointer(new Power(base,exponent));
	}
};

class Log10 :public Function{
public:
	Log10(const ExpressionPointer argument):Function(argument){}
	~Log10(){}

	double evaluate(double x) const{
		return log10(this->argument()->evaluate(x));
	}

	static const ExpressionPointer create(const ExpressionPointer argument){
		return ExpressionPointer(new Log10(argument));
	}
};

class LogE :public Function{
public:
	LogE(const ExpressionPointer argument):Function(argument){}
	~LogE(){}

	double evaluate(double x) const{
		return log(this->argument()->evaluate(x));
	}

	static const ExpressionPointer create(const ExpressionPointer argument){
		return ExpressionPointer(new LogE(argument));
	}
};

class Log :public Function2{
public:
	Log(const ExpressionPointer base, const ExpressionPointer antilogarithm)
		:Function2(base,antilogarithm){}
	~Log(){}

	double evaluate(double x) const{
		return log(this->argument2()->evaluate(x))/log(this->argument()->evaluate(x));
	}

	static const ExpressionPointer create(const ExpressionPointer base, const ExpressionPointer antilogarithm){
		return ExpressionPointer(new Log(base,antilogarithm));
	}
};

class Root :public Function{
public:
	Root(const ExpressionPointer argument):Function(argument){}
	~Root(){}

	double evaluate(double x) const{
		return sqrt(this->argument()->evaluate(x));
	}

	static const ExpressionPointer create(const ExpressionPointer argument){
		return ExpressionPointer(new Root(argument));
	}
};