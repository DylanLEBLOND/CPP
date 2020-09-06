#include <Board.class.hpp>

/*
 * Constructors
 */
Board::Board (void)
	: _width (0u), _height (0u), _boardCells (NULL), _initialized (false),
	  _multiPlayer (false), _friendlyFire (true),
	  _snakeP1 (NULL), _snakeP2 (NULL), _playersInitialized (false) {}

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
		this->initBoard (src.getWidth(), src.getHeight());
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

bool								Board::isInitialized (void) const
{
	return this->_initialized;
}

/*
 * Private
 */
void								Board::loadMapSquare (void)
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
			_boardEmptyCells.push_back (emptyCell);
		}
	}
}

void								Board::loadMapOpen (void)
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
			_boardEmptyCells.push_back (emptyCell);
		}
	}
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

		this->_bonus1.generate (emptyCell.positionX, emptyCell.positionY);

		this->_boardCells->at (emptyCell.positionY).at (emptyCell.positionX) = (int)this->_bonus1.getValue();

		this->_boardEmptyCells.erase (this->_boardEmptyCells.begin() + numEmptyCell);
	}

	if (this->_multiPlayer)
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

			srand (time (NULL));
			numEmptyCell = rand() % this->_boardEmptyCells.size();
			emptyCell = this->_boardEmptyCells [numEmptyCell];

			this->_bonus2.generate (emptyCell.positionX, emptyCell.positionY);

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
		std::cout << "Snake P1 Dead !! (hit obstacle)" << std::endl;
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

	if (this->_multiPlayer)
	{
		/* check if snakeP2 hit a wall */
		snakeP2Cells = this->_snakeP2->getSnakeCells();
		snakeP2Head = snakeP2Cells.front();
		if (this->_boardCells->at (snakeP2Head.positionY).at (snakeP2Head.positionX) < 0)
		{
			this->_snakeP2->dead();
			std::cout << "Snake P2 Dead !! (hit obstacle)" << std::endl;
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

		if (this->_friendlyFire)
		{
			/* check if snakeP1 hit snakeP2 */
			it = std::find (snakeP2Cells.begin(), snakeP2Cells.end(), snakeP1Head);
			if (it != snakeP2Cells.end())
			{
				this->_snakeP1->dead();
				std::cout << "Snake P1 Dead !! (hit Snake P2)" << std::endl;
			}

			/* check if snakeP2 hit snakeP1 */
			it = std::find (snakeP1Cells.begin(), snakeP1Cells.end(), snakeP2Head);
			if (it != snakeP1Cells.end())
			{
				this->_snakeP2->dead();
				std::cout << "Snake P2 Dead !! (hit Snake P1)" << std::endl;
			}
		}
	}
}

/*
 * Public
 */
void								Board::initBoard (unsigned int width, unsigned int height)
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

	this->_initialized = true;
}

void								Board::initPlayers (Snake *snakeP1, Snake *snakeP2, bool multiPlayer, bool friendlyFire)
{
	if (! snakeP1)
	{
		throw InvalidArgumentException ("Board::initPlayers: snakeP1 == null");
	}

	if (! multiPlayer)
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
	this->_snakeP1->setMapWidth (this->_width);
	this->_snakeP1->setMapHeight (this->_height);
	if (multiPlayer)
	{
		this->_snakeP2 = snakeP2;
		this->_snakeP2->setMapWidth (this->_width);
		this->_snakeP2->setMapHeight (this->_height);
	}
	this->_multiPlayer = multiPlayer;
	this->_friendlyFire = friendlyFire;
	this->_playersInitialized = true;
}

void								Board::loadMap (eBoardMaps map)
{
	switch (map)
	{
		case eBoardMaps::Square:
			this->loadMapSquare();
			break;
		case eBoardMaps::Open:
			this->loadMapOpen();
			break;
		default:
			throw ShouldNeverOccurException (__FILE__, __LINE__);
	}
}

void								Board::runTurn (void)
{
	if (! this->_playersInitialized)
	{
		throw InvalidArgumentException ("Board::runTurn: Players not initialized");
	}

	this->_snakeP1->moveStraight();
	if (this->_multiPlayer)
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

	if (! this->_snakeP1->getIsAlive())
		return false;

	if (this->_multiPlayer && ! this->_snakeP2->getIsAlive())
		return false;

	return true;
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
	this->_multiPlayer = false;
	this->_friendlyFire = true,
	this->_snakeP1 = NULL;
	this->_snakeP2 = NULL;
	this->_playersInitialized = false,
	this->_bonus1.clear();
	this->_bonus2.clear();
}
