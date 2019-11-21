#include "rtv1_structs.h"

double				dot_product(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vector			vec_subtract(t_vector vec1, t_vector vec2)
{
	return ((t_vector){vec1.x - vec2.x, vec1.y = vec2.y, vec1.z - vec2.z});
}
