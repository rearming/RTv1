/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:52:41 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:52:42 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parsing.h"

void		get_camera(const char *config, t_camera *out_camera)
{
	if (!(config = ft_strstr(config, "camera")))
		return ;
	out_camera->pos = get_vector(config, STR_POS);
	out_camera->rotation = get_vector(config, STR_ROTATION);
}
