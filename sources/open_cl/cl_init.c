/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:52:05 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:52:06 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		cl_compile(t_rtv1 *rtv1)
{
	int			err;
	char		*cl_file;
	size_t		size;

	cl_file = get_cl_file(&size);
	rtv1->cl.program = clCreateProgramWithSource(rtv1->cl.context, 1,
			(const char **)&cl_file, &size, &err);
	if (err)
		raise_error(ERR_OPENCL_CREATE_PROGRAM);
	if ((err = clBuildProgram(
			rtv1->cl.program, 1, &rtv1->cl.device_id, NULL, NULL, NULL)))
	{
		print_cl_build_program_debug(&rtv1->cl);
		raise_error(ERR_OPENCL_BUILD_PROGRAM);
	}
	rtv1->cl.kernel = clCreateKernel(rtv1->cl.program, "raytracer", &err);
	if (err)
		raise_error(ERR_OPENCL_CREATE_KERNEL);
	free(cl_file);
}

void		cl_init(t_rtv1 *rtv1)
{
	int			err;

	err = clGetPlatformIDs(
			1, &rtv1->cl.platform_id, &rtv1->cl.ret_num_platforms);
	if (err)
		raise_error(ERR_OPENCL_GET_PLATFORM_ID);
	err = clGetDeviceIDs(
			rtv1->cl.platform_id, CL_DEVICE_TYPE_GPU, 1,
			&rtv1->cl.device_id, &rtv1->cl.ret_num_devices);
	if (err)
		raise_error(ERR_OPENCL_GET_DEVICE_ID);
	rtv1->cl.context = clCreateContext(
			NULL, 1, &rtv1->cl.device_id, NULL, NULL, &err);
	if (err)
		raise_error(ERR_OPENCL_CREATE_CONTEXT);
	rtv1->cl.queue = clCreateCommandQueue(
			rtv1->cl.context, rtv1->cl.device_id, 0, &err);
	if (err)
		raise_error(ERR_OPENCL_CREATE_QUEUE);
	cl_compile(rtv1);
}
