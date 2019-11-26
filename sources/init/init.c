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

void		init_scene(t_scene *out_scene)
{
	out_scene->obj_nbr = 5;
	if (!(out_scene->objects = malloc(sizeof(t_object) * (out_scene->obj_nbr))))
		raise_error(ERR_MALLOC);
	out_scene->objects[0] = new_sphere((cl_float3){{0, -1, 3}}, 1, COL_RED, 500);
//	out_scene->objects[2] = new_sphere((cl_float3){{-2, 0, 4}}, 1, COL_BLUE, 10);
//	out_scene->objects[1] = new_sphere((cl_float3){{2, 0,  4}}, 1, COL_GREEN, 500);
//	out_scene->objects[3] = new_sphere((cl_float3){{0, -5001, 0}}, 5000, COL_YELLOW, 1000);
	out_scene->objects[1] = new_cylinder((cl_float3){{0, 0, 0}},(cl_float3) {{0, 0, 0}}, 1, 1, COL_PURPLE, 200);
	out_scene->objects[2] = new_cylinder((cl_float3){{0, 0, 0}},(cl_float3) {{45, 0, 0}}, 1, 1, COL_GREEN, 200);
	out_scene->objects[3] = new_cylinder((cl_float3){{0, 0, 0}},(cl_float3) {{0, 0, 90}}, 1, 1, COL_YELLOW, 200);
//	out_scene->objects[0] = new_cone((cl_float3){{1, 0, 0}}, 0.1f, (cl_float3){{0, 1.f, 0}}, (cl_float2){{2, 3}}, M_PI / 6, COL_PURPLE, 200);
	out_scene->objects[4] = new_plane((cl_float3){{0, -4, 0}}, (cl_float3){{0, 1, 0}}, COL_WHITE, 500);

	out_scene->lights_nbr = 3;
	if (!(out_scene->lights = malloc(sizeof(t_light) * out_scene->lights_nbr)))
		raise_error(ERR_MALLOC);
	out_scene->lights[0] = (t_light){AMBIENT, 0.2, {}, {}};
	out_scene->lights[1] = (t_light){POINT, 0.5, {{4, 1, 2}}, {}};
	out_scene->lights[2] = (t_light){POINT, 0.5, {{6, 1, 6}}, {}};
//	out_scene->lights[2] = (t_light){DIRECTIONAL, 0.2f, {}, {{1, 4, 4}}};
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
	init_scene(&out_rtv1->scene);
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
