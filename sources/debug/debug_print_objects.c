/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_objects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:00:16 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 18:00:18 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		print_sphere(t_object *sphere)
{
	ft_printf("\n<--- SPHERE --->\n");
	ft_printf("center:\n");
	print_clfloat3(sphere->center);
	ft_printf("radius: [%.2f]\n", sphere->radius);
}

static void		print_plane(t_object *plane)
{
	ft_printf("\n<--- PLANE --->\n");
	ft_printf("center:\n");
	print_clfloat3(plane->center);
	ft_printf("normal:\n");
	print_clfloat3(plane->normal);
}

static void		print_cylinder(t_object *cylinder)
{
	ft_printf("\n<--- CYLINDER --->\n");
	ft_printf("center:\n");
	print_clfloat3(cylinder->center);
	ft_printf("rotation:\n");
	print_clfloat3(cylinder->axis);
	ft_printf("len: [%.2f]\n", cylinder->len);
}

static void		print_cone(t_object *cone)
{
	ft_printf("\n<--- CONE --->\n");
	ft_printf("center:\n");
	print_clfloat3(cone->center);
	ft_printf("rotation:\n");
	print_clfloat3(cone->axis);
	ft_printf("len: [%.2f]\n", cone->len);
	ft_printf("angle: [%.2f]\n", cone->angle);
}

void			print_object(t_object *object)
{
	if (object->type == SPHERE)
		print_sphere(object);
	else if (object->type == PLANE)
		print_plane(object);
	else if (object->type == CYLINDER)
		print_cylinder(object);
	else if (object->type == CONE)
		print_cone(object);
	else
		ft_printf_fd(STDERR_FILENO, "CAN'T PRINT UNKNOWN OBJECT");
	ft_printf("material.color: [0x%X]\n", object->material.color.value);
	ft_printf("material.specular: [%i]\n", object->material.specularity);
}
