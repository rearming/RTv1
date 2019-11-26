#define DD dot(ray_dir, ray_dir)
#define DX dot(ray_dir, origin_center)
#define DV(obj) dot(ray_dir, obj->cylinder_axis)
#define XV(obj) dot(origin_center, obj->cylinder_axis)
#define XX dot(origin_center, origin_center)
#define SQR(x) x*x

void			ray_plane_intersect(
		float3 camera_pos,
		float3 ray_dir,
		float3 center,
		float3 normal,
		float *out_x1,
		float *out_x2)
{
		const float3	origin_center = camera_pos - center;

		*out_x1 = (-dot(origin_center, normal)) / dot(ray_dir, normal);
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

	*out_x1 = (-b + sqrt_discriminant) / (2 * a);
	*out_x2 = (-b - sqrt_discriminant) / (2 * a);
}


void			ray_cylinder_intersect(
		float3 camera_pos,
		float3 ray_dir,
		__constant t_object *cylinder,
		float *out_x1,
		float *out_x2)
{
	const float3	origin_center = camera_pos - cylinder->center;
	float 			a, b, c, discriminant;

	a = DD - SQR(DV(cylinder));
	b = 2 * (DX - DV(cylinder) * XV(cylinder));
	c = XX - SQR(XV(cylinder)) - SQR(cylinder->radius);

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return ;
	float sqrt_discriminant = sqrt(discriminant);

	*out_x1 = (-b + sqrt_discriminant) / (2 * a);
	*out_x2 = (-b - sqrt_discriminant) / (2 * a);

	float m1 = dot(ray_dir, cylinder->cylinder_axis * *out_x1) + XV(cylinder);
	float m2 = dot(ray_dir, cylinder->cylinder_axis * *out_x2) + XV(cylinder);

	if (fabs(m1) > cylinder->len && fabs(m2) > cylinder->len)
	{
		*out_x1 = INFINITY;
		*out_x2 = INFINITY;
	}
}

void			ray_cone_intersect(
		float3 camera_pos,
		float3 ray_dir,
		__constant t_object *cone,
		float *out_x1,
		float *out_x2)
{
		float 			a, b, c, discriminant;
		const float 	k2 = SQR(tan(cone->angle)) + 1.f;
		const float3	origin_center = camera_pos - cone->center;

//		a = dot(ray_dir, ray_dir) - k2 * SQR(dot(ray_dir, cone->normal));
//		b = dot(ray_dir, origin_center) - k2 * dot(ray_dir, cone->normal) * dot(origin_center, cone->normal);
//		c = dot(origin_center, origin_center) - k2 * SQR(dot(origin_center, cone->normal));

		a = DD - k2 * SQR(DV(cone));
		b = DX - k2 * (DV(cone) * XV(cone));
		c = XX - k2 * SQR(XV(cone));

		discriminant = b * b - 4.f * a * c;
		if (discriminant < 0)
			return ;
		float sqrt_discriminant = sqrt(discriminant);

		*out_x1 = (-b + sqrt_discriminant) / (2.f * a);
		*out_x2 = (-b - sqrt_discriminant) / (2.f * a);
}

//void			ray_cone_intersect(
//		float3 camera_pos,
//		float3 ray_dir,
//		__constant t_object *cone,
//float *out_x1,
//float *out_x2)
//{
//float 			a, b, c, discriminant;
//const float 	k2 = SQR(cone->angle) + 1.f;
//const float3	origin_center = camera_pos - cone->center;
//
//a = SQR(dot(ray_dir, cone->normal)) - SQR(cos(cone->angle));
//b = 2.f * (dot(ray_dir, cone->normal) * dot(origin_center, cone->normal) - dot(ray_dir, origin_center) * SQR(cos(cone->angle)));
//c = SQR(dot(origin_center, cone->normal)) - dot(origin_center, origin_center) * SQR(cos(cone->angle));
//
//
//discriminant = b * b - 4.f * a * c;
//if (discriminant < 0)
//return ;
//float sqrt_discriminant = sqrt(discriminant);
//
//*out_x1 = (-b + sqrt_discriminant) / (2.f * a);
//*out_x2 = (-b - sqrt_discriminant) / (2.f * a);
//}

