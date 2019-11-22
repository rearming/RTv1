#include "rtv1.h"

void		render_gpu(t_rtv1 *rtv1)
{
	const size_t	kernel_num = WIN_HEIGHT * WIN_WIDTH;
//	const size_t	kernel_num = 1;
	int				ret = 0;

	cl_set_kernel(rtv1, &rtv1->cl);
	ret = clEnqueueNDRangeKernel(rtv1->cl.queue,
			rtv1->cl.kernel, 1, NULL, &kernel_num, NULL, 0, NULL, NULL);
	if (ret)
		raise_error(ERR_OPENCL_RUN_KERNELS);
	ret = clEnqueueReadBuffer(rtv1->cl.queue, rtv1->cl.img_data, CL_TRUE, 0,
			sizeof(int) * WIN_WIDTH * WIN_HEIGHT,
			rtv1->img_data, 0, NULL, NULL);
	if (ret)
		raise_error(ERR_OPENCL_READ_BUFFER);
	cl_clean_memobjs(&rtv1->cl);
}
