#include "rtv1.h"

t_point		get_videomem_coord_system_point(t_point raw_point)
{
	t_point		result;

	result.x = WIN_WIDTH / 2 + raw_point.x;
	result.y = WIN_HEIGHT / 2 + raw_point.y;
	result.color = raw_point.color;
	return (result);
}

t_vector			canvas_to_viewport(t_rtv1 *rtv1, t_vector canvas_point)
{
	return ((t_vector)
	{
		.x = canvas_point.x * rtv1->camera.viewport_width / WIN_WIDTH,
		.y = canvas_point.y * rtv1->camera.viewport_height / WIN_HEIGHT,
		rtv1->camera.viewport_distance
	});
}

void	image_put_pixel(int *img_data, t_point point)
{
	if (point.x >= 0 && point.x < WIN_WIDTH
	&& point.y >= 0 && point.y < WIN_HEIGHT)
		img_data[point.x + point.y * WIN_WIDTH] = point.color;
	//todo ограничение цвета от COL_BLACK до COL_WHITE ?
}
