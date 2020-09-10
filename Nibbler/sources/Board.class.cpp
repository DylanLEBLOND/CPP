#include <Board.class.hpp>

/*
 * Constructors
 */
Board::Board (void)
	: _width (0u), _height (0u), _mapSize (eBonusMapScale::UnknownMapScale), _currentMap (eBoardMaps::UnknownMap),
	  _boardCells (NULL), _boardCompletedScore (0u), _initialized (false),
	  _snakeP1 (NULL), _snakeP2 (NULL), _boardMode (eboadMode::Default), _boardStatus (eBoardStatus::UnknownStatus),
	  _playersInitialized (false) {}

Board::Board (Board const &src)
{
	*this = src;
}

/*
 * Destructor
 */
Board::~Board (void)
{
	if (this->_boardCells)
	{
		delete this->_boardCells;
	}
}

/*
 * Operator "=" Overload
 */
Board								&Board::operator= (Board const &src)
{
	if (src.isInitialized())
	{
		this->initBoard (src.getWidth(), src.getHeight(), src.getBoardMode());
	}

	return *this;
}

/*
 * Getter
 */
unsigned int						Board::getWidth (void) const
{
	return this->_width;
}

unsigned int						Board::getHeight (void) const
{
	return this->_height;
}

std::vector< std::vector<int> >		*Board::getBoardCells (void) const
{
	return this->_boardCells;
}

int									Board::getBoardCompletedScore (void) const
{
	if (this->_boardMode & eboadMode::Endless)
		return -1;

	return this->_boardCompletedScore;
}

eboadMode							Board::getBoardMode (void) const
{
	return this->_boardMode;
}

eBoardStatus						Board::getBoardStatus (void) const
{
	return this->_boardStatus;
}

bool								Board::isInitialized (void) const
{
	return this->_initialized;
}

/*
 * Private
 */
void								Board::loadMapClassic (void)
{
	unsigned int y, x;
	t_cell emptyCell;

	std::fill (this->_boardCells->front().begin(), this->_boardCells->front().end(), -1);
	std::fill (this->_boardCells->back().begin(), this->_boardCells->back().end(), -1);
	for (y = 1; y < this->_height - 1; y++)
	{
		this->_boardCells->at (y).at (0) = -1;
		this->_boardCells->at (y).at (this->_width - 1) = -1;

		for (x = 1; x < this->_width - 1; x++)
		{
			emptyCell.positionX = x;
			emptyCell.positionY = y;
			this->_boardEmptyCells.push_back (emptyCell);
		}
	}

	this->_boardCompletedScore = 20;
}

void								Board::loadMapLines (void)
{
	unsigned int y,  y_begin, y_end, x, x_begin, x_end;
	std::vector<t_cell>::iterator it;
	t_cell emptyCell;

	this->loadMapClassic();

	/* X */

	y_begin = ceil (this->_height / 8.0f);
	y_end = floor (7 * this->_height / 8.0f) - 1;

	x_begin = ceil (this->_width / 8.0f);
	x_end = ceil (3 * this->_width / 8.0f);
	for (x = x_begin; x < x_end; x++)
	{
		this->_boardCells->at (y_begin).at (x) = -1;

		emptyCell.positionX = x;
		emptyCell.positionY = y_begin;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);

		this->_boardCells->at (y_end).at (x) = -1;

		emptyCell.positionX = x;
		emptyCell.positionY = y_end;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);
	}

	x_begin = floor (5 * this->_width / 8.0f);
	x_end = floor (7 * this->_width / 8.0f);
	for (x = x_begin; x < x_end; x++)
	{
		this->_boardCells->at (y_begin).at (x) = -1;

		emptyCell.positionX = x;
		emptyCell.positionY = y_begin;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);

		this->_boardCells->at (y_end).at (x) = -1;

		emptyCell.positionX = x;
		emptyCell.positionY = y_end;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);
	}

	/* Y */

	x_begin = ceil (this->_width / 8.0f);
	x_end = floor (7 * this->_width / 8.0f) - 1;

	y_begin = ceil (this->_height / 8.0f);
	y_end = ceil (3 * this->_height / 8.0f);
	for (y = y_begin; y < y_end; y++)
	{
		this->_boardCells->at (y).at (x_begin) = -1;

		emptyCell.positionX = x_begin;
		emptyCell.positionY = y;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);

		this->_boardCells->at (y).at (x_end) = -1;

		emptyCell.positionX = x_end;
		emptyCell.positionY = y;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);
	}

	y_begin = floor (5 * this->_height / 8.0f);
	y_end = floor (7 * this->_height / 8.0f);
	for (y = y_begin; y < y_end; y++)
	{
		this->_boardCells->at (y).at (x_begin) = -1;

		emptyCell.positionX = x_begin;
		emptyCell.positionY = y;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);

		this->_boardCells->at (y).at (x_end) = -1;

		emptyCell.positionX = x_end;
		emptyCell.positionY = y;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);
	}

	this->_boardCompletedScore = 20;
}

