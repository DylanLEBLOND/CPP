#include <Operand.class.hpp>


int main ()
{
	try
	{
		float d = 0.00000000000000000000000000000000000001f + 0.00000000000000000000000000000000000001f;
//		float d = 0.00000000000000000000000000000000000000001f / 100000000000000000000000.0f;
		std::cout << (d == 0) << std::endl;

//		Operand a (eOperandType::Float, "0.000000000000000000000000000000000000012");
		Operand a (eOperandType::Float, "0.00001");
//		Operand a (eOperandType::Float, "15.0000000000000000001");
		std::cout << "A valid = " << a.toString() << std::endl;
//		Operand b (eOperandType::Float, "0.000000000000000000000000000000000000012");
//		Operand b (eOperandType::Float, "0.0000000009000000000");
//		Operand b (eOperandType::Float, "5.0002");
		float max = FLT_MAX - 10;
		Operand b (eOperandType::Float, std::to_string(max / 1.5));
		std::cout << "B valid = " << b.toString() << std::endl;
		std::cout << "  Min   = " << std::fixed << std::setprecision (38) << FLT_MIN << std::endl;
		Operand add (*(a + b));
		Operand sum (*(a - b));
		Operand mul (*(a * b));
		Operand div (*(a / b));
		Operand mod (*(a % b));

		std::cout << std::endl << a.toString() << " + " << b.toString() << std::endl << "  Add   = " << add.toString() << std::endl;
		std::cout << std::endl << a.toString() << " - " << b.toString() << std::endl << "  Sum   = " << sum.toString() << std::endl;
		std::cout << std::endl << a.toString() << " * " << b.toString() << std::endl << "  Mul   = " << mul.toString() << std::endl;
		std::cout << std::endl << a.toString() << " / " << b.toString() << std::endl << "  Div   = " << div.toString() << std::endl;
		std::cout << std::endl << a.toString() << " % " << b.toString() << std::endl << "  Mod   = " << div.toString() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() <<std::endl;
	}

	return 0;
}
