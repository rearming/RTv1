/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:54:02 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:54:04 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1_errors.h"
#include "libft.h"

static void		raise_error2(int err_code)
{
	if (err_code == ERR_OPENCL_BUILD_PROGRAM)
		ft_printf_fd(STDERR_FILENO, "clBuildProgram failed\n");
	else if (err_code == ERR_OPENCL_CREATE_KERNEL)
		ft_printf_fd(STDERR_FILENO, "clCreateKernel failed\n");
	else if (err_code == ERR_OPENCL_CREATE_BUFFER)
		ft_printf_fd(STDERR_FILENO, "clCreateBuffer failed\n");
	else if (err_code == ERR_OPENCL_SETARG)
		ft_printf_fd(STDERR_FILENO, "clSetKernelArg failed\n");
	else if (err_code == ERR_INV_ARGS_NUM)
		ft_printf_fd(STDERR_FILENO, "Invalid arguments number,"
			"expected 1 argument for *.rtv1 scene file!\n");
	else if (err_code == ERR_UNKNOWN_OBJ)
		ft_printf_fd(STDERR_FILENO, "Unknown object!\n");
	else if (err_code == ERR_INV_SCENE_SYNTAX)
		ft_printf_fd(STDERR_FILENO, "Invalid scene file syntax!\n");
	else
		ft_printf_fd(STDERR_FILENO, "UNKNOWN ERROR!\n");
}

void			raise_error(int err_code)
{
	if (err_code == ERR_SDL_INIT)
		ft_printf_fd(STDERR_FILENO, "SDL_Init failed.\n");
	else if (err_code == ERR_SDL_WIN)
		ft_printf_fd(STDERR_FILENO, "SDL_Create_Window failed.\n");
	else if (err_code == ERR_SDL_RENDER)
		ft_printf_fd(STDERR_FILENO, "SDL_Create_Renderer failed.\n");
	else if (err_code == ERR_SDL_TEXTURE_CREATE)
		ft_printf_fd(STDERR_FILENO, "SDL_Create_Texture failed.\n");
	else if (err_code == ERR_MALLOC)
		ft_printf_fd(STDERR_FILENO, "malloc() failed!\n");
	else if (err_code == ERR_OPENCL)
		ft_printf_fd(STDERR_FILENO, "something went wrong in OpenCL!\n");
	else if (err_code == ERR_OPENCL_GET_PLATFORM_ID)
		ft_printf_fd(STDERR_FILENO, "clGetPlatformIDs failed!\n");
	else if (err_code == ERR_OPENCL_GET_DEVICE_ID)
		ft_printf_fd(STDERR_FILENO, "clGetDeviceIDs failed!\n");
	else if (err_code == ERR_OPENCL_CREATE_CONTEXT)
		ft_printf_fd(STDERR_FILENO, "clCreateContext failed!\n");
	else if (err_code == ERR_OPENCL_CREATE_QUEUE)
		ft_printf_fd(STDERR_FILENO, "clCreateCommandQueue failed\n");
	else if (err_code == ERR_OPENCL_CREATE_PROGRAM)
		ft_printf_fd(STDERR_FILENO, "clCreateProgramWithSource failed\n");
	raise_error2(err_code);
	exit(err_code);
}
