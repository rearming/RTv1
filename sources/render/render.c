#include "rtv1.h"

int					change_color_intensity(t_color color, float intensity)
{
	t_color		result_color;

//	if (intensity > 1)
//		intensity = 1;
//	if (intensity < 0)
//		intensity = 0;
	result_color.rgb.a = color.rgb.a;
	result_color.rgb.r = color.rgb.r * intensity;
	result_color.rgb.g = color.rgb.g * intensity;
	result_color.rgb.b = color.rgb.b * intensity;
	return (result_color.value);
}

cl_float3			compute_normal(cl_float3 point, t_object intersect_obj)
{
	if (intersect_obj.type == SPHERE)
		return (vec_normalize(vec_subtract(point, intersect_obj.center)));
	return ((cl_float3){.x = 0, .y = 0, .z = 0});
}

float				compute_lighting(
		t_rtv1 *rtv1,
		cl_float3 ray_dir,
		float closest_intersect,
		t_object intersect_obj
		)
{
	cl_float3	point;
	cl_float3	normal;
	cl_float3	light;
	float		normal_dot_light;
	float		intensity;
	int			i;

	point = vec_add(rtv1->camera.pos, vec_mult_by_scalar(ray_dir, closest_intersect));
	normal = compute_normal(point, intersect_obj);
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

void find_intersection(
		t_rtv1 *rtv1,
		cl_float3 ray_dir,
		t_object object,
		float *out_intersect1,
		float *out_intersect2)
{
	*out_intersect1 = INFINITY;
	*out_intersect2 = INFINITY;
	if (object.type == SPHERE)
		ray_sphere_intersect(rtv1, ray_dir, object, out_intersect1, out_intersect2);
}

int					trace_ray(
		t_rtv1 *rtv1,
		cl_float3 ray_dir,
		float ray_min,
		float ray_max)
{
	float		closest_intersect;
	float		intersect_1;
	float		intersect_2;
	t_color		color;
	int			closest_obj_i;
	int			i;

	color.value = COL_BG;
	closest_intersect = INFINITY;
	closest_obj_i = NOT_SET;
	i = 0;
	while (i < rtv1->scene.obj_nbr)
	{
		find_intersection(rtv1, ray_dir, rtv1->scene.objects[i], &intersect_1, &intersect_2);
		if (in_range_inclusive(intersect_1, ray_min, ray_max) && intersect_1 < closest_intersect)
		{
			closest_intersect = intersect_1;
			color.value = rtv1->scene.objects[i].material.color.value;
			closest_obj_i = i;
		}
		if (in_range_inclusive(intersect_2, ray_min, ray_max) && intersect_2 < closest_intersect)
		{
			closest_intersect = intersect_2;
			color.value = rtv1->scene.objects[i].material.color.value;
			closest_obj_i = i;
		}
		i++;
	}
	if (closest_obj_i != NOT_SET)
		return (change_color_intensity(color,
				compute_lighting(rtv1, ray_dir, closest_intersect, rtv1->scene.objects[closest_obj_i])));
	return (color.value);
}

void		render_cpu(t_rtv1 *rtv1)
{
	cl_float3		ray_dir;
	t_point			result;

	result.x = -WIN_WIDTH / 2;
	while (result.x < WIN_WIDTH / 2)
	{
		result.y = -WIN_HEIGHT / 2;
		while (result.y < WIN_HEIGHT / 2)
		{
			ray_dir = canvas_to_viewport(rtv1, (cl_float3){{result.x, result.y, 0}});
			result.color.value = trace_ray(rtv1, ray_dir, rtv1->camera.viewport_distance, INFINITY);
			image_put_pixel(rtv1->img_data, get_videomem_coord_system_point(result));
			result.y++;
		}
		result.x++;
	}
	ft_printf("Render done!\n");
}

void		render(t_rtv1 *rtv1, void (*render_func)(t_rtv1 *))
{
	SDL_LockTexture(rtv1->sdl.texture, 0,
			(void**)&rtv1->img_data, &rtv1->sdl.pitch);
	render_func(rtv1);
	SDL_UnlockTexture(rtv1->sdl.texture);
	SDL_SetRenderTarget(rtv1->sdl.rend, rtv1->sdl.texture);
	SDL_RenderCopy(rtv1->sdl.rend, rtv1->sdl.texture, NULL, NULL);
	SDL_RenderPresent(rtv1->sdl.rend);
}
