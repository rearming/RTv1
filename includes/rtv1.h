/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:17:40 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 18:17:41 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

extern t_opencl g_opencl;

/*
** Init
*/

void		init_rtv1(t_rtv1 *out_rtv1);
void		init_scene(
		const char *filename,
		t_scene *out_scene,
		t_camera *out_camera);

/*
**	Scene correction
*/

void		correct_lights_intensity(t_scene *scene);
void		correct_objects(t_scene *scene);

/*
** Hooks
*/

void		process_event(SDL_Event *event, t_rtv1 *rtv1);
int			key_press(int keycode, void *param);
int			cross_close(void *param);

/*
**	Translations
*/

void		camera_move(t_camera *camera, t_events *events);

/*
**	Render
*/

void		render(t_rtv1 *rtv1, void (*render_func)(t_rtv1 *));

/*
** Render utils
*/

void		image_put_pixel(int *img_data, t_point point);
void		bresen_line(int *img_data, t_point start, t_point end);
t_point		get_videomem_coord_system_point(t_point raw_point);
cl_float3	canvas_to_viewport(t_rtv1 *rtv1, cl_float3 canvas_point);

/*
**	SDL
*/

void		sdl_clean(t_rtv1 *rtv1);
void		exit_clean(t_rtv1 *rtv1);
void		sdl_loop(t_rtv1 *rtv1);

/*
** OpenCL
*/

char		*get_cl_file(size_t *out_size);

void		cl_init(t_rtv1 *rtv1);
void		render_gpu(t_rtv1 *rtv1);

void		cl_set_kernel(t_rtv1 *rtv1, t_opencl *cl);
void		cl_clean_memobjs(t_opencl *cl);

/*
**	Error management
*/

void		raise_error(int err_code);

/*
**	Debug
*/

void		print_clfloat3(cl_float3 vec);
void		print_debug_info(t_rtv1 *rtv1);
void		print_object(t_object *object);
void		print_cl_build_program_debug(t_opencl *cl);

#endif
