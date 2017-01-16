#include "Operand.class.hpp"
#include <iostream>

int main ()
{
	try
	{
		float d = 0.000000000000000000000000000000001f / 0.000000000000000000000000000000001f;
//		float d = 0.00000000000000000000000000000000000000001f / 100000000000000000000000.0f;
		std::cout << (d == 0) << std::endl;

		Operand a (eOperandType::Float, "0.000000000000000000000000000000001");
		std::cout << "A valid" << std::endl;
		Operand b (eOperandType::Float, "0.000000000000000000000000000000001");
//		Operand b (eOperandType::Float, "100000000000000000000000.0");
		std::cout << "B valid" << std::endl;
		Operand c (*(a / b));

		std::cout << std::to_string (FLT_EPSILON) << " = " << stof (std::string ("0.000000000000000000000000000000001"))  << std::endl;

		std::cout << a.toString() << " / " << b.toString() << " = " << c.toString() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() <<std::endl;
	}

	return 0;
}
