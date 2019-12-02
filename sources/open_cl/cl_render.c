/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:52:23 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:52:25 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		render_gpu(t_rtv1 *rtv1)
{
	const size_t	kernel_num = WIN_HEIGHT * WIN_WIDTH;
	int				err;

	cl_set_kernel(rtv1, &rtv1->cl);
	if (rtv1->events.info)
		print_debug_info(rtv1);

	err = clEnqueueNDRangeKernel(rtv1->cl.queue,
			rtv1->cl.kernel, 1, NULL, &kernel_num, NULL, 0, NULL, NULL);
	if (err)
		raise_error(ERR_OPENCL_RUN_KERNELS);
	err = clEnqueueReadBuffer(rtv1->cl.queue, rtv1->cl.img_data, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			rtv1->img_data, 0, NULL, NULL);
	if (err)
		raise_error(ERR_OPENCL_READ_BUFFER);
	cl_clean_memobjs(&rtv1->cl);
}
