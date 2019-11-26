
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

void		rotate_y(float3 *point, float angle)
{
	float3		temp;

	temp = *point;
	point->x = point->x * cos(angle) + point->z * sin(angle);
	point->z = -temp.x * sin(angle) + point->z * cos(angle);
}

void		rotate_x(float3 *point, float angle)
{
	float3		temp;

	temp = *point;
	point->y = point->y * cos(angle) + point->z * sin(angle);
	point->z = -temp.y * sin(angle) + point->z * cos(angle);
}

void		rotate_z(float3 *point, float angle)
{
	float3		temp;

	temp = *point;
	point->x = point->x * cos(angle) - point->y * sin(angle);
	point->y = temp.x * sin(angle) + point->y * cos(angle);
}

float3		degree_to_rad(float3 rotation_degrees)
{
	float3	radians;

	radians.x = rotation_degrees.x * M_PI_180;
	radians.y = rotation_degrees.y * M_PI_180;
	radians.z = rotation_degrees.z * M_PI_180;
	return (radians);
}

void		rotate_point(float3 *point, float3 angle)
{
	angle = degree_to_rad(angle);
	rotate_x(point, angle.x);
	rotate_y(point, angle.y);
	rotate_z(point, angle.z);
}
