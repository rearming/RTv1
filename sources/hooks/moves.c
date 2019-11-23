#include "rtv1.h"

static inline void		move_forward(t_camera *camera)
{
	camera->pos.z += MOVE_SPEED * cosf(camera->rotation.y);
	camera->pos.x += MOVE_SPEED * sinf(camera->rotation.y);
}

static inline void		move_backward(t_camera *camera)
{
	camera->pos.z -= MOVE_SPEED * cosf(camera->rotation.y);
	camera->pos.x -= MOVE_SPEED * sinf(camera->rotation.y);
}

static inline void		move_left(t_camera *camera)
{
	camera->pos.z += SIDE_MOVE_SPEED * cosf(camera->rotation.y - (float)M_PI / 2);
	camera->pos.x += SIDE_MOVE_SPEED * sinf(camera->rotation.y - (float)M_PI / 2);
}

static inline void		move_right(t_camera *camera)
{
	camera->pos.z += SIDE_MOVE_SPEED * cosf(camera->rotation.y + (float)M_PI / 2);
	camera->pos.x += SIDE_MOVE_SPEED * sinf(camera->rotation.y + (float)M_PI / 2);
}

inline void				camera_move(t_camera *camera, t_events *events)
{
	if (events->w)
		move_forward(camera);
	if (events->s)
		move_backward(camera);
	if (events->a)
		move_left(camera);
	if (events->d)
		move_right(camera);
	if (events->lshift)
		camera->pos.y -= FLY_SPEED; //todo wtf shift dont repeat?
	if (events->space)
		camera->pos.y += FLY_SPEED;
}
