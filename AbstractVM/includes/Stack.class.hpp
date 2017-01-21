#ifndef STACK_CLASS_HPP
# define STACK_CLASS_HPP

# include <Operand.class.hpp>
# include <Exceptions.hpp>
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

	bool			isEmpty(void) const;
	void			push(Operand const &elem);
	void			pop();
	std::string		dump() const;
	void			assert(std::string const &elem) const;
	void			add();
	void			sub();
	void			mul();
	void			div();
	void			mod();
	char			print() const;
};

#endif /* STACK_CLASS_HPP */
