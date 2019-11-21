#include "rtv1.h"

int					change_color_intensity(int color, double intensity)
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

//	if (intensity > 1)
//		intensity = 1;
//	if (intensity < 0)
//		intensity = 0;
	a = ((color >> 24) & 0xFF) * intensity;
	r = ((color >> 16) & 0xFF) * intensity;
	g = ((color >> 8) & 0xFF) * intensity;
	b = (color & 0xFF) * intensity;
	return (a << 24 | r << 16 | g << 8 | b);
}

double				compute_lighting(
		t_rtv1 *rtv1,
		t_vector ray_dir,
		double closest_intersect,
		t_vector closest_sphere_center //todo это будет generic функция, считающая нормаль к любой поверхности?
		)
{
	t_vector	point;
	t_vector	normal;
	t_vector	light;
	double		normal_dot_light;
	double		intensity;
	int			i;

	point = vec_add(rtv1->camera.pos, vec_mult_by_scalar(ray_dir, closest_intersect));
	normal = vec_normalize(vec_subtract(point, closest_sphere_center));
	intensity = 0.0f;
	i = 0;
	while (i < rtv1->scene.lights_nbr)
	{
		if (rtv1->scene.lights[i].type == AMBIENT)
		{
			intensity += rtv1->scene.lights[i].intensity;
			i++;
			continue ;
		}
		else if (rtv1->scene.lights[i].type == POINT)
			light = vec_subtract(rtv1->scene.lights[i].pos, point);
		else
			light = rtv1->scene.lights[i].dir;
		normal_dot_light = dot_product(normal, light);
		if (normal_dot_light > 0)
			intensity += rtv1->scene.lights[i].intensity * normal_dot_light
					/ (vec_magnitude(normal) * vec_magnitude(light));
		i++;
	}
	return (intensity);
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
	int			closest_sphere_i;

	result_color = COL_BG;
	closest_intersect = INFINITY;
	closest_sphere_i = NOT_SET;
	i = 0;
	while (i < rtv1->scene.spheres_nbr)
	{
		ray_sphere_intersect(rtv1, ray_dir, rtv1->scene.spheres[i],
				&intersect_1, &intersect_2);
		if (in_range_inclusive(intersect_1, ray_min, ray_max) && intersect_1 < closest_intersect)
		{
			closest_intersect = intersect_1;
			result_color = rtv1->scene.spheres[i].color;
			closest_sphere_i = i;
		}
		if (in_range_inclusive(intersect_2, ray_min, ray_max) && intersect_2 < closest_intersect)
		{
			closest_intersect = intersect_2;
			result_color = rtv1->scene.spheres[i].color;
			closest_sphere_i = i;
		}
		i++;
	}
	if (closest_sphere_i != NOT_SET)
		return (change_color_intensity(result_color, compute_lighting(rtv1, ray_dir, closest_intersect, rtv1->scene.spheres[closest_sphere_i].center)));
	return (result_color);
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

void		render(t_rtv1 *rtv1)
{
	SDL_LockTexture(rtv1->sdl.texture, 0,
					(void**)&rtv1->img_data, &rtv1->sdl.pitch);
	render_scene(rtv1);
	SDL_UnlockTexture(rtv1->sdl.texture);
	SDL_SetRenderTarget(rtv1->sdl.rend, rtv1->sdl.texture);
	SDL_RenderCopy(rtv1->sdl.rend, rtv1->sdl.texture, NULL, NULL);
	SDL_RenderPresent(rtv1->sdl.rend);
}
