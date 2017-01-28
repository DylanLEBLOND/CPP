#ifndef STACK_CLASS_HPP
# define STACK_CLASS_HPP

# include <Operand.class.hpp>
# include <Exceptions.hpp>
# include <vector>

class Stack
{
private:

	std::vector<IOperand const *> _stack;

	Stack(Stack const &src);
	Stack &operator=(Stack const &src);

public:

	Stack(void);
	~Stack(void);

	std::vector<IOperand const *> const *getStack() const;

	bool			isEmpty(void) const;
	void			push(eOperandType operand, std::string const &value);
	void			pop();
	std::string		dump() const;
	void			assert(eOperandType operand, std::string const &value) const;
	void			add();
	void			sub();
	void			mul();
	void			div();
	void			mod();
	char			print() const;
};

#endif /* STACK_CLASS_HPP */
