#include "rtv1.h"

void		add_key_event(t_events *events, SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_W)
		events->w = TRUE;
	if (scancode == SDL_SCANCODE_S)
		events->s = TRUE;
	if (scancode == SDL_SCANCODE_A)
		events->a = TRUE;
	if (scancode == SDL_SCANCODE_D)
		events->d = TRUE;
	if (scancode == SDL_SCANCODE_SPACE)
		events->space = TRUE;
	if (scancode == SDL_SCANCODE_X)
		events->lshift = TRUE;
}

void		remove_key_event(t_events *events, SDL_Scancode scancode)
{
	if (scancode == SDL_SCANCODE_W)
		events->w = FALSE;
	if (scancode == SDL_SCANCODE_S)
		events->s = FALSE;
	if (scancode == SDL_SCANCODE_A)
		events->a = FALSE;
	if (scancode == SDL_SCANCODE_D)
		events->d = FALSE;
	if (scancode == SDL_SCANCODE_SPACE)
		events->space = FALSE;
	if (scancode == SDL_SCANCODE_X)
		events->lshift = FALSE;
}

t_bool		any_key_pressed(t_events *events)
{
	return (events->w || events->a || events->s || events->d
			|| events->space || events->lshift);
}

void		process_event(SDL_Event *event, t_rtv1 *rtv1)
{
	if (event->type == SDL_KEYUP)
		remove_key_event(&rtv1->events, event->key.keysym.scancode);
	else if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			exit_clean(rtv1);
		if (event->key.keysym.scancode == SDL_SCANCODE_I)
			rtv1->events.info = !rtv1->events.info;
		if (event->key.keysym.scancode == SDL_SCANCODE_M)
			SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode());
		add_key_event(&rtv1->events, event->key.keysym.scancode);
	}
	else if (event->type == SDL_MOUSEMOTION)
	{
		rtv1->camera.rotation.x -=
				event->motion.yrel * ROTATION_SPEED * WIN_RATIO;
		rtv1->camera.rotation.y += event->motion.xrel * ROTATION_SPEED;
	}
	if (any_key_pressed(&rtv1->events) || event->type == SDL_MOUSEMOTION)
	{
		camera_move(&rtv1->camera, &rtv1->events);
		render(rtv1, render_gpu);
	}
}
