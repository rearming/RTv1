#include "rtv1.h"

void		correct_lights_intensity(t_scene *scene)
{
	int		i;

	i = 0;
	while (i < scene->lights_nbr)
	{
		scene->lights[i].intensity /= scene->lights_nbr;
		i++;
	}
}

void		init_scene(t_scene *out_scene)
{
	out_scene->obj_nbr = 5;
	if (!(out_scene->objects = malloc(sizeof(t_object) * (out_scene->obj_nbr))))
		raise_error(ERR_MALLOC);
	out_scene->objects[0] = new_sphere((cl_float3){{0, -1, 3}}, 1, COL_RED, 500);
	out_scene->objects[1] = new_sphere((cl_float3){{-2, 0, 4}}, 1, COL_BLUE, 10);
//	out_scene->objects[1] = new_sphere((cl_float3){{2, 0,  4}}, 1, COL_GREEN, 500);
//	out_scene->objects[3] = new_sphere((cl_float3){{0, -5001, 0}}, 5000, COL_YELLOW, 1000);
//	out_scene->objects[0] = new_cone((cl_float3){{0, 0, 0}}, 0.3f, (cl_float3){{0, 0, 90}}, M_PI_2 / 3, 10, 200, COL_YELLOW);
//	out_scene->objects[1] = new_cylinder((cl_float3){{0, 0, 0}},(cl_float3) {{0, 0, 0}}, 1, 10, COL_PURPLE, 200);
	out_scene->objects[2] = new_cylinder((cl_float3){{0, 0, 0}},(cl_float3) {{45, 0, 0}}, 1, 5, COL_GREEN, 200);
//	out_scene->objects[3] = new_cylinder((cl_float3){{0, 0, 0}},(cl_float3) {{0, 0, 90}}, 1, 5, COL_MAGNETA, 200);
	out_scene->objects[3] = new_plane((cl_float3){{0, -4, 0}}, (cl_float3){{0, 1, 0}}, COL_WHITE, 500);

	out_scene->lights_nbr = 3;
	if (!(out_scene->lights = malloc(sizeof(t_light) * out_scene->lights_nbr)))
		raise_error(ERR_MALLOC);
	out_scene->lights[0] = (t_light){AMBIENT, 0.6, {}, {}};
	out_scene->lights[1] = (t_light){POINT, 0.8, {{6, -2, 1}}, {}};
	out_scene->lights[2] = (t_light){POINT, 0.8, {{6, 1, 6}}, {}};
//	out_scene->lights[2] = (t_light){DIRECTIONAL, 0.2f, {}, {{1, 4, 4}}};
	correct_lights_intensity(out_scene);
}
