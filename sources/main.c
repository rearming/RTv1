#include "rtv1.h"

t_vector			canvas_to_viewport(t_rtv1 *rtv1, t_vector canvas_point)
{
	return ((t_vector)
	{
		.x = canvas_point.x * rtv1->camera.viewport_width / WIN_WIDTH,
		.y = canvas_point.y * rtv1->camera.viewport_height / WIN_HEIGHT,
		rtv1->camera.viewport_distance
	});
}

int 				in_range_inclusive(double number, double min, double max)
{
	if (number >= min && number <= max)
		return (TRUE);
	else
		return (FALSE);
}

double				dot_product(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vector			vec_subtract(t_vector vec1, t_vector vec2)
{
	return ((t_vector){vec1.x - vec2.x, vec1.y = vec2.y, vec1.z - vec2.z});
}

void				intersect_ray_sphere(
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

int					trace_ray(
		t_rtv1 *rtv1,
		t_vector ray_dir,
		double ray_min,
		double ray_max)
{
	double		closest_intersect;
	int			i;
	double		intersect_1;
	double		intersect_2;
	int			result_color;

	result_color = COL_GREY;
	closest_intersect = INFINITY;
	i = 0;
	while (i < rtv1->scene.objects)
	{
		intersect_ray_sphere(rtv1, ray_dir, rtv1->scene.spheres[i], &intersect_1, &intersect_2);
		if (in_range_inclusive(intersect_1, ray_min, ray_max) && intersect_1 < closest_intersect)
		{
			closest_intersect = intersect_1;
			result_color = rtv1->scene.spheres[i].color;
		}
		if (in_range_inclusive(intersect_2, ray_min, ray_max) && intersect_2 < closest_intersect)
		{
			closest_intersect = intersect_2;
			result_color = rtv1->scene.spheres[i].color;
		}
		i++;
	}
	return (result_color);
}

t_point		get_videomem_coord_system_point(t_point raw_point)
{
	t_point		result;

	result.x = WIN_WIDTH / 2 + raw_point.x;
	result.y = WIN_HEIGHT / 2 - raw_point.y;
	result.color = raw_point.color;
	return (result);
}

void		render_scene(t_rtv1 *rtv1)
{
	t_vector		ray_dir;
	t_point			result;

	result.x = -WIN_WIDTH / 2;
	while (result.x < WIN_WIDTH / 2)
	{
		result.y = -WIN_HEIGHT / 2;
		while (result.y < WIN_HEIGHT / 2)
		{
			ray_dir = canvas_to_viewport(rtv1, (t_vector){result.x, result.y, 0});
			result.color = trace_ray(rtv1, ray_dir, rtv1->camera.viewport_distance, INFINITY);
			image_put_pixel(rtv1->img_data, get_videomem_coord_system_point(result));
			result.y++;
		}
		result.x++;
	}
	ft_printf("Render done!\n");
}

void		init_scene(t_scene *out_scene)
{
	out_scene->objects = 3;
	out_scene->spheres = malloc(sizeof(*out_scene->spheres) * (out_scene->objects));
	out_scene->spheres[0] = (t_sphere){(t_vector){0, -1, 3}, 1, COL_RED};
	out_scene->spheres[1] = (t_sphere){(t_vector){2, 0, 4}, 1, COL_BLUE};
	out_scene->spheres[2] = (t_sphere){(t_vector){-2, 0, 4}, 1, COL_GREEN};
}

void		init_rtv1(t_rtv1 *out_rtv1)
{
	init_mlx(out_rtv1);
	init_scene(&out_rtv1->scene);

	out_rtv1->camera = (t_camera){
		.pos = (t_vector){0, 0, 0},
		.viewport_distance = 1,
		.viewport_width = 1,
		.viewport_height = 1
	};

}

int			main(int argc, char **argv)
{
	t_rtv1		rtv1;

	(void)argc;
	(void)argv;
	init_rtv1(&rtv1);
	mlx_hook(rtv1.win_ptr, 2, 2, key_press, &rtv1);
	mlx_hook(rtv1.win_ptr, 17, 1, cross_close, &rtv1);
	render_scene(&rtv1);
	mlx_put_image_to_window(rtv1.mlx_ptr, rtv1.win_ptr, rtv1.mlx_img, 0, 0);
	//todo нахуй mlx?
	mlx_loop(rtv1.mlx_ptr);
	return (0);
}
