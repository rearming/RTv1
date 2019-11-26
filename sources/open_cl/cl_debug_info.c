#include "rtv1.h"

void		print_vector(cl_float3 vec)
{
	ft_printf("x: [%.2f], y: [%.2f], z: [%.2f]\n", vec.x, vec.y, vec.z);
}

void		print_debug_info(t_rtv1 *rtv1)
{
	write(1, "\033[0;33m", 7);
	ft_printf("camera position: ");
	print_vector(rtv1->camera.pos);
	ft_printf("camera rotation: ");
	print_vector(rtv1->camera.rotation);
	write(1, "\033[0m", 4);
	ft_putchar('\n');
}
