float				compute_glare(
		float3 normal,
		float3 light_vec,
		float3 ray_dir,
		float light_intensity,
		int specularity)
{
	float	result_intensity = 0;

	float3 half_ray_light = normalize(light_vec + ray_dir);
	result_intensity = pow(dot(normal, half_ray_light), specularity);
	return result_intensity * light_intensity;
}

float3			compute_normal(float3 point, __constant t_object *intersect_obj)
{
	if (intersect_obj->type == SPHERE)
		return normalize(point - intersect_obj->center);
	else if (intersect_obj->type == PLANE)
		return intersect_obj->normal;
	else if (intersect_obj->type == CYLINDER)
		return normalize((point - intersect_obj->center)
			- (dot(intersect_obj->axis, (point - intersect_obj->center))) * intersect_obj->axis);
	return (float3)(0, 0, 0);
}

int					in_shadow(
		__constant t_scene *scene,
		__constant t_object *objects,
		float3 point,
		float3 light_dir,
		float ray_max)
{
	int		found_object = NOT_SET;

	closest_intersection(scene, objects, point, light_dir, 0.01f, ray_max, &found_object, 0);
	if (found_object != NOT_SET)
		return true;
	else
		return false;
}

float				compute_lighting(
	__constant t_scene *scene,
	__constant t_light *lights,
	__constant t_object *objects,
	float3 point,
	float3 normal,
	float3 ray_dir,
	float closest_intersect,
	int closest_obj_index)
{
	float3		light_dir;
	float		normal_dot_light;
	float		intensity;

	intensity = 0.0f;
	for (int i = 0; i < scene->lights_nbr; i++)
	{
		float		ray_max;

		if (lights[i].type == 1)
		{
			intensity += lights[i].intensity;
			continue;
		}
		else if (lights[i].type == POINT)
		{
			light_dir = lights[i].pos - point;
			ray_max = 1;
		}
		else
		{
			light_dir = lights[i].dir;
			ray_max = INFINITY;
		}
		if (in_shadow(scene, objects, point, light_dir, ray_max))
			continue;
		normal_dot_light = dot(normal, light_dir);
		if (normal_dot_light > 0)
		{
			if (objects[closest_obj_index].material.specularity != MATERIAL_OPAQUE)
				intensity += lights[i].intensity * normal_dot_light / (length(normal) * length(light_dir));
				intensity += compute_glare(normal, light_dir, ray_dir, lights[i].intensity, objects[closest_obj_index].material.specularity);
		}
	}
	return (intensity);
}