void								Board::loadMapBlocks (void)
{
	unsigned int beginY, endY, y, blockYCount, beginX, endX, x, blockXCount;
	std::vector<t_cell>::iterator it;
	t_cell emptyCell;

	this->loadMapClassic();

	for (blockYCount = 1; blockYCount < 4; blockYCount++)
	{
		beginY = blockYCount * (this->_height / 4) - (this->_height / 20);
		endY = blockYCount * (this->_height / 4) + (this->_height / 20);
		for (y = beginY + 1; y <= endY; y++)
		{
			for (blockXCount = 1; blockXCount < 4; blockXCount++)
			{
				beginX = blockXCount * (this->_width / 4) - (this->_width / 20);
				endX = blockXCount * (this->_width / 4) + (this->_width / 20);
				for (x = beginX + 1; x <= endX; x++)
				{
					this->_boardCells->at (y).at (x) = -1;

					emptyCell.positionX = x;
					emptyCell.positionY = y;
					it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
					this->_boardEmptyCells.erase (it);
				}
			}
		}
	}

	this->_boardCompletedScore = 20;
}

void								Board::loadMapBorderless (void)
{
	unsigned int y, x;
	t_cell emptyCell;

	for (y = 0; y < this->_height; y++)
	{
		std::fill (this->_boardCells->at (y).begin(), this->_boardCells->at (y).end(), 0);

		for (x = 0; x < this->_width; x++)
		{
			emptyCell.positionX = x;
			emptyCell.positionY = y;
			this->_boardEmptyCells.push_back (emptyCell);
		}
	}

	this->_boardCompletedScore = 20;
}

