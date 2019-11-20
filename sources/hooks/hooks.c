#include "rtv1.h"

int		key_press(int keycode, void *param)
{
	t_rtv1		*rtv1;

	rtv1 = (t_rtv1*)param;
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int		cross_close(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
}
