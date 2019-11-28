/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:50:50 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:50:53 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		correct_objects(t_scene *scene)
{
	int		i;

	i = 0;
	while (i < scene->obj_nbr)
	{
		if (scene->objects[i].type == CYLINDER)
		{
			scene->objects[i].center = vec_add(scene->objects[i].center,
				(cl_float3){{scene->objects[i].center.x,
				scene->objects[i].center.y + 1, scene->objects[i].center.z}});
			rotate_point(&scene->objects[i].center, scene->objects[i].axis);
			scene->objects[i].axis = vec_normalize(scene->objects[i].center);
		}
		else if (scene->objects[i].type == CONE)
		{
			scene->objects[i].center = vec_add(scene->objects[i].center,
				(cl_float3){{scene->objects[i].center.x,
				scene->objects[i].center.y + 1, scene->objects[i].center.z}});
			rotate_point(&scene->objects[i].center, scene->objects[i].axis);
			scene->objects[i].axis = vec_normalize(scene->objects[i].center);
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
