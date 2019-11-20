#include "rtv1.h"

void	init_mlx(t_rtv1 *out_rtv1)
{
	int		dummie_for_mlx;

	if (!(out_rtv1->mlx_ptr = mlx_init()))
		raise_error(ERR_MLX_INIT);
	if (!(out_rtv1->win_ptr = mlx_new_window(
			out_rtv1->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Dota 4")))
		raise_error(ERR_MLX_WIN);
	if (!(out_rtv1->mlx_img =
				  mlx_new_image(out_rtv1->win_ptr, WIN_WIDTH, WIN_HEIGHT)))
		raise_error(ERR_MLX_IMG);
	if (!(out_rtv1->img_data = (int*)mlx_get_data_addr(out_rtv1->mlx_img,
			&dummie_for_mlx, &dummie_for_mlx, &dummie_for_mlx)))
		raise_error(ERR_MLX_IMG_DATA);
}