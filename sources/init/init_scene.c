/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:50:50 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/29 18:41:51 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		correct_objects(t_scene *scene)
{
	int			i;
	cl_float3	rotation;

	i = 0;
	while (i < scene->obj_nbr)
	{
		if (scene->objects[i].type == CYLINDER)
		{
			rotation = (cl_float3){{0, scene->objects[i].center.y + 1, 0}};
			rotate_point(&rotation, scene->objects[i].axis);
			scene->objects[i].axis = vec_normalize(rotation);
		}
		else if (scene->objects[i].type == CONE)
		{
			rotation = (cl_float3){{0, scene->objects[i].center.y + 1, 0}};
			rotate_point(&rotation, scene->objects[i].axis);
			scene->objects[i].axis = vec_normalize(rotation);
		}
		if (RTV1_DEBUG)
			print_object(&scene->objects[i]);
		i++;
	}
}

void		correct_lights_intensity(t_scene *scene)
{
	int		i;

	i = 0;
	while (i < scene->lights_nbr)
	{
		scene->lights[i].intensity /= scene->lights_nbr;
		i++;
	}
}
