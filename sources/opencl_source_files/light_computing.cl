float				compute_glare(
		float3 normal_vec,
		float3 light_vec,
		float3 ray_dir,
		float light_intensity,
		int specularity)
{
	float3	perfect_reflect = 2 * normal_vec * dot(normal_vec, light_vec) - light_vec;
	float	perfect_reflect_dot_opposite_ray_dir = dot(perfect_reflect, -ray_dir);
	float	result_intensity = 0;

	if (perfect_reflect_dot_opposite_ray_dir > 0)
		result_intensity = light_intensity *
						   pow(perfect_reflect_dot_opposite_ray_dir / (length(perfect_reflect) * length(-ray_dir)), specularity);
	return result_intensity;
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
		if (intersect_obj->material.specularity != MATERIAL_OPAQUE)
			intensity += compute_glare(normal, light, ray_dir, lights[i].intensity, intersect_obj->material.specularity);
		i++;
	}
	return (intensity);
}
