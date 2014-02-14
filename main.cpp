
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <sstream>

#include "expression.h"

using namespace std;

int main(){
	cout << "1+2 =" << Add(Constant::create(1.0),Constant::create(2.0)).evaluate(0.0) <<endl;

	ExpressionPointer e =Add::create(Cos::create(Divide::create(Constant::PI,Constant::create(3.0))),Variable::create());
	for(int i=0;i<10;++i){
		cout << "cos(pi/3)+x =" << e->evaluate(i) <<endl;
	}

	ExpressionParser ep("cos^2(x)");
	ExpressionPointer e2 =ep.parse();
	for(double i=0;i<3.14;i+=0.01){
		cout << "cos^2(x) =" << e2->evaluate(i) <<endl;
	}

	return 0;
}