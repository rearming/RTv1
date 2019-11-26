#include "math_utils.h"

int			in_range_inclusive(float number, float min, float max)
{
	if (number >= min && number <= max)
		return (TRUE);
	else
		return (FALSE);
}
