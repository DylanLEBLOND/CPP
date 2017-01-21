#include <Operand.class.hpp>
#include <Stack.class.hpp>


int main ()
{
	try
	{
		Stack stack;

		stack.push (Operand (eOperandType::Float, "0.00001"));
		stack.push (Operand (eOperandType::Float, "5.0002"));
		std::cout << "Stack Dump:\n" << stack.dump();
		stack.add();
		std::cout << "Stack Dump:\n" << stack.dump();
		stack.push (Operand (eOperandType::Int8, "97"));
		std::cout << "Stack Dump:\n" << stack.dump();
		std::cout << "Stack Print = \"" << stack.print() << "\"" << std::endl;
		stack.pop();
		std::cout << "Stack Dump:\n" << stack.dump();
		stack.assert("5.00021");
		stack.pop();
		std::cout << "Stack Dump:\n" << stack.dump();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() <<std::endl;
	}

	return 0;
}
