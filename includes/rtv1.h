#ifndef RTV1_H
# define RTV1_H

#include <stdio.h>
#include <mlx.h>

#include "libft.h"
#include "rtv1_structs.h"
#include "rtv1_defines.h"
#include "rtv1_key_codes.h"
#include "rtv1_errors.h"
#include "math.h"

/*
** Init
*/

void	init_mlx(t_rtv1 *out_rtv1);

/*
** Hooks
*/

int		key_press(int keycode, void *param);
int		cross_close(void *param);

/*
** Render utils
*/

void	image_put_pixel(int *mlx_img, t_point point);
void	bresen_line(int *img_data, t_point start, t_point end);

/*
**	Error management
*/

void	raise_error(int err_code);

#endif
