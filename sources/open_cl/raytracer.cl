//todo __global to __const

t_point		get_videomem_coord_system_point(t_point raw_point)
{
	t_point		result;

	result.x = WIN_WIDTH / 2 + raw_point.x;
	result.y = WIN_HEIGHT / 2 - raw_point.y;
	result.color = raw_point.color;
	return (result);
}

float3			canvas_to_viewport(__constant t_camera *camera, float3 canvas_point)
{
	return ((float3)
	{
		.x = canvas_point.x * camera->viewport_width / WIN_WIDTH,
		.y = canvas_point.y * camera->viewport_height / WIN_HEIGHT,
		.z = camera->viewport_distance
	});
}

void	image_put_pixel(int *img_data, t_point point)
{
	if (point.x >= 0 && point.x < WIN_WIDTH
		&& point.y >= 0 && point.y < WIN_HEIGHT)
		img_data[point.x + point.y * WIN_WIDTH] = point.color;
	//todo ограничение цвета от COL_BLACK до COL_WHITE ?
}

void				ray_sphere_intersect(
		float3 ray_dir
		const float3 center,
		const float radius,
		float *out_x1,
		float *out_x2)
{
	const float3	origin_center = camera_pos - center;
	float 			a, b, c, discriminant;

	a = dot(ray_dir, ray_dir);
	b = 2 * dot(origin_center, ray_dir);
	c = dot(origin_center, origin_center) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	float sqrt_discriminant = sqrt(discriminant);
	*out_x1 = (-b + sqrt_discriminant / (2 * a); //todo check -O2 cached sqrt
	*out_x2 = (-b - sqrt_discriminant / (2 * a);
}


void find_intersection(
		float3 ray_dir,
		t_object object,
		float *out_intersect1,
		float *out_intersect2)
{
	*out_intersect1 = CL_INFINITY;
	*out_intersect2 = CL_INFINITY;
	if (object.type == SPHERE)
		ray_sphere_intersect(ray_dir, (t_sphere*)object.obj, out_intersect1, out_intersect2);
}


int					trace_ray(
		__constant t_scene *scene,
		float3 ray_dir,
		float ray_min,
		float ray_max)
{
	float		closest_intersect;
	float		intersect_1;
	float		intersect_2;
	int			result_color;
	int			closest_obj_i;
	int			i;

	result_color = COL_BG;
	closest_intersect = INFINITY;
	closest_obj_i = NOT_SET;
	i = 0;
	while (i < scene->obj_nbr)
	{
		find_intersection(ray_dir, scene->objects[i], &intersect_1, &intersect_2);
		if (in_range_inclusive(intersect_1, ray_min, ray_max) && intersect_1 < closest_intersect)
		{
			closest_intersect = intersect_1;
			result_color = scene->objects[i].color;
			closest_obj_i = i;
		}
		if (in_range_inclusive(intersect_2, ray_min, ray_max) && intersect_2 < closest_intersect)
		{
			closest_intersect = intersect_2;
			result_color = scene->objects[i].color;
			closest_obj_i = i;
		}
		i++;
	}
//	if (closest_obj_i != NOT_SET)
//		return (change_color_intensity(result_color,
//				compute_lighting(rtv1, ray_dir, closest_intersect, rtv1->scene.objects[closest_obj_i])));
	return (result_color);
}

 __kernel void		raytracer(__constant t_scene *scene, __constant t_camera *camera, __global int *img_data)
{
	int		g_id = get_global_id(0);

	int		x = g_id % WIN_WIDTH;
	int		y = g_id / WIN_HEIGHT;
	int		result_color;

	x -= WIN_WIDTH / 2;
	y -= WIN_HEIGHT / 2; //todo но вообще-то это перевернутое изображение (рендер с нижнего левого края)

	float3 ray_dir = canvas_to_viewport(camera, {{x, y, 0}});
	result.color = trace_ray(rtv1, ray_dir, rtv1->camera.viewport_distance, CL_INFINITY);
	image_put_pixel(rtv1->img_data, get_videomem_coord_system_point(result));
}
