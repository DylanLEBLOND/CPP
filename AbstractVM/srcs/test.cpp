#include <Operand.class.hpp>
#include <Stack.class.hpp>


int main ()
{
	try
	{
		Stack stack;

		stack.push (Operand (eOperandType::Float, "0.00001"));
//		Operand a (eOperandType::Float, "15.0000000000000000001");
//		Operand b (eOperandType::Float, "0.000000000000000000000000000000000000012");
//		Operand b (eOperandType::Float, "0.0000000009000000000");
		stack.push (Operand (eOperandType::Float, "5.0002"));

		std::cout << "Stack Dump:\n" << stack.dump() << std::endl;
		stack.add();
		std::cout << "Stack Dump:\n" << stack.dump() << std::endl;
}
	catch (std::exception &e)
	{
		std::cerr << e.what() <<std::endl;
	}

	return 0;
}
