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

int					Bonus::getTimeLeft (void) const
{
	if (this->_timeLeft == eBonusTime::InfiniteTime)
		return 1;

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
void				Bonus::generate (unsigned int x, unsigned int y, eBonusMapScale mapSize, bool infinite)
{
	unsigned int bonusChosen;
	unsigned int multiplier;

	if (infinite)
	{
		this->_value = eBonusValue::CommonValue;
		this->_timeLeft = eBonusTime::InfiniteTime;
	}
	else
	{
		srand (time (NULL));
		bonusChosen = rand() % 100 + 1;

		switch (mapSize)
		{
			case eBonusMapScale::Small:
				multiplier = 1;
				break;
			case eBonusMapScale::Medium:
				multiplier = 2;
				break;
			case eBonusMapScale::Large:
				multiplier = 4;
				break;
			default:
				multiplier = 1;
				break;
		}

		switch (bonusChosen)
		{
			case 1:
				/*  1 % */
				this->_value = eBonusValue::GodlikeValue;
				this->_timeLeft = eBonusTime::GodlikeTime * multiplier;
				break;
			case 2 ... 5:
				/*  4 % */
				this->_value = eBonusValue::LegendaryValue;
				this->_timeLeft = eBonusTime::LegendaryTime * multiplier;
				break;
			case 6 ... 20:
				/* 15 % */
				this->_value = eBonusValue::RareValue;
				this->_timeLeft = eBonusTime::RareTime * multiplier;
				break;
			case 21 ... 50:
				/* 30 % */
				this->_value = eBonusValue::UncommonValue;
				this->_timeLeft = eBonusTime::UncommonTime * multiplier;
				break;
			default:
				/* 50 % */
				this->_value = eBonusValue::CommonValue;
				this->_timeLeft = eBonusTime::CommonTime * multiplier;
				break;
		}
	}

	this->_x = x;
	this->_y = y;

	this->_isActif = true;

	print_trace ("Bonus::generate: Bonus +", false);
	print_trace (this->_value, true);
	print_trace (" (Time:", false);
	if (this->_timeLeft == eBonusTime::InfiniteTime)
	{
		print_trace ("INFITITE", false);
	}
	else
	{
		print_trace (this->_timeLeft, false);
	}
	print_trace (") generated at (x = ", false);
	print_trace (this->_x, false)
	print_trace (" | y = ", false);
	print_trace (this->_y, true);
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
