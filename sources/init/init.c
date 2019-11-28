#include "rtv1.h"

void		init_sdl(t_sdl *out_sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		raise_error(ERR_SDL_INIT);
	if (!(out_sdl->win = SDL_CreateWindow(WIN_TITLE,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH * SCALE_WIDTH, WIN_HEIGHT * SCALE_HEIGHT,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)))
		raise_error(ERR_SDL_WIN);
	if (!(out_sdl->rend = SDL_CreateRenderer(out_sdl->win, -1, SDL_RENDERER_SOFTWARE)))
		raise_error(ERR_SDL_RENDER);
	if (!(out_sdl->texture = SDL_CreateTexture(out_sdl->rend, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_WIDTH, WIN_HEIGHT)))
		raise_error(ERR_SDL_TEXTURE_CREATE);
}

void		init_events(t_events *events)
{
	events->w = FALSE;
	events->a = FALSE;
	events->s = FALSE;
	events->d = FALSE;
	events->info = FALSE;
	events->space = FALSE;
	events->lshift = FALSE;
}

void		init_rtv1(t_rtv1 *out_rtv1)
{
	init_sdl(&out_rtv1->sdl);
	init_events(&out_rtv1->events);

	out_rtv1->camera = (t_camera)
	{
		.pos = (cl_float3){{-17.5, 1.5, 20}},
		.rotation = (cl_float3){{5, -220, 0}},
		.viewport_distance = 1,
		.viewport_width = WIN_RATIO < 1 ? D_I_MAZOHIN : 1,
		.viewport_height = WIN_RATIO > 1 ? D_E_KARMATSKIY : 1
	};
}
