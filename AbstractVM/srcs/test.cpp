#include <Operand.class.hpp>
#include <Stack.class.hpp>


int main ()
{
	try
	{
		Stack stack;

		stack.push (eOperandType::Int32, "42");
		std::cout << "Stack Push (Int32, 42)" << std::endl;
		stack.push (eOperandType::Int32, "33");
		std::cout << "Stack Push (Int32, 33)" << std::endl;
		stack.add();
		std::cout << "Stack Add" << std::endl;
		stack.push (eOperandType::Float, "44.55");
		std::cout << "Stack Push (Float, 44.55)" << std::endl;
		stack.mul();
		std::cout << "Stack Mul" << std::endl;
		stack.push (eOperandType::Double, "42.42");
		std::cout << "Stack Push (Double, 42.42)" << std::endl;
		stack.push (eOperandType::Int32, "42");
		std::cout << "Stack Push (Int32, 42)" << std::endl;
		std::cout << "Stack Dump:\n" << stack.dump();
		stack.pop();
		std::cout << "Stack Pop" << std::endl;
		stack.assert(eOperandType::Double, "42.42");
		std::cout << "Stack Assert (Double, 42.42)" << std::endl;

		std::cout << "******** END ********\nStack Dump:\n" << stack.dump();
/*
		stack.push (Operand (eOperandType::Float, "0.00001"));
		std::cout << "Stack Push (Float, 0.00001)" << std::endl;
		stack.push (Operand (eOperandType::Float, "5.0002"));
		std::cout << "Stack Push (Float, 5.0002)" << std::endl;
		std::cout << "Stack Dump:\n" << stack.dump();
		stack.add();
		std::cout << "Stack Add" << std::endl;
		std::cout << "Stack Dump:\n" << stack.dump();
		stack.push (Operand (eOperandType::Int8, "97"));
		std::cout << "Stack Push (Int8, 97)" << std::endl;
		std::cout << "Stack Dump:\n" << stack.dump();
		std::cout << "Stack Print = \"" << stack.print() << "\"" << std::endl;
		stack.pop();
		std::cout << "Stack Pop" << std::endl;
		std::cout << "Stack Dump:\n" << stack.dump();
		stack.assert(Operand (eOperandType::Float, "5.00021"));
		std::cout << "Stack Assert (Float, 5.00021)" << std::endl;
		stack.pop();
		std::cout << "Stack Pop" << std::endl;
		std::cout << "Stack Dump:\n" << stack.dump();
*/
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() <<std::endl;
	}

	return 0;
}
