#include "rtv1.h"

void				ray_sphere_intersect(
		t_rtv1 *rtv1,
		t_vector ray_dir,
		const t_sphere *sphere,
		float *out_x1,
		float *out_x2)
{
	t_vector		center = sphere->center;
	float			radius = sphere->raduis;
	const t_vector	origin_center = vec_subtract(rtv1->camera.pos, center);
	t_quadratic_eq	eq;

	eq.a = dot_product(ray_dir, ray_dir);
	eq.b = 2 * dot_product(origin_center, ray_dir);
	eq.c = dot_product(origin_center, origin_center) - radius * radius;
	eq.discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
	if (eq.discriminant < 0)
		return ;
	*out_x1 = (-eq.b + (float)sqrt(eq.discriminant)) / (2 * eq.a); //todo check -O2 cached sqrt
	*out_x2 = (-eq.b - (float)sqrt(eq.discriminant)) / (2 * eq.a);
}
