#include <Stack.class.hpp>

/*
** Constructors
*/
Stack::Stack ()
{
	this->_stack = std::vector<IOperand const *> ();
}

Stack::Stack (Stack const &src)
{
	*this = src;
}

/*
** Destructors
*/
Stack::~Stack()
{
	size_t i;

	for (i = this->_stack.size() - 1; !this->_stack.empty(); i--)
	{
		delete this->_stack[i];
		this->_stack.pop_back();
	}
}

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

std::vector<IOperand const *> const	*Stack::getStack() const
{
	return &this->_stack;
}

bool	Stack::isEmpty() const
{
	return this->_stack.empty();
}

void	Stack::push(eOperandType operand, std::string const &value)
{
	IOperand const *pushOp = Operand::Get()->createOperand(operand, value);

	this->_stack.push_back(pushOp);
}

void	Stack::pop()
{
	if (this->_stack.size() < 1)
		throw StackException ("Pop on empty stack");

	delete this->_stack.back();
	this->_stack.pop_back();
}

std::string		Stack::dump() const
{
	if (this->_stack.size() < 1)
		throw StackException ("Dump on empty stack");

	std::string mess;
	IOperand const *op;
	size_t i;

	for (i = this->_stack.size() - 1; i > 0; i--)
	{
		op = this->_stack[i];
		mess = mess + ((*op).toString()) + "\n";
	}
	op = this->_stack[0];
	mess = mess + ((*op).toString()) + "\n";

	return mess;
}

void			Stack::assert(eOperandType operand, std::string const &value) const
{
	if (this->_stack.size() < 1)
		throw StackException ("Assert on empty stack");

	IOperand const *op = this->_stack[this->_stack.size() - 1];
	IOperand const *assertOp =  Operand::Get()->createOperand(operand, value);

	if ((*op).getType() != (*assertOp).getType() || (*op).toString() != (*assertOp).toString())
		throw StackException ("An assert instruction is not true: " + (*assertOp).toString() + " != " + (*op).toString());

	delete assertOp;
}

void			Stack::add()
{
	if (this->_stack.size() < 2)
		throw StackException ("The stack is composed of strictly less that two values when an arithmetic instruction is executed: Add");

	IOperand const *op  = *(this->_stack[this->_stack.size() - 2]) + *(this->_stack[this->_stack.size() - 1]);

	this->pop();
	this->pop();
	this->_stack.push_back(op);
}

void			Stack::sub()
{
	if (this->_stack.size() < 2)
		throw StackException ("The stack is composed of strictly less that two values when an arithmetic instruction is executed: Sub");

	IOperand const *op  = *(this->_stack[this->_stack.size() - 2]) - *(this->_stack[this->_stack.size() - 1]);

	this->pop();
	this->pop();
	this->_stack.push_back(op);
}

void			Stack::mul()
{
	if (this->_stack.size() < 2)
		throw StackException ("The stack is composed of strictly less that two values when an arithmetic instruction is executed: Mul");

	IOperand const *op = *(this->_stack[this->_stack.size() - 2]) * *(this->_stack[this->_stack.size() - 1]);

	this->pop();
	this->pop();
	this->_stack.push_back(op);
}

void			Stack::div()
{
	if (this->_stack.size() < 2)
		throw StackException ("The stack is composed of strictly less that two values when an arithmetic instruction is executed: Div");

	IOperand const *op = *(this->_stack[this->_stack.size() - 2]) / *(this->_stack[this->_stack.size() - 1]);

	this->pop();
	this->pop();
	this->_stack.push_back(op);
}

void			Stack::mod()
{
	if (this->_stack.size() < 2)
		throw StackException ("The stack is composed of strictly less that two values when an arithmetic instruction is executed: Mod");

	IOperand const *op = *(this->_stack[this->_stack.size() - 2]) % *(this->_stack[this->_stack.size() - 1]);

	this->pop();
	this->pop();
	this->_stack.push_back(op);
}

char			Stack::print() const
{
	if (this->_stack.size() < 1)
		throw StackException ("Print on empty stack");

	IOperand const *op = this->_stack[this->_stack.size() - 1];

	if ((*op).getType() != eOperandType::Int8)
		throw StackException ("Print instruction not true:" + (*op).toString() + " is not a Int8");

	return std::stoi ((*op).toString());
}


