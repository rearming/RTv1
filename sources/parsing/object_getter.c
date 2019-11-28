/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:53:00 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:53:02 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parsing.h"

static void		get_sphere(const char *config, t_object *out_sphere)
{
	out_sphere->type = SPHERE;
	out_sphere->center = get_vector(config, STR_CENTER);
	out_sphere->radius = get_float_num(config, STR_RADIUS);
	out_sphere->material.color.value = get_int_num(config, STR_COLOR, 16);
	out_sphere->material.specularity = get_int_num(config, STR_SPECULAR, 10);
}

static void		get_plane(const char *config, t_object *out_plane)
{
	out_plane->type = PLANE;
	out_plane->center = get_vector(config, STR_POS);
	out_plane->normal = get_vector(config, STR_NORMAL);
	out_plane->material.color.value = get_int_num(config, STR_COLOR, 16);
	out_plane->material.specularity = get_int_num(config, STR_SPECULAR, 10);
}

static void		get_cylinder(const char *config, t_object *out_cylinder)
{
	out_cylinder->type = CYLINDER;
	out_cylinder->center = get_vector(config, STR_POS);
	out_cylinder->axis = get_vector(config, STR_ROTATION);
	out_cylinder->radius = get_float_num(config, STR_RADIUS);
	out_cylinder->len = get_float_num(config, STR_LENGTH);
	out_cylinder->material.color.value = get_int_num(config, STR_COLOR, 16);
	out_cylinder->material.specularity = get_int_num(config, STR_SPECULAR, 10);
}

static void		get_cone(const char *config, t_object *out_cone)
{
	out_cone->type = CONE;
	out_cone->center = get_vector(config, STR_POS);
	out_cone->axis = get_vector(config, STR_ROTATION);
	out_cone->angle = get_float_num(config, STR_ANGLE);
	out_cone->len = get_float_num(config, STR_LENGTH);
	out_cone->material.color.value = get_int_num(config, STR_COLOR, 16);
	out_cone->material.specularity = get_int_num(config, STR_SPECULAR, 10);
}

t_object		get_object(const char *config, const char *objname)
{
	t_object	object;

	object = (t_object){
			NOT_SET, 0, (t_material){{0}, NOT_SET},
			(cl_float3){{0}}, 0, (cl_float3){{0}}, 0, (cl_float3){{0}}};
	if (objname == STR_SPHERE)
		get_sphere(config, &object);
	else if (objname == STR_PLANE)
		get_plane(config, &object);
	else if (objname == STR_CYLINDER)
		get_cylinder(config, &object);
	else if (objname == STR_CONE)
		get_cone(config, &object);
	else
	{
		ft_printf_fd(STDERR_FILENO, "object: [%s]\n", objname);
		raise_error(ERR_UNKNOWN_OBJ);
	}
	return (object);
}
