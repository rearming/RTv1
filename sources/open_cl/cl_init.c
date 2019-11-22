#include "rtv1.h"

char		*get_cl_file(size_t *size)
{
	char	*cl_file;
	char	*file_1;
	char	*file_2;
	char	*file_3;

	file_1 = cl_gnl(open("./includes/rtv1_defines.h", O_RDONLY));
	file_2 = cl_gnl(open("./includes/rtv1_structs.h", O_RDONLY));
	file_3 = cl_gnl(open("./sources/open_cl/raytracer.cl", O_RDONLY));
	ft_sprintf(&cl_file, "%s%s%s%s", "#define FT_OPENCL___ \n\n", file_1, file_2, file_3);
	free(file_1);
	free(file_2);
	free(file_3);
	*size = ft_strlen(cl_file);
	return (cl_file);
}

void		cl_set_kernel(t_rtv1 *rtv1, t_opencl *cl)
{
	int		err;

	err = 0;
	//todo research CL_MEM_USE_HOST_PTR
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

void		print_cl_build_program_debug(t_opencl *cl)
{
	size_t		log_size;
	char		*log;

	clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	log = malloc(log_size);
	clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	printf("OpenCL Log:\n%s\n", log);
}

void		cl_init(t_rtv1 *rtv1)
{
	int			err;
	char		*cl_file;
	size_t		size;

	if ((err = clGetPlatformIDs(1, &rtv1->cl.platform_id, &rtv1->cl.ret_num_platforms)))
		raise_error(ERR_OPENCL_GET_PLATFORM_ID);
	if ((err = clGetDeviceIDs(rtv1->cl.platform_id, CL_DEVICE_TYPE_GPU, 1,
							  &rtv1->cl.device_id, &rtv1->cl.ret_num_devices)))
		raise_error(ERR_OPENCL_GET_DEVICE_ID);
	rtv1->cl.context = clCreateContext(NULL, 1, &rtv1->cl.device_id, NULL, NULL, &err);
	if (err)
		raise_error(ERR_OPENCL_CREATE_CONTEXT);
	rtv1->cl.queue = clCreateCommandQueue(rtv1->cl.context, rtv1->cl.device_id, 0, &err);
	if (err)
		raise_error(ERR_OPENCL_CREATE_QUEUE);
	cl_file = get_cl_file(&size);
	rtv1->cl.program = clCreateProgramWithSource(rtv1->cl.context, 1,
			(const char **)&cl_file, &size, &err);
	if (err)
		raise_error(ERR_OPENCL_CREATE_PROGRAM);
	if ((err = clBuildProgram(rtv1->cl.program, 1, &rtv1->cl.device_id, NULL, NULL, NULL)))
	{
		print_cl_build_program_debug(&rtv1->cl);
		raise_error(ERR_OPENCL_BUILD_PROGRAM);
	}
	rtv1->cl.kernel = clCreateKernel(rtv1->cl.program, "raytracer", &err);
	if (err)
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
