/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:50:19 by sleonard          #+#    #+#             */
/*   Updated: 2019/11/28 17:50:22 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static inline void	move_forward(t_camera *camera, cl_float3 rotation_rad)
{
	camera->pos.z += MOVE_SPEED * cosf(rotation_rad.y);
	camera->pos.x += MOVE_SPEED * sinf(rotation_rad.y);
}

static inline void	move_backward(t_camera *camera, cl_float3 rotation_rad)
{
	camera->pos.z -= MOVE_SPEED * cosf(rotation_rad.y);
	camera->pos.x -= MOVE_SPEED * sinf(rotation_rad.y);
}

static inline void	move_left(t_camera *camera, cl_float3 rotation_rad)
{
	camera->pos.z += SIDE_MOVE_SPEED * cosf(rotation_rad.y - (float)M_PI / 2);
	camera->pos.x += SIDE_MOVE_SPEED * sinf(rotation_rad.y - (float)M_PI / 2);
}

static inline void	move_right(t_camera *camera, cl_float3 rotation_rad)
{
	camera->pos.z += SIDE_MOVE_SPEED * cosf(rotation_rad.y + (float)M_PI / 2);
	camera->pos.x += SIDE_MOVE_SPEED * sinf(rotation_rad.y + (float)M_PI / 2);
}

inline void			camera_move(t_camera *camera, t_events *events)
{
	const cl_float3		cam_rotation_rad = degree_to_rad(camera->rotation);

	if (events->w)
		move_forward(camera, cam_rotation_rad);
	if (events->s)
		move_backward(camera, cam_rotation_rad);
	if (events->a)
		move_left(camera, cam_rotation_rad);
	if (events->d)
		move_right(camera, cam_rotation_rad);
	if (events->lshift)
		camera->pos.y -= FLY_SPEED;
	if (events->space)
		camera->pos.y += FLY_SPEED;
}
