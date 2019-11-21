#include "rtv1.h"

void				ray_sphere_intersect(
		t_rtv1 *rtv1,
		t_vector ray_dir,
		t_sphere sphere,
		double *out_x1,
		double *out_x2)
{
	t_vector		center = sphere.center;
	double			radius = sphere.raduis;
	const t_vector	origin_center = vec_subtract(rtv1->camera.pos, center);
	t_quadratic_eq	eq;

	eq.a = dot_product(ray_dir, ray_dir);
	eq.b = 2 * dot_product(origin_center, ray_dir);
	eq.c = dot_product(origin_center, origin_center) - radius * radius;
	eq.discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
	if (eq.discriminant < 0)
	{
		*out_x1 = INFINITY;
		*out_x2 = INFINITY;
		return ;
	}
	*out_x1 = (-eq.b + sqrt(eq.discriminant)) / (2 * eq.a); //todo check -O2 cached sqrt
	*out_x2 = (-eq.b - sqrt(eq.discriminant)) / (2 * eq.a);
}
