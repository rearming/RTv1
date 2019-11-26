#include "rtv1.h"

void		print_vector(cl_float3 vec)
{
	ft_printf("x: [%.2f], y: [%.2f], z: [%.2f]\n", vec.x, vec.y, vec.z);
}

void		print_debug_info(t_rtv1 *rtv1)
{
	write(1, "\033[0;33m", 7);
	ft_printf("camera position: ");
	print_vector(rtv1->camera.pos);
	ft_printf("camera rotation: ");
	print_vector(rtv1->camera.rotation);
	write(1, "\033[0m", 4);
	ft_putchar('\n');
}

void		render_gpu(t_rtv1 *rtv1)
{
	const size_t	kernel_num = WIN_HEIGHT * WIN_WIDTH;
	int				ret = 0;

	cl_set_kernel(rtv1, &rtv1->cl);
	if (rtv1->events.info)
		print_debug_info(rtv1);
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
