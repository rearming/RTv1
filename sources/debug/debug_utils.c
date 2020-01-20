/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:00:30 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 18:00:33 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		print_clfloat3(cl_float3 vec)
{
	ft_printf("x: [%.2f], y: [%.2f], z: [%.2f]\n", vec.x, vec.y, vec.z);
}

void		print_debug_info(t_rtv1 *rtv1)
{
	ft_printf("\033[0;33m");
	ft_printf("camera position: ");
	print_clfloat3(rtv1->camera.pos);
	ft_printf("camera rotation: ");
	print_clfloat3(rtv1->camera.rotation);
	ft_printf("\033[0m");
	ft_putchar('\n');
}

void		print_cl_build_program_debug(t_opencl *cl)
{
	size_t		log_size;
	char		*log;

	clGetProgramBuildInfo(g_opencl.program, g_opencl.device_id,
			CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	if (!(log = malloc(log_size)))
		raise_error(ERR_MALLOC);
	clGetProgramBuildInfo(g_opencl.program, g_opencl.device_id,
			CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	ft_printf("OpenCL Log:\n%s\n", log);
	free(log);
}
