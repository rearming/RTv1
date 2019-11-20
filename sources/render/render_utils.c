#include "rtv1.h"

void	image_put_pixel(int *mlx_img, t_point point)
{
	if (point.x >= 0 && point.x < WIN_WIDTH && point.y >= 0 && point.y < WIN_HEIGHT)
		mlx_img[point.x + point.y * WIN_WIDTH] = point.color;
}
