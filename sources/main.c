#include "rtv1.h"

int			count_all_objects(const char *config);

int			main(int argc, char **argv)
{
	t_rtv1		rtv1;

	if (argc != 2)
		raise_error(ERR_INV_ARGS_NUM);
	(void)argc;
	(void)argv;
	init_rtv1(&rtv1);
	init_objects(argv[1], &rtv1.scene);
//	init_scene(&rtv1.scene);
	cl_init(&rtv1);
	render(&rtv1, &render_gpu);
	sdl_loop(&rtv1);
	return (0);
}
