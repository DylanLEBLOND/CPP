#include <Snake.class.hpp>

/*
 * Constructors
 */
Snake::Snake (void) : _currentDirection (eSnakeDirection::East), _canPassThroughWall (true), _mapSize (400), _eatCounter (0), _isAlive (true)
{
	t_cell cur_cell;

	this->_snakeCells = std::list<t_cell> ();

	cur_cell.positionX = 0;
	cur_cell.positionY = 0;
	this->_snakeCells.push_front (cur_cell);

	cur_cell.positionX = 1;
	cur_cell.positionY = 0;
	this->_snakeCells.push_front (cur_cell);

	cur_cell.positionX = 2;
	cur_cell.positionY = 0;
	this->_snakeCells.push_front (cur_cell);
}

Snake::Snake (unsigned int initPosX, unsigned int initPosY, unsigned int initSize, bool canPassThroughWall)
	: _currentDirection (eSnakeDirection::East), _canPassThroughWall (canPassThroughWall), _mapSize (400), _eatCounter (0), _isAlive (true)
{
	t_cell cur_cell;
	unsigned int i;

	if (initSize > 100 || (int)(initPosX - initSize) < 0)
	{
		//THOW EXCEPTION HERE
		exit (0);
	}

	this->_snakeCells = std::list<t_cell> ();

	cur_cell.positionX = initPosX;
	cur_cell.positionY = initPosY;
	this->_snakeCells.push_front (cur_cell);

	for (i = 1; i < initSize; i++)
	{
		cur_cell.positionX = initPosX - i;
		this->_snakeCells.push_back (cur_cell);
	}
}

Snake::Snake (Snake const &src)
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
Snake					&Snake::operator= (Snake const &src)
{
	this->_snakeCells = src.getSnakeCells ();
	this->_currentDirection = src.getCurrentDirection ();
	this->_canPassThroughWall = src.getCanPassThroughWall ();
	this->_mapSize = src.getMapSize ();
	this->_eatCounter = 0;		/* always start with a eatCounter of 0 */
	this->_isAlive = src.getIsAlive ();

	return *this;
}

/*
 * Getter
 */
bool					Snake::getIsAlive (void) const
{
	return this->_isAlive;
}

std::list<t_cell>		Snake::getSnakeCells (void) const
{
	return this->_snakeCells;
}

eSnakeDirection			Snake::getCurrentDirection (void) const
{
	return this->_currentDirection;
}

bool					Snake::getCanPassThroughWall (void) const
{
	return this->_canPassThroughWall;
}

unsigned int			Snake::getMapSize (void) const
{
	return this->_mapSize;
}

/*
 * Setter
 */
void					Snake::setMapSize (unsigned int newSize)
{
	if (! this->_isAlive)
		return;

	this->_mapSize = newSize;
}

/*
 * Private
 */

/*
 * Public
 */
void					Snake::passThroughWall (bool active)
{
	if (! this->_isAlive)
		return;

	this->_canPassThroughWall = active;
}

void					Snake::eat (int value)
{
	if (! this->_isAlive)
		return;

	this->_eatCounter += value;
}

void					Snake::goLeft (void)
{
	if (! this->_isAlive)
		return;

	if (this->_currentDirection == eSnakeDirection::East)
		return;		/* cannot turn around */

	this->_currentDirection = eSnakeDirection::West;
}

void					Snake::goRight (void)
{
	if (! this->_isAlive)
		return;

	if (this->_currentDirection == eSnakeDirection::West)
		return;		/* cannot turn around */

	this->_currentDirection = eSnakeDirection::East;
}

void					Snake::goUp (void)
{
	if (! this->_isAlive)
		return;

	if (this->_currentDirection == eSnakeDirection::South)
		return;		/* cannot turn around */

	this->_currentDirection = eSnakeDirection::North;
}

void					Snake::goDown (void)
{
	if (! this->_isAlive)
		return;

	if (this->_currentDirection == eSnakeDirection::North)
		return;		/* cannot turn around */

	this->_currentDirection = eSnakeDirection::South;
}

void					Snake::moveStraight (void)
{
	std::list<t_cell>::iterator it;
	t_cell current_head;
	t_cell new_head;

	if (! this->_isAlive)
		return;

	current_head = this->_snakeCells.front ();
	switch (this->_currentDirection)
	{
		case eSnakeDirection::West:
			new_head.positionX = current_head.positionX - 1;
			new_head.positionY = current_head.positionY;
			if (this->_canPassThroughWall && new_head.positionX < 0)
				new_head.positionX = this->_mapSize - 1;
			break;
		case eSnakeDirection::East:
			new_head.positionX = current_head.positionX + 1;
			new_head.positionY = current_head.positionY;
			if (this->_canPassThroughWall && new_head.positionX >= (int)this->_mapSize)
				new_head.positionX = 0;
			break;
		case eSnakeDirection::North:
			new_head.positionX = current_head.positionX;
			new_head.positionY = current_head.positionY - 1;
			if (this->_canPassThroughWall && new_head.positionY < 0)
				new_head.positionY = this->_mapSize - 1;
			break;
		case eSnakeDirection::South:
			new_head.positionX = current_head.positionX;
			new_head.positionY = current_head.positionY + 1;
			if (this->_canPassThroughWall && new_head.positionY >= (int)this->_mapSize)
				new_head.positionY = 0;
			break;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	it = std::find (this->_snakeCells.begin(), this->_snakeCells.end(), new_head);
	if (it != this->_snakeCells.end())
	{
		/* new_head match another cell, which mean that the snake eat himself */
		this->_isAlive = false;
		return;
	}

	this->_snakeCells.push_front (new_head);

	if (this->_eatCounter > 0)
		this->_eatCounter--;
	else
		this->_snakeCells.pop_back ();
}
