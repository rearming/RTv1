#include "rtv1.h"
#include "rtv1_cl_header.h"

char		*get_cl_file(size_t *size)
{
	char	*cl_file;
	char	*file_1;
	char	*file_2;

	file_1 = cl_gnl(open("./sources/open_cl/opencl_header.cl", O_RDONLY));
	file_2 = cl_gnl(open("./sources/open_cl/raytracer.cl", O_RDONLY));
	cl_file = ft_strjoin(file_1, file_2);
	free(file_1);
	free(file_2);
	*size = ft_strlen(cl_file);
	return (cl_file);
}

void		cl_set_kernel(t_rtv1 *rtv1, t_opencl *cl)
{
	int		ret;

	ret = 0;
	//todo нужно сделать CL_MEM_READ_ONLY ?
	cl->scene = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(t_object_cl) * rtv1->scene.obj_nbr +
			sizeof(t_light_cl) * rtv1->scene.lights_nbr +
			sizeof(int) * 2, NULL, &ret);
	cl->camera = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(t_camera_cl), NULL, &ret);
	cl->img_data = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			sizeof(int) * WIN_HEIGHT * WIN_WIDTH, NULL, &ret);
	if (ret)
		raise_error(ERR_OPENCL_CREATE_BUFFER);
	ret += clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->scene);
 	ret += clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->camera);
	ret += clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &cl->img_data);
	if (ret)
		raise_error(ERR_OPENCL_SETARG);
}

void		cl_init(t_rtv1 *rtv1)
{
	int			ret;
	char		*cl_file;
	size_t		size;

	if ((ret = clGetPlatformIDs(1, &rtv1->cl.platform_id, &rtv1->cl.ret_num_platforms)))
		raise_error(ERR_OPENCL_GET_PLATFORM_ID);
	if ((ret = clGetDeviceIDs(rtv1->cl.platform_id, CL_DEVICE_TYPE_GPU, 1,
			&rtv1->cl.device_id, &rtv1->cl.ret_num_devices)))
		raise_error(ERR_OPENCL_GET_DEVICE_ID);
	rtv1->cl.context = clCreateContext(NULL, 1, &rtv1->cl.device_id, NULL, NULL, &ret);
	if (ret)
		raise_error(ERR_OPENCL_CREATE_CONTEXT);
	rtv1->cl.queue = clCreateCommandQueue(rtv1->cl.context, rtv1->cl.device_id, 0, &ret);
	if (ret)
		raise_error(ERR_OPENCL_CREATE_QUEUE);
	cl_file = get_cl_file(&size);
	rtv1->cl.program = clCreateProgramWithSource(rtv1->cl.context, 1,
			(const char **)&cl_file, &size, &ret);
	if (ret)
		raise_error(ERR_OPENCL_CREATE_PROGRAM);
	if ((ret = clBuildProgram(rtv1->cl.program, 1, &rtv1->cl.device_id, NULL, NULL, NULL)))
		raise_error(ERR_OPENCL_BUILD_PROGRAM);
	rtv1->cl.kernel = clCreateKernel(rtv1->cl.program, "raytracer", &ret);
	if (ret)
		raise_error(ERR_OPENCL_CREATE_KERNEL);
	free(cl_file);
}

void		cl_clean_memobjs(t_opencl *cl)
{
	clReleaseMemObject(cl->scene); //todo каждый раз не очищать сцену если нет на то причин
	clReleaseMemObject(cl->camera); // то же самое с камерой
	clReleaseMemObject(cl->img_data);
	cl->scene = NULL;
	cl->camera = NULL;
	cl->img_data = NULL;
}

void		cl_render(t_rtv1 *rtv1)
{
	const size_t	kernel_num = WIN_HEIGHT * WIN_WIDTH;
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
