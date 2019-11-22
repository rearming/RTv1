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

float3			compute_normal(float3 point, __constant t_object *intersect_obj)
{
	if (intersect_obj->type == SPHERE)
		return (normalize(point - intersect_obj->center));
	return (float3)(0, 0, 0);
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
