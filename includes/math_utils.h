#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "rtv1.h"

int 				in_range_inclusive(float number, float min, float max);

float				dot_product(cl_float3 vec1, cl_float3 vec2);
cl_float3			vec_subtract(cl_float3 vec1, cl_float3 vec2);
cl_float3			vec_add(cl_float3 vec1, cl_float3 vec2);
cl_float3			vec_mult_by_scalar(cl_float3 vec, float scalar);
float				vec_magnitude(cl_float3 vec);
cl_float3			vec_normalize(cl_float3 vec);

void				rotate_y(cl_float3 *point, double angle);
void				rotate_x(cl_float3 *point, double angle);
void				rotate_z(cl_float3 *point, double angle);
void				rotate_point(cl_float3 *point, cl_float3 angle);
cl_float3			degree_to_rad(cl_float3 rotation_degrees);

#endif
