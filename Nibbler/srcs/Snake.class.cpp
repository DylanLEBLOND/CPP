#include <Snake.class.hpp>

/*
 * Constructors
 */
Snake::Snake (void) {}

Snake::Snake(Snake const &src)
{
	*this = src;
}

/*
 * Destructor
 */
Snake::~Snake(void) {}

/*
 * Operator "=" Overload
 */
Snake					&Snake::operator=(Snake const &src)
{
	(void)src;

	return *this;
}

/*
 * Getter
 */

/*
 * Private
 */

/*
 * Public
 */

