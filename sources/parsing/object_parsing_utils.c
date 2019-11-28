/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_parsing_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:53:07 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:53:08 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parsing.h"

cl_float3	get_vector(const char *config, const char *field_name)
{
	cl_float3	result;

	if (!(config = ft_strstr(config, field_name)))
		raise_error(ERR_INV_SCENE_SYNTAX);
	config += ft_strlen(field_name);
	result.x = (float)ft_strtod(config);
	while (*config && *config != ',')
		++config;
	if (*config != ',')
		raise_error(ERR_INV_SCENE_SYNTAX);
	result.y = (float)ft_strtod(++config);
	while (*config && *config != ',')
		config++;
	if (*config != ',')
		raise_error(ERR_INV_SCENE_SYNTAX);
	result.z = (float)ft_strtod(++config);
	while (*config && *config != ')')
		config++;
	if (*config != ')')
		raise_error(ERR_INV_SCENE_SYNTAX);
	return (result);
}

cl_float	get_float_num(const char *config, const char *field_name)
{
	cl_float	result;

	if (!(config = ft_strstr(config, field_name)))
		raise_error(ERR_INV_SCENE_SYNTAX);
	config += ft_strlen(field_name);
	result = (float)ft_strtod(config);
	while (*config && *config != ')')
		config++;
	if (*config != ')')
		raise_error(ERR_INV_SCENE_SYNTAX);
	return (result);
}

cl_int		get_int_num(const char *config, const char *field_name, int base)
{
	cl_int	result;

	if (!(config = ft_strstr(config, field_name)))
		raise_error(ERR_INV_SCENE_SYNTAX);
	config += ft_strlen(field_name);
	result = (float)ft_atoll_base(config, base);
	while (*config && *config != ')')
		config++;
	if (*config != ')')
		raise_error(ERR_INV_SCENE_SYNTAX);
	return (result);
}

char		*get_string(const char *config, const char *field_name)
{
	char			*str_type;

	if (!(config = ft_strstr(config, field_name)))
		raise_error(ERR_INV_SCENE_SYNTAX);
	config += ft_strlen(field_name);
	str_type = ft_strsub(config, 0, ft_strlen_char(config, ')'));
	return (str_type);
}
