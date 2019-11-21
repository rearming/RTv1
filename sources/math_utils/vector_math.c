#include "rtv1.h"

float				dot_product(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vector			vec_subtract(t_vector vec1, t_vector vec2)
{
	return ((t_vector){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
}

t_vector			vec_add(t_vector vec1, t_vector vec2)
{
	return ((t_vector){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_vector			vec_mult_by_scalar(t_vector vec, float scalar)
{
	return ((t_vector){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}

float				vec_magnitude(t_vector vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vector			vec_normalize(t_vector vec)
{
	const float	vec_length = vec_magnitude(vec);

	return ((t_vector){
		vec.x / vec_length,
		vec.y / vec_length,
		vec.z / vec_length});
}
