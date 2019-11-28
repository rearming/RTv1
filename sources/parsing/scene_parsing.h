/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:53:31 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:53:33 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_PARSING_H
# define SCENE_PARSING_H

# include "rtv1.h"

cl_float3	get_vector(const char *config, const char *field_name);
cl_float	get_float_num(const char *config, const char *field_name);
cl_int		get_int_num(const char *config, const char *field_name, int base);
char		*get_string(const char *config, const char *field_name);

t_object	get_object(const char *config, const char *objname);
t_light		get_light(const char *config);
void		get_camera(const char *config, t_camera *out_camera);

int			get_lights_by_name(
		const char *config,
		t_light *lights,
		int	*out_light_index);

int			get_objects_by_name(
		const char *config,
		const char *objname,
		t_object *objects,
		int	*out_obj_index);

#endif
