#ifndef MATH_UTILS_H
# define MATH_UTILS_H

#include <math.h>

# define TRUE 1
# define FALSE 0

typedef struct s_vector		t_vector;

int 				in_range_inclusive(double number, double min, double max);

double				dot_product(t_vector vec1, t_vector vec2);
t_vector			vec_subtract(t_vector vec1, t_vector vec2);
t_vector			vec_add(t_vector vec1, t_vector vec2);
t_vector			vec_mult_by_scalar(t_vector vec, double scalar);
double				vec_magnitude(t_vector vec);
t_vector			vec_normalize(t_vector vec);

#endif
