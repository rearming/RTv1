#include "rtv1.h"

void		print_vector(cl_float3 vec)
{
	ft_printf("x: [%.2f], y: [%.2f], z: [%.2f]\n", vec.x, vec.y, vec.z);
}

void		print_object(t_object object)
{
	if (object.type == SPHERE)
		ft_printf("\nsphere:\n");
	else if (object.type == PLANE)
		ft_printf("\nplane:\n");
	else if (object.type == CYLINDER)
		ft_printf("\ncylinder:\n");
	else if (object.type == CONE)
		ft_printf("\ncone:\n");
	ft_printf("radius: [%.2f]\n", object.radius);
	ft_printf("center:\n");
	print_vector(object.center);
	ft_printf("normal:\n");
	print_vector(object.normal);
	ft_printf("rotation:\n");
	print_vector(object.axis);
	ft_printf("len: [%.2f]\n", object.len);
	ft_printf("angle: [%.2f]\n", object.angle);
	ft_printf("material.color: [0x%X]\n", object.material.color.value);
	ft_printf("material.specular: [%i]\n", object.material.specularity);
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
