#ifndef STACK_CLASS_HPP
# define STACK_CLASS_HPP

# include "Operand.class.hpp"
# include "OperandFactory.class.hpp"
# include <vector>

class Stack
{
private:

	std::vector<Operand> _stack;

	Stack(Stack const &src);
	Stack &operator=(Stack const &src);

public:

	Stack(void);
	~Stack(void);

	std::vector<Operand> const *getStack() const;

	bool isEmpty(void);
	void push(std::string const &elem);
};

#endif /* IOPERAND_CLASS_HPP */
