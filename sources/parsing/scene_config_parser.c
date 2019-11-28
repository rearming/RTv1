/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_config_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:53:25 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:53:26 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parsing.h"

static int	count_all_objects(const char *config)
{
	int				obj_count;

	obj_count = 0;
	obj_count += get_objects_by_name(config, STR_CONE, NULL, NULL);
	obj_count += get_objects_by_name(config, STR_PLANE, NULL, NULL);
	obj_count += get_objects_by_name(config, STR_CYLINDER, NULL, NULL);
	obj_count += get_objects_by_name(config, STR_SPHERE, NULL, NULL);
	return (obj_count);
}

void		init_scene(
		const char *filename,
		t_scene *out_scene,
		t_camera *out_camera)
{
	char		*config;
	int			obj_index;
	int			light_index;

	config = ft_readfile(open(filename, O_RDONLY), NULL);
	out_scene->obj_nbr = count_all_objects(config);
	if (!(out_scene->objects = malloc(sizeof(t_object) * out_scene->obj_nbr)))
		raise_error(ERR_MALLOC);
	obj_index = 0;
	get_objects_by_name(config, STR_CONE, out_scene->objects, &obj_index);
	get_objects_by_name(config, STR_PLANE, out_scene->objects, &obj_index);
	get_objects_by_name(config, STR_CYLINDER, out_scene->objects, &obj_index);
	get_objects_by_name(config, STR_SPHERE, out_scene->objects, &obj_index);
	out_scene->lights_nbr = get_lights_by_name(config, NULL, NULL);
	if (!(out_scene->lights = malloc(sizeof(t_light) * out_scene->lights_nbr)))
		raise_error(ERR_MALLOC);
	light_index = 0;
	get_lights_by_name(config, out_scene->lights, &light_index);
	get_camera(config, out_camera);
	correct_lights_intensity(out_scene);
	correct_objects(out_scene);
	free(config);
}
