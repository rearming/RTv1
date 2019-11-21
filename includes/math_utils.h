#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "rtv1.h"

int 				in_range_inclusive(float number, float min, float max);

float				dot_product(t_vector vec1, t_vector vec2);
t_vector			vec_subtract(t_vector vec1, t_vector vec2);
t_vector			vec_add(t_vector vec1, t_vector vec2);
t_vector			vec_mult_by_scalar(t_vector vec, float scalar);
float				vec_magnitude(t_vector vec);
t_vector			vec_normalize(t_vector vec);

#endif