void								Board::loadMapLinesBorderless (void)
{
	unsigned int y,  y_begin, y_end, x, x_begin, x_end;
	std::vector<t_cell>::iterator it;
	t_cell emptyCell;

	this->loadMapBorderless();

	/* X */

	y_begin = ceil (this->_height / 8.0f);
	y_end = floor (7 * this->_height / 8.0f) - 1;

	x_begin = ceil (this->_width / 8.0f);
	x_end = ceil (3 * this->_width / 8.0f);
	for (x = x_begin; x < x_end; x++)
	{
		this->_boardCells->at (y_begin).at (x) = -1;

		emptyCell.positionX = x;
		emptyCell.positionY = y_begin;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);

		this->_boardCells->at (y_end).at (x) = -1;

		emptyCell.positionX = x;
		emptyCell.positionY = y_end;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);
	}

	x_begin = floor (5 * this->_width / 8.0f);
	x_end = floor (7 * this->_width / 8.0f);
	for (x = x_begin; x < x_end; x++)
	{
		this->_boardCells->at (y_begin).at (x) = -1;

		emptyCell.positionX = x;
		emptyCell.positionY = y_begin;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);

		this->_boardCells->at (y_end).at (x) = -1;

		emptyCell.positionX = x;
		emptyCell.positionY = y_end;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);
	}

	/* Y */

	x_begin = ceil (this->_width / 8.0f);
	x_end = floor (7 * this->_width / 8.0f) - 1;

	y_begin = ceil (this->_height / 8.0f);
	y_end = ceil (3 * this->_height / 8.0f);
	for (y = y_begin; y < y_end; y++)
	{
		this->_boardCells->at (y).at (x_begin) = -1;

		emptyCell.positionX = x_begin;
		emptyCell.positionY = y;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);

		this->_boardCells->at (y).at (x_end) = -1;

		emptyCell.positionX = x_end;
		emptyCell.positionY = y;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);
	}

	y_begin = floor (5 * this->_height / 8.0f);
	y_end = floor (7 * this->_height / 8.0f);
	for (y = y_begin; y < y_end; y++)
	{
		this->_boardCells->at (y).at (x_begin) = -1;

		emptyCell.positionX = x_begin;
		emptyCell.positionY = y;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);

		this->_boardCells->at (y).at (x_end) = -1;

		emptyCell.positionX = x_end;
		emptyCell.positionY = y;
		it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
		if (it != this->_boardEmptyCells.end())
			this->_boardEmptyCells.erase (it);
	}

	this->_boardCompletedScore = 20;
}

void								Board::loadMapBlocksBorderless (void)
{
	unsigned int beginY, endY, y, blockYCount, beginX, endX, x, blockXCount;
	std::vector<t_cell>::iterator it;
	t_cell emptyCell;

	this->loadMapBorderless();

	for (blockYCount = 1; blockYCount < 4; blockYCount++)
	{
		beginY = blockYCount * (this->_height / 4) - (this->_height / 20);
		endY = blockYCount * (this->_height / 4) + (this->_height / 20);
		for (y = beginY + 1; y <= endY; y++)
		{
			for (blockXCount = 1; blockXCount < 4; blockXCount++)
			{
				beginX = blockXCount * (this->_width / 4) - (this->_width / 20);
				endX = blockXCount * (this->_width / 4) + (this->_width / 20);
				for (x = beginX + 1; x <= endX; x++)
				{
					this->_boardCells->at (y).at (x) = -1;

					emptyCell.positionX = x;
					emptyCell.positionY = y;
					it = std::find (this->_boardEmptyCells.begin(), this->_boardEmptyCells.end(), emptyCell);
					this->_boardEmptyCells.erase (it);
				}
			}
		}
	}

	this->_boardCompletedScore = 20;
}

void								Board::updateBonus (void)
{
	unsigned int numEmptyCell;
	t_cell emptyCell;

	if (this->_bonus1.getTimeLeft())
	{
		this->_bonus1.update();
	}
	else
	{
		if (this->_bonus1.isActif())
		{
			emptyCell.positionX = this->_bonus1.getX();
			emptyCell.positionY = this->_bonus1.getY();

			this->_boardCells->at (emptyCell.positionY).at (emptyCell.positionX) = 0;
			this->_boardEmptyCells.push_back (emptyCell);		/* bonus1 become an empty cell */
			this->_bonus1.clear();
		}

		srand (time (NULL));
		numEmptyCell = rand() % this->_boardEmptyCells.size();
		emptyCell = this->_boardEmptyCells [numEmptyCell];

		this->_bonus1.generate (emptyCell.positionX, emptyCell.positionY, this->_mapSize);

		this->_boardCells->at (emptyCell.positionY).at (emptyCell.positionX) = (int)this->_bonus1.getValue();

		this->_boardEmptyCells.erase (this->_boardEmptyCells.begin() + numEmptyCell);
	}

	if (this->_boardMode & eboadMode::Multiplayer)
	{
		if (this->_bonus2.getTimeLeft())
			this->_bonus2.update();
		else
		{
			if (this->_bonus2.isActif())
			{
				emptyCell.positionX = this->_bonus2.getX();
				emptyCell.positionY = this->_bonus2.getY();

				this->_boardCells->at (emptyCell.positionY).at (emptyCell.positionX) = 0;
				this->_boardEmptyCells.push_back (emptyCell);		/* bonus2 become an empty cell */
				this->_bonus2.clear();
			}

			srand (time (NULL) / 2);
			numEmptyCell = rand() % this->_boardEmptyCells.size();
			emptyCell = this->_boardEmptyCells [numEmptyCell];

			this->_bonus2.generate (emptyCell.positionX, emptyCell.positionY, this->_mapSize);

			this->_boardCells->at (emptyCell.positionY).at (emptyCell.positionX) = (int)this->_bonus2.getValue();

			this->_boardEmptyCells.erase (this->_boardEmptyCells.begin() + numEmptyCell);
		}
	}
}

