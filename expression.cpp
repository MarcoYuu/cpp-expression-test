#include "expression.h"
#include <sstream>
#include <cctype>

//---------------------------------------------------------------------------
//Ž®‰ðÍ
//---------------------------------------------------------------------------
ExpressionParser::ExpressionParser()
	:expression_()
{
}
ExpressionParser::ExpressionParser(const std::string &expression)
	:expression_(expression)
{
}

void ExpressionParser::setExpression(const std::string &expression){
	expression_ =expression;
}
const ExpressionPointer ExpressionParser::parse() const{
	int index =0;
	return analyzeAddition(index);
}

const ExpressionPointer ExpressionParser::analyzeAddition(int &index) const{
	ExpressionPointer expr =analyzeMultiplication(index);
	if(index>expression_.size())
		return expr;
	for(;;){
		if(expression_[index] == '+'){
			++index;
			expr =Add::create(expr,analyzeMultiplication(index));
		}else if(expression_[index] == '-') {
			++index;
			expr =Subtract::create(expr,analyzeMultiplication(index));
		}else{
			break;
		}
	}
	return expr;
}
const ExpressionPointer ExpressionParser::analyzeMultiplication(int &index) const{
	ExpressionPointer expr = analyzeBracket(index);
	if(index>expression_.size())
		return expr;
	for(;;){ 
		if(expression_[index] == '*') {
			++index;
			expr =Multiply::create(expr,analyzeMultiplication(index));
		}else if(expression_[index] == '/') {
			++index;
			expr =Divide::create(expr,analyzeMultiplication(index));
		}else{
			break;
		}
	}
	return expr;
}
const ExpressionPointer ExpressionParser::analyzeBracket(int &index) const{
	if(expression_[index] == '('){
		++index;
		ExpressionPointer expr =analyzeAddition(index);
		if(expression_[index] != ')'){
			return ExpressionPointer(NULL);
		}
		if(index>expression_.size())
			return expr;

		++index;

		if(expression_[index] == '^'){
			++index;
			ExpressionPointer expr2 =analyzeAddition(index);
			return Power::create(expr,expr2);
		}else{
			return expr;
		}
	}else{
		ExpressionPointer expr =analyzeFunction(index);

		if(expression_[index] == '^'){
			++index;
			ExpressionPointer expr2 =analyzeAddition(index);
			return Power::create(expr,expr2);
		}else{
			return expr;
		}
	}
}
const ExpressionPointer ExpressionParser::analyzeFunction(int &index) const{
	if(expression_[index] < UCHAR_MAX && expression_[index] > 0 &&isdigit(expression_[index])){

		std::istringstream sub_expr(expression_.substr(index));
		double constant;
		sub_expr >> constant;
		index +=static_cast<int>(sub_expr.tellg());

		return Constant::create(constant);

	}else if(expression_.find("ƒÎ",index) == index){
		index+=2;
		return Constant::PI;
	}else{
		switch(expression_[index])
		{
		case 'E':{++index;return Constant::E;}
		case 's':{return createTrigFunc<Sin>(index);}//sin
		case 'c':{return createTrigFunc<Cos>(index);}//cos
		case 't':{return createTrigFunc<Tan>(index);}//tan
		case 'l':{return createLogFunc(index);}//ln,log10
		case 'x':{++index;return Variable::create();}//•Ï”
		case 'e':{
			index+=3;
			ExpressionPointer expr =analyzeBracket(index);
			return Exp::create(expr);
		}//exp
		default:{return ExpressionPointer(NULL);}
		}
	}
}

const ExpressionPointer ExpressionParser::createLogFunc(int &index) const{
	++index;
	if(expression_[index] == 'n'){
		++index;
		ExpressionPointer expr =analyzeBracket(index);
		return LogE::create(expr);

	}else if(expression_[index] == 'o'){
		index+=2;
		std::istringstream sub_expr(expression_.substr(index));
		double constant;
		sub_expr >> constant;
		index +=static_cast<int>(sub_expr.tellg());

		ExpressionPointer expr =analyzeBracket(index);

		if(constant == 10.0){
			return Log10::create(expr);
		}else{
			return Log::create(Constant::create(constant),expr);
		}
	}else{
		return ExpressionPointer(NULL);
	}
}