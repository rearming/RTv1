/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:59:08 by sleonard          #+#    #+#             */
/*   Updated: 2019/05/11 00:01:12 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		rotate_y(cl_float3 *point, double angle)
{
	cl_float3		temp;

	temp = *point;
	point->x = point->x * cos(angle) + point->z * sin(angle);
	point->z = -temp.x * sin(angle) + point->z * cos(angle);
}

void		rotate_x(cl_float3 *point, double angle)
{
	cl_float3		temp;

	temp = *point;
	point->y = point->y * cos(angle) + point->z * sin(angle);
	point->z = -temp.y * sin(angle) + point->z * cos(angle);
}

void		rotate_z(cl_float3 *point, double angle)
{
	cl_float3		temp;

	temp = *point;
	point->x = point->x * cos(angle) - point->y * sin(angle);
	point->y = temp.x * sin(angle) + point->y * cos(angle);
}

void		rotate_point(cl_float3 *point, cl_float3 angle)
{
	rotate_x(point, angle.x);
	rotate_y(point, angle.y);
	rotate_z(point, angle.z);
}
