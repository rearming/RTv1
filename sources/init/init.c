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

void		init_scene(t_scene *out_scene)
{
	out_scene->objects = 3;
	out_scene->spheres = malloc(sizeof(*out_scene->spheres) * (out_scene->objects));
	out_scene->spheres[0] = (t_sphere){(t_vector){0, -1, 3}, 1, COL_RED};
	out_scene->spheres[1] = (t_sphere){(t_vector){2, 0, 4}, 1, COL_BLUE};
	out_scene->spheres[2] = (t_sphere){(t_vector){-2, 0, 4}, 1, COL_GREEN};
}

void		init_rtv1(t_rtv1 *out_rtv1)
{
	init_sdl(&out_rtv1->sdl);
	init_scene(&out_rtv1->scene);

	out_rtv1->camera = (t_camera){
			.pos = (t_vector){0, 0, 0},
			.viewport_distance = 1,
			.viewport_width = 1,
			.viewport_height = 1
	};

}
