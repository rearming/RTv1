//todo __global to __const

void	image_put_pixel(__global int *img_data, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH
		&& y >= 0 && y < WIN_HEIGHT)
		img_data[x + y * WIN_WIDTH] = color;
	//todo ограничение цвета от COL_BLACK до COL_WHITE ?
}

 __kernel void		raytracer(__global t_scene *scene, __global t_camera *camera, __global int *img_data)
{
	int		g_id = get_global_id(0);

	int		x = g_id % WIN_WIDTH;
	int		y = g_id / WIN_HEIGHT;


	if (x < 500)
		image_put_pixel(img_data, x, y, COL_BLUE);
	else
		image_put_pixel(img_data, x, y, COL_GREEN);
//	for (int i = 0; i < scene->obj_nbr; i++)
//	{
//		if (scene->objects[i].type == SPHERE)
//			printf("obj[%d]: sphere!\n", i);
//	}
//	float3 = canvas_to_viewport(rtv1, (t_vector){result.x, result.y, 0});
//	result.color = trace_ray(rtv1, ray_dir, rtv1->camera.viewport_distance, CL_INFINITY);
//	image_put_pixel(rtv1->img_data, get_videomem_coord_system_point(result));
}
