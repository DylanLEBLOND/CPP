#ifndef COMMOM_HPP
# define COMMOM_HPP

/*
 * System Includes
 */
# include <iostream>

/*
 * Defines
 */
# ifdef DEBUG_MODE

#  ifndef print_trace
#   define print_trace(message, eol)				\
{													\
	std::cout << (message);							\
	if (eol)										\
		std::cout << std::endl;						\
}
#endif

# else

#  ifndef print_trace
#   define print_trace(message, eol) {}
#  endif

# endif

/*
 * Structures
 */
typedef struct s_bounds
{
	int x;
	int y;
	unsigned int width;
	unsigned int height;

	s_bounds (void)
	: x (0), y (0), width (0), height (0) {}

	s_bounds (int x, int y, unsigned int width, unsigned int height)
	: x (x), y (y), width (width), height (height) {}

	s_bounds (s_bounds const &src)
	{
		*this = src;
	}

	s_bounds &operator= (s_bounds const &src)
	{
		this->x = src.x;
		this->y = src.y;
		this->width = src.width;
		this->height = src.height;

		return *this;
	}

	bool operator== (const s_bounds &rhs)
	{
		return ((this->x == rhs.x) &&
				(this->y == rhs.y) &&
				(this->width == rhs.width) &&
				(this->height == rhs.height));
	}

	void scale (unsigned int xScalingFactor, unsigned int yScalingFactor, unsigned int ratio)
	{
		this->x = this->x * xScalingFactor / ratio;
		this->y = this->y * yScalingFactor / ratio;
		this->width = this->width * xScalingFactor / ratio;
		this->height = this->height * yScalingFactor / ratio;
	}

	bool in (int x, int y)
	{
		return ((this->x <= x && x <= (int)(this->x + this->width)) &&
				(this->y <= y && y <= (int)(this->y + this->height)));
	}
}				bounds;

#endif // COMMOM_HPP
