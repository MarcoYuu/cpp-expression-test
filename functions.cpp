#include "functions.h"

const ExpressionPointer Value::zero_expression(new Value::ZeroExpression());
const ExpressionPointer Constant::E(new Constant(2.71828182845904523536));
const ExpressionPointer Constant::PI(new Constant(3.14159265358979323846));