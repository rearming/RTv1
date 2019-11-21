#ifndef RTV1_H
# define RTV1_H

# include <stdio.h>
# include <math.h>
# include <SDL.h>

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# include "libft.h"
# include "rtv1_structs.h"
# include "rtv1_defines.h"
# include "rtv1_errors.h"

# include "math_utils.h"

/*
** Init
*/

void		init_rtv1(t_rtv1 *out_rtv1);

/*
** Hooks
*/

int			key_press(int keycode, void *param);
int			cross_close(void *param);

/*
**	Render
*/

void render(t_rtv1 *rtv1, void (*render_func)(t_rtv1 *));

/*
** Raytracing objects
*/

void		ray_sphere_intersect(t_rtv1 *rtv1, t_vector ray_dir,
		const t_sphere *sphere, float *out_x1, float *out_x2);

/*
** Render utils
*/

void		image_put_pixel(int *img_data, t_point point);
void		bresen_line(int *img_data, t_point start, t_point end);
t_point		get_videomem_coord_system_point(t_point raw_point);
t_vector	canvas_to_viewport(t_rtv1 *rtv1, t_vector canvas_point);

/*
**	SDL
*/

void		sdl_clean(t_rtv1 *rtv1);
void		sdl_exit(t_rtv1 *rtv1);
void		sdl_loop(t_rtv1 *rtv1);

/*
** OpenCL
*/

char		*cl_gnl(int fd);
void		cl_init(t_rtv1 *rtv1);
void		cl_render(t_rtv1 *rtv1);

/*
**	Error management
*/

void		raise_error(int err_code);

#endif
