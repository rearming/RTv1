#include "rtv1.h"

int			main(int argc, char **argv)
{
	t_rtv1		rtv1;

	(void)argc;
	(void)argv;
	init_rtv1(&rtv1);
	cl_init(&rtv1);
	render(&rtv1, &cl_render);
	sdl_loop(&rtv1);
	return (0);
}
