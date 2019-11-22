#include "rtv1.h"

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
