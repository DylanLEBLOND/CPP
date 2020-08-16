#include <Board.class.hpp>

/*
 * Constructors
 */
Board::Board (void) : _size(20) {}

Board::Board (int size) : _size (size)
{

}

Board::Board(Board const &src)
{
	*this = src;
}

/*
 * Destructor
 */
Board::~Board(void) {}

/*
 * Operator "=" Overload
 */
Board					&Board::operator=(Board const &src)
{
	this->_size = src.getSize();

	return *this;
}

/*
 * Getter
 */
int						Board::getSize(void) const
{
	return this->_size;
}

/*
 * Private
 */

/*
 * Public
 */

