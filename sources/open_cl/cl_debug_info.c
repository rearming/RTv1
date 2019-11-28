#include "rtv1.h"

void		print_vector(cl_float3 vec)
{
	ft_printf("x: [%.2f], y: [%.2f], z: [%.2f]\n", vec.x, vec.y, vec.z);
}

static void		print_sphere(t_object *sphere)
{
	ft_printf("\n<--- SPHERE --->\n");
	ft_printf("center:\n");
	print_vector(sphere->center);
	ft_printf("radius: [%.2f]\n", sphere->radius);
}

static void		print_plane(t_object *plane)
{
	ft_printf("\n<--- PLANE --->\n");
	ft_printf("center:\n");
	print_vector(plane->center);
	ft_printf("normal:\n");
	print_vector(plane->normal);

}

static void		print_cylinder(t_object *cylinder)
{
	ft_printf("\n<--- CYLINDER --->\n");
	ft_printf("center:\n");
	print_vector(cylinder->center);
	ft_printf("rotation:\n");
	print_vector(cylinder->axis);
	ft_printf("len: [%.2f]\n", cylinder->len);
}

static void		print_cone(t_object *cone)
{
	ft_printf("\n<--- CONE --->\n");
	ft_printf("center:\n");
	print_vector(cone->center);
	ft_printf("rotation:\n");
	print_vector(cone->axis);
	ft_printf("len: [%.2f]\n", cone->len);
	ft_printf("angle: [%.2f]\n", cone->angle);
}

void		print_object(t_object *object)
{
	if (object->type == SPHERE)
		print_sphere(object);
	else if (object->type == PLANE)
		print_plane(object);
	else if (object->type == CYLINDER)
		print_cylinder(object);
	else if (object->type == CONE)
		print_cone(object);
	else
		ft_printf_fd(STDERR_FILENO, "CAN'T PRINT UNKNOWN OBJECT");
	ft_printf("material.color: [0x%X]\n", object->material.color.value);
	ft_printf("material.specular: [%i]\n", object->material.specularity);
}

void		print_debug_info(t_rtv1 *rtv1)
{
	ft_printf("\033[0;33m");
	ft_printf("camera position: ");
	print_vector(rtv1->camera.pos);
	ft_printf("camera rotation: ");
	print_vector(rtv1->camera.rotation);
	ft_printf("\033[0m");
	ft_putchar('\n');
}
