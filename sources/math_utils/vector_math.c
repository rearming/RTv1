#include "rtv1.h"

float				dot_product(cl_float3 vec1, cl_float3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

cl_float3			vec_subtract(cl_float3 vec1, cl_float3 vec2)
{
	return ((cl_float3){{vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z}});
}

cl_float3			vec_add(cl_float3 vec1, cl_float3 vec2)
{
	return ((cl_float3){{vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z}});
}

cl_float3			vec_mult_by_scalar(cl_float3 vec, float scalar)
{
	return ((cl_float3){{vec.x * scalar, vec.y * scalar, vec.z * scalar}});
}

float				vec_magnitude(cl_float3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

cl_float3			vec_normalize(cl_float3 vec)
{
	const float	vec_length = vec_magnitude(vec);

	return ((cl_float3){
		{vec.x / vec_length,
		vec.y / vec_length,
		vec.z / vec_length}});
}
