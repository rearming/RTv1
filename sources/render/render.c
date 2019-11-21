#include "rtv1.h"

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
		ray_sphere_intersect(rtv1, ray_dir, rtv1->scene.spheres[i],
							 &intersect_1, &intersect_2);
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
