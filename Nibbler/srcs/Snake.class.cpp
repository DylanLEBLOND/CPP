#include <Snake.class.hpp>

/*
 * Constructors
 */
Snake::Snake (void)
	: _currentDirection (eSnakeDirection::East), _canPassThroughWall (true), _mapWidth (0u), _mapHeight (0u), _eatCounter (0), _score (0), _isAlive (true) { }

Snake::Snake (Snake const &src)
{
	*this = src;
}

/*
 * Destructor
 */
Snake::~Snake (void) {}

/*
 * Operator "=" Overload
 */
Snake					&Snake::operator= (Snake const &src)
{
	this->_snakeCells = src.getSnakeCells();
	this->_currentDirection = src.getCurrentDirection();
	this->_canPassThroughWall = src.getCanPassThroughWall();
	this->_mapWidth = src.getMapWidth();
	this->_mapHeight = src.getMapHeight();
	this->_eatCounter = 0;		/* always start with a eatCounter of 0 */
	this->_isAlive = src.getIsAlive();

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

unsigned int			Snake::getMapWidth (void) const
{
	return this->_mapWidth;
}

unsigned int			Snake::getMapHeight (void) const
{
	return this->_mapHeight;
}

unsigned int			Snake::getScore (void) const
{
	return this->_score;
}

/*
 * Setter
 */
void					Snake::setMapWidth (unsigned int newWidth)
{
	if (! this->_isAlive)
		return;

	this->_mapWidth = newWidth;
}

void					Snake::setMapHeight (unsigned int newHeight)
{
	if (! this->_isAlive)
		return;

	this->_mapHeight = newHeight;
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
	this->_score += value;

	std::cout << "Snake current score = " << this->_score << std::endl;
}

void					Snake::dead (void)
{
	if (! this->_isAlive)
		return;

	this->_isAlive = false;
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

	current_head = this->_snakeCells.front();
	switch (this->_currentDirection)
	{
		case eSnakeDirection::West:
			new_head.positionX = current_head.positionX - 1;
			new_head.positionY = current_head.positionY;
			if (this->_canPassThroughWall && new_head.positionX < 0)
				new_head.positionX = this->_mapWidth - 1;
			break;
		case eSnakeDirection::East:
			new_head.positionX = current_head.positionX + 1;
			new_head.positionY = current_head.positionY;
			if (this->_canPassThroughWall && new_head.positionX >= (int)this->_mapWidth)
				new_head.positionX = 0;
			break;
		case eSnakeDirection::North:
			new_head.positionX = current_head.positionX;
			new_head.positionY = current_head.positionY - 1;
			if (this->_canPassThroughWall && new_head.positionY < 0)
				new_head.positionY = this->_mapHeight - 1;
			break;
		case eSnakeDirection::South:
			new_head.positionX = current_head.positionX;
			new_head.positionY = current_head.positionY + 1;
			if (this->_canPassThroughWall && new_head.positionY >= (int)this->_mapHeight)
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
		this->_snakeCells.pop_back();
}

void					Snake::initSnake (unsigned int initPosX, unsigned int initPosY, unsigned int initSize, eSnakeDirection initDirection, bool canPassThroughWall)
{
	t_cell cur_cell;
	unsigned int i;

	if (initSize > 100 || (int)(initPosX - initSize) < 0 || (int)(initPosY - initSize) < 0)
	{
		throw InvalidArgumentException ("Snake::reset: initSize > 100 || initPosX > initSize || initPosY > initSize");
	}

	this->_snakeCells.clear();

	cur_cell.positionX = initPosX;
	cur_cell.positionY = initPosY;
	this->_snakeCells.push_front (cur_cell);

	for (i = 1; i < initSize; i++)
	{
		switch (initDirection)
		{
			case eSnakeDirection::West:
				cur_cell.positionX = initPosX + i;
				this->_snakeCells.push_back (cur_cell);
				break;
			case eSnakeDirection::East:
				cur_cell.positionX = initPosX - i;
				this->_snakeCells.push_back (cur_cell);
				break;
			case eSnakeDirection::North:
				cur_cell.positionY = initPosY + i;
				this->_snakeCells.push_back (cur_cell);
				break;
			case eSnakeDirection::South:
				cur_cell.positionY = initPosY + i;
				this->_snakeCells.push_back (cur_cell);
				break;
			default:
				throw ShouldNeverOccurException (__FILE__, __LINE__);
		}
	}

	this->_currentDirection = initDirection;
	this->_canPassThroughWall = canPassThroughWall;
	this->_mapWidth = 0u;
	this->_mapHeight = 0u;
	this->_eatCounter = 0;
	this->_score = 0;
	this->_isAlive = true;
}
