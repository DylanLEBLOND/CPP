#include <Snake.class.hpp>

/*
 * Constructors
 */
Snake::Snake (void) : _currrentSize (3), _canPassThroughWall (true)
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
	: _canPassThroughWall (canPassThroughWall)
{
	t_cell cur_cell;
	int i;

	if (initSize > 100 || (int)(initPosX - initSize) < 0)
	{
		//THOW EXCEPTION HERE
		exit (0);
	}

	this->_snameCells = std::list<t_cell> ();

	cur_cell.positionX = initPosX;
	cur_cell.positionY = initPosY;
	this->_snameCells.push_front (cur_cell);

	for (i = 1; i < initSize; i++)
	{
		cur_cell.positionX = initPosX - i;
		this->_snameCells.push_back (cur_cell);
	}

	this->_currrentSize = initSize;
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
Snake		&Snake::operator=(Snake const &src)
{
	this->_x = src.getPositionX();
	this->_y = src.getPositionY();

	return *this;
}

/*
 * Getter
 */
int			Snake::getPositionX (void) const
{
	return this->_x;
}

int			Snake::getPositionY (void) const
{
	return this->_y;
}

/*
 * Private
 */

/*
 * Public
 */
void		Snake::passThroughWall (bool active)
{
	this->_canPassThroughWall = active;
}

void		Snake::moveLeft (void)
{
	this->_x--;
}

void		Snake::moveRight (void)
{
	this->_x++;
}

void		Snake::moveUp (void)
{
	this->_y--;
}

void		Snake::moveDown (void)
{
	this->_y++;
}
