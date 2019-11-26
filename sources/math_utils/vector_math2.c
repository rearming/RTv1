#include "rtv1.h"

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
