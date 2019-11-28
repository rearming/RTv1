/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_getter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:52:49 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:52:50 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parsing.h"

static t_light_type		get_light_type(char *str_light_type)
{
	t_light_type	type;

	type = NOT_SET;
	if (ft_strequ(str_light_type, STR_POINT_LIGHT))
		type = POINT;
	else if (ft_strequ(str_light_type, STR_DIRECTIONAL_LIGHT))
		type = DIRECTIONAL;
	else if (ft_strequ(str_light_type, STR_AMBIET_LIGHT))
		type = AMBIENT;
	else
		raise_error(ERR_INV_SCENE_SYNTAX);
	free(str_light_type);
	return (type);
}

t_light					get_light(const char *config)
{
	t_light		light;

	light.type = get_light_type(get_string(config, "type("));
	light.intensity = get_float_num(config, "intensity(");
	light.pos = (cl_float3){{0}};
	light.dir = (cl_float3){{0}};
	if (light.type == POINT)
		light.pos = get_vector(config, STR_POS);
	if (light.type == DIRECTIONAL)
		light.dir = get_vector(config, "dir(");
	return (light);
}