void find_intersection(
		float3 origin,
		float3 ray_dir,
		__constant t_object *object,
		float *out_intersect1,
		float *out_intersect2)
{
	*out_intersect1 = INFINITY;
	*out_intersect2 = INFINITY;
	switch(object->type)
	{
		case (SPHERE):
			ray_sphere_intersect(origin, ray_dir, object, out_intersect1, out_intersect2);
			break ;
		case (PLANE):
			ray_plane_intersect(origin, ray_dir, object->center, object->normal, out_intersect1, out_intersect2);
			break ;
		case (CYLINDER):
			ray_cylinder_intersect(origin, ray_dir, object, out_intersect1, out_intersect2);
			break ;
		case (CONE):
			ray_cone_intersect(origin, ray_dir, object, out_intersect1, out_intersect2);
			break ;
	}
}

float				closest_intersection(
		__constant t_scene *scene,
		__constant t_object *objects,
		float3 origin,
		float3 ray_dir,
		float ray_min,
		float ray_max,
		int *out_closest_obj_index,
		t_color *out_result_color
		)
{
	float		closest_intersect = INFINITY;
	float		intersect_1;
	float		intersect_2;

	for (int i = 0; i < scene->obj_nbr; i++)
	{
		find_intersection(origin, ray_dir, &objects[i], &intersect_1, &intersect_2);
		if (in_range_inclusive(intersect_1, ray_min, ray_max) && intersect_1 < closest_intersect)
		{
			closest_intersect = intersect_1;
			if (out_result_color) // проверка если нам не нужен цвет, можно послать NULL
				(*out_result_color).value = objects[i].material.color.value;
			*out_closest_obj_index = i;
		}
		if (in_range_inclusive(intersect_2, ray_min, ray_max) && intersect_2 < closest_intersect)
		{
			closest_intersect = intersect_2;
			if (out_result_color)
				(*out_result_color).value = objects[i].material.color.value;
			*out_closest_obj_index = i;
		}
	}
	return (closest_intersect);
}

int					trace_ray(
		__constant t_scene *scene,
		float3 origin,
		__constant t_object *objects,
		__constant t_light *lights,
		float3 ray_dir,
		float ray_min,
		float ray_max)
{
	float		closest_intersect;
	t_color		result_color;
	int			closest_obj_index = NOT_SET;

	closest_intersect = closest_intersection(scene, objects, origin, ray_dir, ray_min, ray_max, &closest_obj_index, &result_color);
	if (closest_obj_index == NOT_SET)
		return COL_BG;

	float3 point = origin + (ray_dir * closest_intersect);
	float3 normal = compute_normal(point, &objects[closest_obj_index]);
	return change_color_intensity(
			result_color,
			compute_lighting(scene, lights, objects, point, normal, ray_dir, closest_intersect, closest_obj_index));
}

__kernel void		raytracer(
		__constant t_scene *scene,
 		__constant t_object *objects,
 		__constant t_light *lights,
 		__constant t_camera *camera,
 		__global int *img_data)
{
	t_color		result_color;

	int			g_id = get_global_id(0);
	int			x = g_id % WIN_WIDTH;
	int			y = g_id / WIN_HEIGHT;

	x -= WIN_WIDTH / 2;
	y -= WIN_HEIGHT / 2;
	y = -y;

	float3 ray_dir = canvas_to_viewport(camera, (float3)(x, y, 0));
	rotate_point(&ray_dir, camera->rotation);
	result_color.value = trace_ray(scene, camera->pos, objects, lights, ray_dir, camera->viewport_distance, INFINITY);
	img_data[g_id] = result_color.value;
}
