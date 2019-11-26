/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 02:30:41 by dgreat            #+#    #+#             */
/*   Updated: 2019/11/25 02:30:46 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object	new_plane(
cl_float3 dot,
cl_float3 normal_vector,
int color,
int specularity) {
	t_object plane;

	plane.type = PLANE;
	plane.center = dot;
	plane.normal = normal_vector;
	plane.material.color.value = color;
	plane.material.specularity = specularity;
	return (plane);
}

/*
 * vector determines start and end of cylinder
*/

t_object new_cylinder(
		cl_float3 center,
		cl_float3 rotation,
		cl_float radius,
		cl_float len,
		int color,
		int specularity)
{
	t_object cylinder;

	cylinder.type = CYLINDER;
	cylinder.center = center;
	center = vec_add(center, (cl_float3){{center.x, center.y + 1, center.z}});
	rotate_point(&center, rotation);
	cylinder.cylinder_axis = vec_normalize(center);
	cylinder.len = len; //todo len
	cylinder.radius = radius;
	cylinder.material.color.value = color;
	cylinder.material.specularity = specularity;
	return (cylinder);
}

t_object new_cone(cl_float3 center, float radius, cl_float3 normal_vector,
				  cl_float2 cone_min_max, float angle, int specularity,
				  int color) {
	t_object cone;

	cone.type = CONE;
	cone.center = center;
	cone.radius = radius;
	cone.cylinder_axis = normal_vector;
	cone.cylinder_axis = vec_normalize(cone.cylinder_axis);
	cone.cone_min_max = cone_min_max;
	cone.angle = angle;
	cone.material.color.value = color;
	cone.material.specularity = specularity;
	return (cone);
}