void								Board::checkSnakesCollision (void)
{
	std::list<t_cell> snakeP1Cells;
	std::list<t_cell> snakeP2Cells;
	std::list<t_cell>::iterator it;
	t_cell snakeP1Head;
	t_cell snakeP2Head;
	t_cell bonus1Position;
	t_cell bonus2Position;

	bonus1Position.positionX = this->_bonus1.getX();
	bonus1Position.positionY = this->_bonus1.getY();
	bonus2Position.positionX = this->_bonus2.getX();
	bonus2Position.positionY = this->_bonus2.getY();

	/* check if snakeP1 hit a wall */
	snakeP1Cells = this->_snakeP1->getSnakeCells();
	snakeP1Head = snakeP1Cells.front();
	if (this->_boardCells->at (snakeP1Head.positionY).at (snakeP1Head.positionX) < 0)
	{
		this->_snakeP1->dead();
		std::cout << "Snake P1 Dead !! (hit wall at [" << snakeP1Head.positionX;
		std::cout << ";" << snakeP1Head.positionY << "])" << std::endl;
		this->_boardStatus = eBoardStatus::Player1Lose;
	}

	/* check if snakeP1 eat something */
	if (this->_boardCells->at (snakeP1Head.positionY).at (snakeP1Head.positionX) > 0)
	{
		std::cout << " *** SnakeP1 eat ***" << std::endl;

		this->_snakeP1->eat (this->_boardCells->at (snakeP1Head.positionY).at (snakeP1Head.positionX));
		if (snakeP1Head == bonus1Position)
			this->_bonus1.clear();
		if (snakeP1Head == bonus2Position)
			this->_bonus2.clear();

		this->_boardCells->at (snakeP1Head.positionY).at (snakeP1Head.positionX) = 0;
		this->_boardEmptyCells.push_back (snakeP1Head);		/* snakeP1 Head become an empty cell */
	}

	if (this->_boardMode & eboadMode::Multiplayer)
	{
		/* check if snakeP2 hit a wall */
		snakeP2Cells = this->_snakeP2->getSnakeCells();
		snakeP2Head = snakeP2Cells.front();
		if (this->_boardCells->at (snakeP2Head.positionY).at (snakeP2Head.positionX) < 0)
		{
			this->_snakeP2->dead();
			std::cout << "Snake P2 Dead !! (hit wall at [" << snakeP2Head.positionX;
			std::cout << ";" << snakeP2Head.positionY << "])" << std::endl;
			if (this->_snakeP1->isAlive())
				this->_boardStatus = eBoardStatus::Player1Win;
			else
				this->_boardStatus = eBoardStatus::Draw;
		}

		/* check if snakeP2 eat something */
		if (this->_boardCells->at (snakeP2Head.positionY).at (snakeP2Head.positionX) > 0)
		{
			std::cout << " *** SnakeP2 eat ***" << std::endl;

			this->_snakeP2->eat (this->_boardCells->at (snakeP2Head.positionY).at (snakeP2Head.positionX));
			if (snakeP2Head == bonus1Position)
				this->_bonus1.clear();
			if (snakeP2Head == bonus2Position)
				this->_bonus2.clear();

			this->_boardCells->at (snakeP2Head.positionY).at (snakeP2Head.positionX) = 0;
			this->_boardEmptyCells.push_back (snakeP2Head);		/* snakeP2 Head become an empty cell */
		}

		if (! (this->_boardMode & eboadMode::NoFriendlyFire))
		{
			/* check if snakeP1 hit snakeP2 */
			it = std::find (snakeP2Cells.begin(), snakeP2Cells.end(), snakeP1Head);
			if (it != snakeP2Cells.end())
			{
				this->_snakeP1->dead();
				std::cout << "Snake P1 Dead !! (hit Snake P2 at [" << snakeP1Head.positionX;
				std::cout << ";" << snakeP1Head.positionY << "])" << std::endl;
				this->_boardStatus = eBoardStatus::Player2Win;
			}

			/* check if snakeP2 hit snakeP1 */
			it = std::find (snakeP1Cells.begin(), snakeP1Cells.end(), snakeP2Head);
			if (it != snakeP1Cells.end())
			{
				this->_snakeP2->dead();
				std::cout << "Snake P2 Dead !! (hit Snake P1 at [" << snakeP2Head.positionX;
				std::cout << ";" << snakeP2Head.positionY << "])" << std::endl;
				if (this->_snakeP1->isAlive())
					this->_boardStatus = eBoardStatus::Player1Win;
				else
					this->_boardStatus = eBoardStatus::Draw;
			}
		}
	}
}

