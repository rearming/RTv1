/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_memory_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:52:12 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:52:14 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** norme because of opencl macros
*/

void		cl_set_kernel(t_rtv1 *rtv1, t_opencl *cl)
{
	int		err;

	err = 0;
	g_opencl.scene = clCreateBuffer(g_opencl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_scene), &rtv1->scene, &err);
	g_opencl.objects = clCreateBuffer(g_opencl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_object) * rtv1->scene.obj_nbr, rtv1->scene.objects, &err);
	g_opencl.lights = clCreateBuffer(g_opencl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_light) * rtv1->scene.lights_nbr, rtv1->scene.lights, &err);
	g_opencl.camera = clCreateBuffer(g_opencl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_camera), &rtv1->camera, &err);
	g_opencl.img_data = clCreateBuffer(g_opencl.context, CL_MEM_READ_WRITE,
			sizeof(int) * WIN_HEIGHT * WIN_WIDTH, NULL, &err);
	if (err)
		raise_error(ERR_OPENCL_CREATE_BUFFER);
	err += clSetKernelArg(g_opencl.kernel, 0, sizeof(cl_mem), &g_opencl.scene);
	err += clSetKernelArg(g_opencl.kernel, 1, sizeof(cl_mem), &g_opencl.objects);
	err += clSetKernelArg(g_opencl.kernel, 2, sizeof(cl_mem), &g_opencl.lights);
	err += clSetKernelArg(g_opencl.kernel, 3, sizeof(cl_mem), &g_opencl.camera);
	err += clSetKernelArg(g_opencl.kernel, 4, sizeof(cl_mem), &g_opencl.img_data);
	if (err)
		raise_error(ERR_OPENCL_SETARG);
}

void		cl_clean_memobjs(t_opencl *cl)
{
	clReleaseMemObject(g_opencl.scene); //todo каждый раз не очищать сцену если нет на то причин
	clReleaseMemObject(g_opencl.camera);
	clReleaseMemObject(g_opencl.img_data);
	g_opencl.scene = NULL;
	g_opencl.camera = NULL;
	g_opencl.img_data = NULL;
}
