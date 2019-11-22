//todo __global to __const

int 				in_range_inclusive(float number, float min, float max)
{
	if (number >= min && number <= max)
		return (TRUE);
	else
		return (FALSE);
}

float3			canvas_to_viewport(__constant t_camera *camera, float3 canvas_point)
{
	float3		result;

	return (float3)
	(
		canvas_point.x * camera->viewport_width / WIN_WIDTH,
		canvas_point.y * camera->viewport_height / WIN_HEIGHT,
		camera->viewport_distance
	);
}

t_point		get_videomem_coord_system_point(t_point raw_point)
{
t_point		result;

result.x = WIN_WIDTH / 2 + raw_point.x;
result.y = WIN_HEIGHT / 2 - raw_point.y;
result.color = raw_point.color;
return (result);
}

void	image_put_pixel(__global int *img_data, t_point point)
{
	if (point.x >= 0 && point.x < WIN_WIDTH
		&& point.y >= 0 && point.y < WIN_HEIGHT)
		img_data[point.x + point.y * WIN_WIDTH] = point.color.value;
	//todo ограничение цвета от COL_BLACK до COL_WHITE ?
}

int					change_color_intensity(t_color color, float intensity)
{
	t_color		result_color;
//
////	if (intensity > 1)
////		intensity = 1;
////	if (intensity < 0)
////		intensity = 0;
////	color.a = intensity; //todo alpha не надо трогать?
	result_color.rgb.a = color.rgb.a;
	result_color.rgb.r = color.rgb.r * intensity;
	result_color.rgb.g = color.rgb.g * intensity;
	result_color.rgb.b = color.rgb.b * intensity;

	return result_color.value;
//	return (a << 24 | r << 16 | g << 8 | b);
}

float3			compute_normal(float3 point, __constant t_object *intersect_obj)
{
	if (intersect_obj->type == SPHERE)
		return (normalize(point - intersect_obj->center));
	return (float3)(0, 0, 0);
}

float				compute_lighting(
		__constant t_scene *scene,
		__constant t_camera *camera,
		__constant t_light *lights,
		float3 ray_dir,
		float closest_intersect,
		__constant t_object *intersect_obj)
{
	float3		point;
	float3		normal;
	float3		light;
	float		normal_dot_light;
	float		intensity;
	int			i;

	point = camera->pos + (ray_dir * closest_intersect);
	normal = compute_normal(point, intersect_obj);
	intensity = 0.0f;
	i = 0;
	while (i < scene->lights_nbr)
	{
		if (lights[i].type == 1)
		{
			intensity += lights[i].intensity;
			i++;
			continue ;
		}
		else if (lights[i].type == POINT)
			light = lights[i].pos - point;
		else
			light = lights[i].dir;
		normal_dot_light = dot(normal, light);
		if (normal_dot_light > 0)
			intensity += lights[i].intensity * normal_dot_light
						 / (length(normal) * length(light));
		i++;
	}
	return (intensity);
}

void				ray_sphere_intersect(
		float3 camera_pos,
		float3 ray_dir,
		__constant t_object *sphere,
		float *out_x1,
		float *out_x2)
{
	const float3	origin_center = camera_pos - sphere->center;
	float 			a, b, c, discriminant;

	a = dot(ray_dir, ray_dir);
	b = 2 * dot(origin_center, ray_dir);
	c = dot(origin_center, origin_center) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	float sqrt_discriminant = sqrt(discriminant);

	*out_x1 = (-b + sqrt_discriminant) / (2 * a); //todo check -O2 cached sqrt
	*out_x2 = (-b - sqrt_discriminant) / (2 * a);
}

void find_intersection(
		__constant t_camera *camera,
		float3 ray_dir,
		__constant t_object *object,
		float *out_intersect1,
		float *out_intersect2)
{
	*out_intersect1 = INFINITY;
	*out_intersect2 = INFINITY;
	if (object->type == SPHERE)
	{
		ray_sphere_intersect(camera->pos, ray_dir, object, out_intersect1, out_intersect2);
	}
}

int					trace_ray(
		__constant t_scene *scene,
		__constant t_camera *camera,
		__constant t_object *objects,
		__constant t_light *lights,
		float3 ray_dir,
		float ray_min,
		float ray_max)
{
	float		closest_intersect;
	float		intersect_1;
	float		intersect_2;
	t_color		result_color;
	int			closest_obj_i;
	int			i;

	result_color.value = COL_BG;
	closest_intersect = INFINITY;
	closest_obj_i = NOT_SET;
	i = 0;
	while (i < scene->obj_nbr)
	{
		find_intersection(camera, ray_dir, &objects[i], &intersect_1, &intersect_2);
		if (in_range_inclusive(intersect_1, ray_min, ray_max) && intersect_1 < closest_intersect)
		{
			closest_intersect = intersect_1;
			result_color.value = objects[i].material.color.value;
			closest_obj_i = i;
		}
		if (in_range_inclusive(intersect_2, ray_min, ray_max) && intersect_2 < closest_intersect)
		{
			closest_intersect = intersect_2;
			result_color.value = objects[i].material.color.value;
			closest_obj_i = i;
		}
		i++;
	}
	if (closest_obj_i != NOT_SET)
		return (change_color_intensity(result_color,
				compute_lighting(scene, camera, lights, ray_dir, closest_intersect, &objects[closest_obj_i])));
	return (result_color.value);
}

 __kernel void		raytracer(
		__constant t_scene *scene,
 		__constant t_object *objects,
 		__constant t_light *lights,
 		__constant t_camera *camera,
 		__global int *img_data)
{
	int			g_id = get_global_id(0);

	int			x = g_id % WIN_WIDTH;
	int			y = g_id / WIN_HEIGHT;
	t_color		result_color;

	x -= WIN_WIDTH / 2;
	y -= WIN_HEIGHT / 2; //todo но вообще-то это перевернутое изображение (рендер с нижнего левого края)

	float3 ray_dir = canvas_to_viewport(camera, (float3)(x, y, 0));
	result_color.value = trace_ray(scene, camera, objects, lights, ray_dir, camera->viewport_distance, INFINITY);
	image_put_pixel(img_data, get_videomem_coord_system_point((t_point){x, y, 0, result_color}));
}
