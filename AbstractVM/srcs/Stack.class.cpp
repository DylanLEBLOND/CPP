#include "Stack.class.hpp"

/*
** Constructors
*/
Stack::Stack ()
{
	this->_stack = new std::vector<Operand> ();
}

Stack::Stack (Stack const &src)
{
	*this = src;
}

/*
** Destructors
*/
Stack::~Stack() {}

/*
** Operator "=" Overload
*/
Stack	&Stack::operator=(Stack const &src)
{
	this->_stack = src.getStack();

	return *this;
}

/*
** Public
*/

std::vector<Operand> const	*Stack::getStack() const
{
	return &this->_stack;
}

bool	Stack::isEmpty()
{
	return this->_stack.empty();
}

void	Stack::push(Operand const &elem)
{
	this->_stack.push_back(elem);
}
