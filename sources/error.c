#include "rtv1_errors.h"
#include "libft.h"

void	raise_error(int err_code)
{
	if (err_code == ERR_MLX_INIT)
		ft_printf("mlx_init() failed!\n");
	else if (err_code == ERR_MLX_WIN)
		ft_printf("mlx_new_window() failed!\n");
	else if (err_code == ERR_MLX_IMG)
		ft_printf("mlx_new_image() failed!\n");
	else if (err_code == ERR_MALLOC)
		ft_printf("malloc() failed!\n");
	else (ft_printf("UNKNOWN ERROR!\n"));
	exit(err_code);
}
