#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# define TRUE 1
# define FALSE 0

typedef struct s_vector		t_vector;

double				dot_product(t_vector vec1, t_vector vec2);
t_vector			vec_subtract(t_vector vec1, t_vector vec2);
int 				in_range_inclusive(double number, double min, double max);

#endif
