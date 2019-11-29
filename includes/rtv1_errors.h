/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 19:11:02 by sleonard          #+#    #+#             */
/*   Updated: 2019/06/03 09:34:21 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_ERRORS_H
# define RTV1_ERRORS_H

# define ERR_INV_ARGS_NUM 5
# define ERR_INV_FILE 6

# define ERR_MALLOC 7

# define ERR_SDL_INIT 8
# define ERR_SDL_WIN 9
# define ERR_SDL_RENDER 10
# define ERR_SDL_TEXTURE_CREATE 11

# define ERR_USAGE 12
# define ERR_OPENCL 13
# define ERR_OPENCL_CLEAN 14
# define ERR_OPENCL_SETARG 15
# define ERR_OPENCL_GET_PLATFORM_ID 16
# define ERR_OPENCL_GET_DEVICE_ID 17
# define ERR_OPENCL_CREATE_CONTEXT 18
# define ERR_OPENCL_CREATE_QUEUE 19
# define ERR_OPENCL_CREATE_PROGRAM 20
# define ERR_OPENCL_BUILD_PROGRAM 21
# define ERR_OPENCL_CREATE_KERNEL 22
# define ERR_OPENCL_CREATE_BUFFER 23
# define ERR_OPENCL_RUN_KERNELS 24
# define ERR_OPENCL_READ_BUFFER 25

# define ERR_UNKNOWN_OBJ 26

# define ERR_INV_SCENE_SYNTAX 27
# define ERR_INV_OBJ_DEFINITION 28
# define ERR_SCENE_NO_OBJECTS 29

#endif
