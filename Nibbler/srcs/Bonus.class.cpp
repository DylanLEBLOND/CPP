#include <Bonus.class.hpp>

/*
 * Constructors
 */
Bonus::Bonus (void)
	: _x (0u), _y (0u), _value (eBonusValue::UnknownValue), _timeLeft (eBonusTime::UnknownTime), _isActif (false) {}

Bonus::Bonus (Bonus const &src)
{
	*this = src;
}

/*
 * Destructor
 */
Bonus::~Bonus (void) {}

/*
 * Operator "=" Overload
 */
Bonus				&Bonus::operator= (Bonus const &src)
{
	this->_x = src.getX();
	this->_y = src.getY();
	this->_value = src.getValue();
	this->_timeLeft = src.getTimeLeft();
	this->_isActif = src.isActif();

	return *this;
}

/*
 * Getter
 */
unsigned int		Bonus::getX (void) const
{
	return this->_x;
}

unsigned int		Bonus::getY (void) const
{
	return this->_y;
}

eBonusValue			Bonus::getValue (void) const
{
	return this->_value;
}

unsigned int		Bonus::getTimeLeft (void) const
{
	return this->_timeLeft;
}

bool				Bonus::isActif (void) const
{
	return this->_isActif;
}

/*
 * Private
 */

/*
 * Public
 */
void				Bonus::generate (unsigned int x, unsigned int y)
{
	unsigned int bonusChosen;

	srand (time (NULL));
	bonusChosen = rand() % 100 + 1;

	switch (bonusChosen)
	{
		case 1:
			/*  1 % */
			this->_value = eBonusValue::GodlikeValue;
			this->_timeLeft = eBonusTime::GodlikeTime;
			break;
		case 2 ... 5:
			/*  4 % */
			this->_value = eBonusValue::LegendaryValue;
			this->_timeLeft = eBonusTime::LegendaryTime;
			break;
		case 6 ... 20:
			/* 15 % */
			this->_value = eBonusValue::RareValue;
			this->_timeLeft = eBonusTime::RareTime;
			break;
		case 21 ... 50:
			/* 30 % */
			this->_value = eBonusValue::UncommonValue;
			this->_timeLeft = eBonusTime::UncommonTime;
			break;
		default:
			/* 50 % */
			this->_value = eBonusValue::CommonValue;
			this->_timeLeft = eBonusTime::CommonTime;
			break;
	}

	this->_x = x;
	this->_y = y;

	this->_isActif = true;

	std::cout << "Bonus::generate: Bonus +" << this->_value << " (Time:" << this->_timeLeft;
	std::cout << ") generated at (x = " << this->_x << " | y = " << this->_y << ")" << std::endl;
}

void				Bonus::update (void)
{
	if (this->_timeLeft > 0)
		this->_timeLeft--;
}

void				Bonus::clear (void)
{
	this->_x = 0u;
	this->_y = 0u;
	this->_value = eBonusValue::UnknownValue,
	this->_timeLeft = eBonusTime::UnknownTime;
	this->_isActif = false;
}
