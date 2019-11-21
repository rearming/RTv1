#include "rtv1.h"

void		process_event(SDL_Event *event, t_rtv1 *rtv1)
{
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			sdl_exit(rtv1);
	}
}

void		sdl_loop(t_rtv1 *rtv1)
{
	SDL_Event		event;

	while (21)
	{
		while (SDL_PollEvent(&event))
			process_event(&event, rtv1);
		if (event.type == SDL_QUIT)
			break ;
	}
}
