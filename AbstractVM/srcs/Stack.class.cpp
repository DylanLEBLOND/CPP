#include <Stack.class.hpp>

/*
** Constructors
*/
Stack::Stack ()
{
	this->_stack = std::vector<Operand> ();
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
	this->_stack = *(src.getStack());

	return *this;
}

/*
** Public
*/

std::vector<Operand> const	*Stack::getStack() const
{
	return &this->_stack;
}

bool	Stack::isEmpty() const
{
	return this->_stack.empty();
}

void	Stack::push(Operand const &elem)
{
	this->_stack.push_back(elem);
}

void	Stack::pop()
{
	if (this->_stack.size() < 1)
		throw StackException ("Pop on empty stack");

	this->_stack.pop_back();
}

std::string		Stack::dump() const
{
	if (this->_stack.size() < 1)
		throw StackException ("Dump on empty stack");

	std::string mess;
	Operand const *op;
	size_t i;

	for (i = 0; i < this->_stack.size(); i++)
	{
		op = &this->_stack[i];
		mess = mess + ((*op).toString()) + "\n";
	}

	return mess;
}

void			Stack::assert(std::string const &elem) const
{
	if (this->_stack.size() < 1)
		throw StackException ("Assert on empty stack");

	Operand const *op;

	op = &this->_stack[this->_stack.size() - 1];
	if ((*op).toString() != elem)
		throw StackException ("An assert instruction is not true: " + elem + " != " + (*op).toString());
}

void			Stack::add()
{
	if (this->_stack.size() < 2)
		throw StackException ("The stack is composed of strictly less that two values when an arithmetic instruction is executed: Add");

	Operand op (*(this->_stack[this->_stack.size() - 1] + this->_stack[this->_stack.size() - 2]));

	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(op);
}

void			Stack::sub()
{
	if (this->_stack.size() < 2)
		throw StackException ("The stack is composed of strictly less that two values when an arithmetic instruction is executed: Sub");

	Operand op (*(this->_stack[this->_stack.size() - 1] - this->_stack[this->_stack.size() - 2]));

	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(op);
}

void			Stack::mul()
{
	if (this->_stack.size() < 2)
		throw StackException ("The stack is composed of strictly less that two values when an arithmetic instruction is executed: Mul");

	Operand op (*(this->_stack[this->_stack.size() - 1] * this->_stack[this->_stack.size() - 2]));

	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(op);
}

void			Stack::div()
{
	if (this->_stack.size() < 2)
		throw StackException ("The stack is composed of strictly less that two values when an arithmetic instruction is executed: Div");

	Operand op (*(this->_stack[this->_stack.size() - 1] / this->_stack[this->_stack.size() - 2]));

	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(op);
}

void			Stack::mod()
{
	if (this->_stack.size() < 2)
		throw StackException ("The stack is composed of strictly less that two values when an arithmetic instruction is executed: Mod");

	Operand op (*(this->_stack[this->_stack.size() - 1] % this->_stack[this->_stack.size() - 2]));

	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(op);
}

char			Stack::print() const
{
	if (this->_stack.size() < 1)
		throw StackException ("Print on empty stack");

	Operand const *op = &this->_stack[this->_stack.size() - 1];

	if ((*op).getType() != eOperandType::Int8)
		throw StackException ("Print instruction not true:" + (*op).toString() + " is not a Int8");

	return std::stoi ((*op).toString());
}


