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
** (1 << 2) is CL_MEM_READ_ONLY, well fuck norme =)
*/

void		cl_set_kernel(t_rtv1 *rtv1, t_opencl *cl)
{
	int		err;

	err = 0;
	cl->scene = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_scene), &rtv1->scene, &err);
	cl->objects = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_object) * rtv1->scene.obj_nbr, rtv1->scene.objects, &err);
	cl->lights = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_light) * rtv1->scene.lights_nbr, rtv1->scene.lights, &err);
	cl->camera = clCreateBuffer(cl->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_camera), &rtv1->camera, &err);
	cl->img_data = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(int) * WIN_HEIGHT * WIN_WIDTH, NULL, &err);
	if (err)
		raise_error(ERR_OPENCL_CREATE_BUFFER);
	err += clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->scene);
	err += clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->objects);
	err += clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &cl->lights);
	err += clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &cl->camera);
	err += clSetKernelArg(cl->kernel, 4, sizeof(cl_mem), &cl->img_data);
	if (err)
		raise_error(ERR_OPENCL_SETARG);
}

void		cl_clean_memobjs(t_opencl *cl)
{
	clReleaseMemObject(cl->scene); //todo каждый раз не очищать сцену если нет на то причин
	clReleaseMemObject(cl->camera);
	clReleaseMemObject(cl->img_data);
	cl->scene = NULL;
	cl->camera = NULL;
	cl->img_data = NULL;
}
