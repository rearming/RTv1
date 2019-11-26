#include "rtv1.h"

void		sdl_loop(t_rtv1 *rtv1)
{
	SDL_Event		event;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (21)
	{
		Uint32 timeout = SDL_GetTicks() + 30;
		//todo correct camera rotation / movement
		while (SDL_PollEvent(&event) && (event.type == SDL_KEYUP || !SDL_TICKS_PASSED(SDL_GetTicks(), timeout)))
		{
			process_event(&event, rtv1);
		}
		if (event.type == SDL_QUIT)
			break ;
	}
}