/*
 * Public
 */
void								Board::initBoard (unsigned int width, unsigned int height, eboadMode boardMode)
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

	if (this->_initialized)
	{
		throw InvalidArgumentException ("Board::initBoard: already initialized");
	}

	this->_boardCells = new std::vector< std::vector<int> > (height, std::vector<int> (width, 0));
	if (! this->_boardCells)
	{
		throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	this->_width = width;
	this->_height = height;

	switch (width + height)
	{
		case 60 ... 100:
			this->_mapSize = eBonusMapScale::Small;
			break;
		case 101 ... 140:
			this->_mapSize = eBonusMapScale::Medium;
			break;
		case 141 ... 200:
			this->_mapSize = eBonusMapScale::Large;
			break;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	this->_boardMode = boardMode;
	this->_initialized = true;
}

void								Board::setMultiPlayerMode (bool activate)
{
	if (activate)
	{
		this->_boardMode = static_cast<eboadMode>
							(this->_boardMode | eboadMode::Multiplayer);
	}
	else
	{
		this->_boardMode = static_cast<eboadMode>
							(this->_boardMode & ~eboadMode::Multiplayer);
	}
}

void								Board::loadMap (eBoardMaps map)
{
	switch (map)
	{
		case eBoardMaps::Classic:
			this->loadMapClassic();
			break;

		case eBoardMaps::Lines:
			this->loadMapLines();
			break;

		case eBoardMaps::Blocks:
			this->loadMapBlocks();
			break;

//		case eBoardMaps::Tribal:
//			this->loadMapTribal();
//			break;

		case eBoardMaps::Borderless:
			this->loadMapBorderless();
			break;

		case eBoardMaps::LinesBorderless:
			this->loadMapLinesBorderless();
			break;

		case eBoardMaps::BlocksBorderless:
			this->loadMapBlocksBorderless();
			break;

		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	this->_currentMap = map;
}

void								Board::initPlayers (Snake *snakeP1, Snake *snakeP2)
{
	unsigned int p1InitPosX, p1InitPosY, p2InitPosX, p2InitPosY;

	if (! snakeP1)
	{
		throw InvalidArgumentException ("Board::initPlayers: snakeP1 == null");
	}

	if (! (this->_boardMode & eboadMode::Multiplayer))
	{
		if (snakeP2)
		{
			throw InvalidArgumentException ("Board::initPlayers: SinglePlayer board but snakeP2 != null");
		}
	}
	else
	{
		if (! snakeP2)
		{
			throw InvalidArgumentException ("Board::initPlayers: MultiPlayer board but snakeP2 == null");
		}
	}

	if (! this->_initialized)
	{
		throw InvalidArgumentException ("Board::initPlayers: Board not initialized");
	}

	this->_snakeP1 = snakeP1;
	switch (this->_currentMap)
	{
		case eBoardMaps::Classic:
		case eBoardMaps::Borderless:
			if (! (this->_boardMode & eboadMode::Multiplayer))
			{
				p1InitPosX = floor (this->_width / 2.0f);
				p1InitPosY = floor (this->_height / 2.0f);
			}
			else
			{
				p1InitPosX = floor (this->_width / 8.0f) > 4 ?
							 floor (this->_width / 8.0f) : 6;
				p1InitPosY = floor (this->_height / 8.0f) > 4 ?
							 floor (this->_height / 8.0) : 6;
			}
			break;
		case eBoardMaps::Lines:
		case eBoardMaps::LinesBorderless:
			if (! (this->_boardMode & eboadMode::Multiplayer))
			{
				p1InitPosX = floor (this->_width / 2.0f);
				p1InitPosY = floor (this->_height / 2.0f);
			}
			else
			{
				p1InitPosX = floor (this->_width / 3.0f);
				p1InitPosY = floor (this->_height / 3.0f);
			}
			break;
		case eBoardMaps::Blocks:
			p1InitPosX = floor (this->_width / 10.0f) > 4 ?
						 floor (this->_width / 10.0f) : 4;
			p1InitPosY = floor (this->_height / 10.0f) > 4 ?
						 floor (this->_height / 10.0f) : 4;
			break;
		case eBoardMaps::Tribal:
			if (! (this->_boardMode & eboadMode::Multiplayer))
			{
				p1InitPosX = floor (this->_width / 2.0f);
				p1InitPosY = floor (this->_height / 2.0f);
			}
			else
			{
				p1InitPosX = 10u;
				p1InitPosY = 10u;
			}
			break;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}

	this->_snakeP1->initSnake (p1InitPosX, p1InitPosY, 4u,
							   eSnakeDirection::East, true /* canPassThroughWall */,
							   (bool)! (this->_boardMode & eboadMode::NoFriendlyFire));
	this->_snakeP1->setMapWidth (this->_width);
	this->_snakeP1->setMapHeight (this->_height);

	if (this->_boardMode & eboadMode::Multiplayer)
	{
		this->_snakeP2 = snakeP2;
		switch (this->_currentMap)
		{
			case eBoardMaps::Classic:
			case eBoardMaps::Borderless:
				p2InitPosX = ceil (7.0f * this->_width / 8.0f) < this->_width - 4 ?
							 ceil (7.0f * this->_width / 8.0f) - 1 :
							 this->_width - 7;
				p2InitPosY = ceil (7.0f * this->_height / 8.0f) < this->_height - 4 ?
							 ceil (7.0f * this->_height / 8.0f) - 1 :
							 this->_height - 7;
				break;
			case eBoardMaps::Lines:
			case eBoardMaps::LinesBorderless:
				p2InitPosX = ceil (2.0f * this->_width / 3.0f) - 1;
				p2InitPosY = ceil (2.0f * this->_height / 3.0f) - 1;
				break;
			case eBoardMaps::Blocks:
				p2InitPosX = ceil (9.0f * this->_width / 10.0f) < this->_width - 4 ?
							 ceil (9.0f * this->_width / 10.0f) - 1 :
							 this->_width - 5;
				p2InitPosY = ceil (9.0f * this->_height / 10.0f) < this->_height - 4 ?
							 ceil (9.0f * this->_height / 10.0f) - 1 :
							 this->_height - 5;
				break;
			case eBoardMaps::Tribal:
				p2InitPosX = ceil (7.0f * this->_width / 8.0f) < this->_width - 4 ?
							 ceil (7.0f * this->_width / 8.0f) - 1:
							 this->_width - 7;
				p2InitPosY = ceil (7.0f * this->_height / 8.0f) < this->_height - 4 ?
							 ceil (7.0f * this->_height / 8.0f) - 1:
							 this->_height - 7;
				break;
			default:
				throw ShouldNeverOccurException (__FILE__, __LINE__);
		}
		this->_snakeP2->initSnake (p2InitPosX, p2InitPosY, 4u,
								   eSnakeDirection::West, true /* canPassThroughWall */,
								   (bool)! (this->_boardMode & eboadMode::NoFriendlyFire));
		this->_snakeP2->setMapWidth (this->_width);
		this->_snakeP2->setMapHeight (this->_height);
	}

	this->_boardStatus = eBoardStatus::Playing;
	this->_playersInitialized = true;
}

void								Board::runTurn (void)
{
	if (! this->_playersInitialized)
	{
		throw InvalidArgumentException ("Board::runTurn: Players not initialized");
	}

	this->_snakeP1->moveStraight();
	if (this->_boardMode & eboadMode::Multiplayer)
		this->_snakeP2->moveStraight();

	this->checkSnakesCollision();
	this->updateBonus();
}

bool								Board::snakesAreAlive (void)
{
	if (! this->_playersInitialized)
	{
		throw InvalidArgumentException ("Board::snakesAreAlive: Players not initialized");
	}

	if (! this->_snakeP1->isAlive())
	{
		this->_boardStatus = eBoardStatus::Player1Lose;
		if (this->_boardMode & eboadMode::Multiplayer)
		{
			if (this->_snakeP2->isAlive())
				this->_boardStatus = eBoardStatus::Player2Win;
			else
				this->_boardStatus = eBoardStatus::Draw;
		}
		return false;
	}

	if ((this->_boardMode & eboadMode::Multiplayer) && ! this->_snakeP2->isAlive())
	{
		this->_boardStatus = eBoardStatus::Player1Win;
		return false;
	}

	return true;
}

bool								Board::boardIsCompleted (void)
{
	if (! this->_playersInitialized)
	{
		throw InvalidArgumentException ("Board::boardCompleted: Players not initialized");
	}

	if (this->_boardMode & eboadMode::Endless)
	{
		return false;
	}

	if (this->_snakeP1->getScore() >= this->_boardCompletedScore)
	{
		if (this->_boardMode & eboadMode::Multiplayer)
		{
			if (this->_snakeP2->getScore() < this->_boardCompletedScore)
			{
				this->_snakeP2->dead();
				this->_boardStatus = eBoardStatus::Player1Win;
			}
			else
				this->_boardStatus = eBoardStatus::Draw;
		}
		else
			this->_boardStatus = eBoardStatus::Player1Win;

		return true;
	}

	if ((this->_boardMode & eboadMode::Multiplayer) &&
		(this->_snakeP2->getScore() >= this->_boardCompletedScore))
	{
		this->_snakeP1->dead();
		this->_boardStatus = eBoardStatus::Player2Win;

		return true;
	}

	return false;
}

void								Board::clearBoard (void)
{
	if (this->_boardCells)
	{
		delete this->_boardCells;
	}
	this->_boardCells = NULL;
	this->_boardEmptyCells.clear();

	this->_width = 0u;
	this->_height = 0u;
	this->_initialized = false,
	this->_boardMode = eboadMode::Default;
	this->_snakeP1 = NULL;
	this->_snakeP2 = NULL;
	this->_playersInitialized = false,
	this->_bonus1.clear();
	this->_bonus2.clear();
}