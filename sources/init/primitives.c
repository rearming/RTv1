/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 02:30:41 by dgreat            #+#    #+#             */
/*   Updated: 2019/11/27 16:14:22 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_object	new_sphere(
		cl_float3 center,
		float radius,
		int color,
		int specularity)
{
	t_object	sphere;

	sphere.type = SPHERE;
	sphere.center = center;
	sphere.radius = radius;
	sphere.material.color.value = color;
	sphere.material.specularity = specularity;
	return (sphere);
}

t_object	new_plane(
		cl_float3 dot,
		cl_float3 normal_vector,
		int color,
		int specularity)
{
	t_object plane;

	plane.type = PLANE;
	plane.center = dot;
	plane.normal = normal_vector;
	plane.material.color.value = color;
	plane.material.specularity = specularity;
	return (plane);
}

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
	cylinder.axis = vec_normalize(center);
	cylinder.len = len;
	cylinder.radius = radius;
	cylinder.material.color.value = color;
	cylinder.material.specularity = specularity;
	return (cylinder);
}

t_object new_cone(
		cl_float3 center,
		float radius,
		cl_float3 rotation,
		cl_float angle,
		cl_float len,
		int specularity,
		int color)
{
	t_object cone;

	cone.type = CONE;
	cone.center = center;
	cone.radius = radius;
	center = vec_add(center, (cl_float3){{center.x, center.y + 1, center.z}});
	rotate_point(&center, rotation);
	cone.axis = vec_normalize(center);
	cone.len = len;
	cone.angle = angle * (float)M_PI_180;
	cone.material.color.value = color;
	cone.material.specularity = specularity;
	return (cone);
}
