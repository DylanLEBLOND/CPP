#include <Board.class.hpp>

/*
 * Constructors
 */
Board::Board (void)
	: _width (0u), _height (0u), _boardCells (NULL), _initialized (false),
	  _multiPlayer (false), _friendlyFire (true),
	  _snakeP1 (NULL), _snakeP2 (NULL), _playersInitialized (false),
	  _bonusStillUp (0u) {}

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
	if (src.isInitialized ())
	{
		this->initBoard (src.getWidth(), src.getHeight(), src.getMultiPlayer(), src.getFriendlyFire());
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

bool								Board::getMultiPlayer (void) const
{
	return this->_multiPlayer;
}

bool								Board::getFriendlyFire (void) const
{
	return this->_friendlyFire;
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

void								Board::generateBonus (unsigned int number)
{
	unsigned int bonusValue, posEmptyCell;
	t_cell emptyCell;

	while (number > 0)
	{
		srand (time (NULL));
		bonusValue = rand() % 3 + 1;

		srand (time (NULL));
		posEmptyCell = rand() % this->_boardEmptyCells.size();
		emptyCell = this->_boardEmptyCells [posEmptyCell];
		this->_boardCells->at (emptyCell.positionY).at (emptyCell.positionX) = bonusValue;

		this->_boardEmptyCells.erase (this->_boardEmptyCells.begin() + posEmptyCell);
		this->_bonusStillUp++;
		number--;
	}
}

void								Board::checkSnakesCollision (void)
{
	std::list<t_cell> snakeP1Cells;
	std::list<t_cell> snakeP2Cells;
	std::list<t_cell>::iterator it;
	t_cell snakeP1Head;
	t_cell snakeP2Head;

	/* check if snakeP1 hit a wall */
	snakeP1Cells = this->_snakeP1->getSnakeCells();
	snakeP1Head = snakeP1Cells.front();
	if (this->_boardCells->at (snakeP1Head.positionY).at (snakeP1Head.positionX) < 0)
		this->_snakeP1->dead();

	/* check if snakeP1 eat something */
	if (this->_boardCells->at (snakeP1Head.positionY).at (snakeP1Head.positionX) > 0)
	{
		this->_snakeP1->eat (this->_boardCells->at (snakeP1Head.positionY).at (snakeP1Head.positionX));

		this->_boardCells->at (snakeP1Head.positionY).at (snakeP1Head.positionX) = 0;
		this->_boardEmptyCells.insert (this->_boardEmptyCells.begin() +
										snakeP1Head.positionY * this->_width + snakeP1Head.positionX,
										snakeP1Head);		/* snakeP1 Head become an empty cell */
		this->_bonusStillUp--;
	}

	if (this->_multiPlayer)
	{
		/* check if snakeP2 hit a wall */
		snakeP2Cells = this->_snakeP2->getSnakeCells();
		snakeP2Head = snakeP2Cells.front();
		if (this->_boardCells->at (snakeP2Head.positionY).at (snakeP2Head.positionX) < 0)
			this->_snakeP2->dead();

		/* check if snakeP2 eat something */
		if (this->_boardCells->at (snakeP2Head.positionY).at (snakeP2Head.positionX) > 0)
		{
			this->_snakeP2->eat (this->_boardCells->at (snakeP2Head.positionY).at (snakeP2Head.positionX));

			this->_boardCells->at (snakeP2Head.positionY).at (snakeP2Head.positionX) = 0;
			this->_boardEmptyCells.insert (this->_boardEmptyCells.begin() +
											snakeP2Head.positionY * this->_width + snakeP2Head.positionX,
											snakeP2Head);		/* snakeP2 Head become an empty cell */
			this->_bonusStillUp--;
		}

		if (this->_friendlyFire)
		{
			/* check if snakeP1 hit snakeP2 */
			it = std::find (snakeP2Cells.begin(), snakeP2Cells.end(), snakeP1Head);
			if (it != snakeP2Cells.end())
				this->_snakeP2->dead();

			/* check if snakeP2 hit snakeP1 */
			it = std::find (snakeP1Cells.begin(), snakeP1Cells.end(), snakeP2Head);
			if (it != snakeP1Cells.end())
				this->_snakeP1->dead();
		}
	}
}

/*
 * Public
 */
void								Board::initBoard (unsigned int width, unsigned int height, bool multiPlayer, bool friendlyFire)
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
	this->_multiPlayer = multiPlayer;
	this->_friendlyFire = friendlyFire;

	this->_initialized = true;
}

void								Board::initPlayers (Snake *snakeP1, Snake *snakeP2)
{
	if (! snakeP1)
	{
		throw InvalidArgumentException ("Board::initPlayers: snakeP1 == null");
	}

	if (! this->_multiPlayer)
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
	if (this->_multiPlayer)
	{
		this->_snakeP2 = snakeP2;
		this->_snakeP2->setMapWidth (this->_width);
		this->_snakeP2->setMapHeight (this->_height);
	}
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

	if (! this->_multiPlayer && !this->_bonusStillUp)
		this->generateBonus (1);
	else if (this->_multiPlayer)
	{
		if (this->_bonusStillUp < 1)
			this->generateBonus (2);
		else if (this->_bonusStillUp == 1)
			this->generateBonus (1);
	}

	this->_snakeP1->moveStraight();
	if (this->_multiPlayer)
		this->_snakeP2->moveStraight();

	this->checkSnakesCollision();
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

	this->_width = 0u;
	this->_height = 0u;
	this->_multiPlayer = false;
	this->_boardCells = NULL;
}
