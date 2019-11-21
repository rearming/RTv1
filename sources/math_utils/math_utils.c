#include "math_utils.h"

int 				in_range_inclusive(double number, double min, double max)
{
	if (number >= min && number <= max)
		return (TRUE);
	else
		return (FALSE);
}