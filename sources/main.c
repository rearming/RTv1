/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:54:18 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:54:20 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			main(int argc, char **argv)
{
	t_rtv1		rtv1;

	if (argc != 2)
		raise_error(ERR_INV_ARGS_NUM);
	init_rtv1(&rtv1);
	init_scene(argv[1], &rtv1.scene, &rtv1.camera);
	cl_init(&rtv1);
	render(&rtv1, &render_gpu);
	sdl_loop(&rtv1);
	return (0);
}
