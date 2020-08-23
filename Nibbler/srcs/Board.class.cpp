#include <Board.class.hpp>

/*
 * Constructors
 */
Board::Board (void) : _width (0u), _height (0u),_multiPlayer (false), _snakeP1 (NULL), _snakeP2 (NULL) {}

Board::Board (Board const &src)
{
	*this = src;
}

/*
 * Destructor
 */
Board::~Board (void) {}

/*
 * Operator "=" Overload
 */
Board				&Board::operator= (Board const &src)
{
	this->_width = src.getWidth();
	this->_height = src.getHeight();
	this->_multiPlayer = src.getMultiPlayer();

	return *this;
}

/*
 * Getter
 */
unsigned int		Board::getWidth (void) const
{
	return this->_width;
}

unsigned int		Board::getHeight (void) const
{
	return this->_height;
}

bool				Board::getMultiPlayer (void) const
{
	return this->_multiPlayer;
}

/*
 * Private
 */

/*
 * Public
 */
void				Board::initBoard (unsigned int width, unsigned int height, bool multiPlayer)
{
	if (width < 30 || 100 < width)
	{
		std::string error_message = "Board::initBoard: width < 30 || width > 100 (";
		error_message += std::to_string (width);
		error_message += ")";

		throw InvalidArgumentException (error_message.c_str());
	}

	if (height < 30 || 100 < height)
	{
		std::string error_message = "Board::initBoard: height < 30 || height > 100 (";
		error_message += std::to_string (height);
		error_message += ")";

		throw InvalidArgumentException (error_message.c_str());
	}

	this->_width = width;
	this->_height = height;
	this->_multiPlayer = multiPlayer;
}

void				Board::initPlayers (Snake *snakeP1, Snake *snakeP2)
{
	if (! snakeP1)
	{
		throw InvalidArgumentException ("Board::initPlayers: snakeP1 == null");
	}
	this->_snakeP1 = snakeP1;
	this->_snakeP1->setMapWidth (this->_width);
	this->_snakeP1->setMapHeight (this->_height);

	if (! this->_multiPlayer && snakeP2)
	{
		throw InvalidArgumentException ("Board::initPlayers: SinglePlayer board but snakeP2 != null");
	}

	if (this->_multiPlayer)
	{
		if (! snakeP2)
		{
			throw InvalidArgumentException ("Board::initPlayers: MultiPlayer board but snakeP2 == null");
		}
		this->_snakeP2 = snakeP2;
		this->_snakeP2->setMapWidth (this->_width);
		this->_snakeP2->setMapHeight (this->_height);
	}
}

void				Board::runTurn (void)
{
	this->_snakeP1->moveStraight();
	if (this->_multiPlayer)
		this->_snakeP2->moveStraight();
}

bool				Board::snakesAreAlive (void)
{
	if (! this->_snakeP1->getIsAlive())
		return false;

	if (this->_multiPlayer && ! this->_snakeP2->getIsAlive())
		return false;

	return true;
}
