
int 				in_range_inclusive(float number, float min, float max)
{
	if (number >= min && number <= max)
		return (TRUE);
	else
		return (FALSE);
}

float3			canvas_to_viewport(__constant t_camera *camera, float3 canvas_point)
{
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

	if (intensity > 1)
		intensity = 1;
	if (intensity < 0)
		intensity = 0;
	result_color.rgb.a = color.rgb.a;
	result_color.rgb.r = color.rgb.r * intensity;
	result_color.rgb.g = color.rgb.g * intensity;
	result_color.rgb.b = color.rgb.b * intensity;
	return result_color.value;
}
