#include "rtv1.h"

cl_float3	get_vector(const char *config, const char *field_name)
{
	cl_float3	result;

	if (!(config = ft_strstr(config, field_name)))
		raise_error(ERR_INV_SCENE_SYNTAX);
	config += ft_strlen(field_name);
	result.x = (float)ft_strtod(config);
	while (*config && *config != ',')
		++config;
	if (*config != ',')
		raise_error(ERR_INV_SCENE_SYNTAX);
	result.y = (float)ft_strtod(++config);
	while (*config && *config != ',')
		config++;
	if (*config != ',')
		raise_error(ERR_INV_SCENE_SYNTAX);
	result.z = (float)ft_strtod(++config);
	while (*config && *config != ')')
		config++;
	if (*config != ')')
		raise_error(ERR_INV_SCENE_SYNTAX);
	return (result);
}

cl_float	get_float_number(const char *config, const char *field_name)
{
	cl_float	result;

	if (!(config = ft_strstr(config, field_name)))
		raise_error(ERR_INV_SCENE_SYNTAX);
	config += ft_strlen(field_name);
	result = (float)ft_strtod(config);
	while (*config && *config != ')')
		config++;
	if (*config != ')')
		raise_error(ERR_INV_SCENE_SYNTAX);
	return (result);
}

cl_int		get_int_number(const char *config, const char *field_name, int base)
{
	cl_int	result;

	if (!(config = ft_strstr(config, field_name)))
		raise_error(ERR_INV_SCENE_SYNTAX);
	config += ft_strlen(field_name);
	result = (float)ft_atoll_base(config, base);
	while (*config && *config != ')')
		config++;
	if (*config != ')')
		raise_error(ERR_INV_SCENE_SYNTAX);
	return (result);
}

char		*get_string(const char *config, const char *field_name)
{
	char			*str_type;

	if (!(config = ft_strstr(config, field_name)))
		raise_error(ERR_INV_SCENE_SYNTAX);
	config += ft_strlen(field_name);
	str_type = ft_strsub(config, 0, ft_strlen_char(config, ')'));
	return (str_type);
}

t_light_type	get_light_type(char *str_light_type)
{
	t_light_type	type;

	type = NOT_SET;
	if (ft_strequ(str_light_type, STR_POINT_LIGHT))
		type = POINT;
	else if (ft_strequ(str_light_type, STR_DIRECTIONAL_LIGHT))
		type = DIRECTIONAL;
	else if (ft_strequ(str_light_type, STR_AMBIET_LIGHT))
		type = AMBIENT;
	else
		raise_error(ERR_INV_SCENE_SYNTAX);
	free(str_light_type);
	return (type);
}

t_object	get_sphere(const char *config)
{
	t_object	sphere;

	sphere.type = SPHERE;
	sphere.center = get_vector(config, "center(");
	sphere.radius = get_float_number(config, "radius(");
	sphere.material.color.value = get_int_number(config, "color(", 16);
	sphere.material.specularity = get_int_number(config, "specular(", 10);
	ft_printf("specular: [%i]\n", sphere.material.specularity);
	return (sphere);
}

t_object	get_plane(const char *config)
{
	t_object	plane;

	plane.type = PLANE;
	plane.center = get_vector(config, "pos(");
	plane.normal = get_vector(config, "normal(");
	plane.material.color.value = get_int_number(config, "color(", 16);
	plane.material.specularity = get_int_number(config, "specular(", 10);
	return (plane);
}

t_object	get_cylinder(const char *config)
{
	t_object	cylinder;

	cylinder.type = CYLINDER;
	cylinder.center = get_vector(config, "pos(");
	cylinder.axis = get_vector(config, "rotation(");
	cylinder.radius = get_float_number(config, "radius(");
	cylinder.len = get_float_number(config, "length(");
	cylinder.material.color.value = get_int_number(config, "color(", 16);
	cylinder.material.specularity = get_int_number(config, "specular(", 10);
	return (cylinder);
}

t_object	get_cone(const char *config)
{
	t_object	cone;

	cone.type = CONE;
	cone.center = get_vector(config, "pos(");
	cone.axis = get_vector(config, "rotation(");
	cone.angle = get_float_number(config, "angle(");
	cone.len = get_float_number(config, "length(");
	cone.material.color.value = get_int_number(config, "color(", 16);
	cone.material.specularity = get_int_number(config, "specular(", 10);
	return (cone);
}

t_object	get_object(const char *config, const char *objname)
{
	t_object	object;

	if (objname == STR_SPHERE)
		object = get_sphere(config);
	else if (objname == STR_PLANE)
		object = get_plane(config);
	else if (objname == STR_CYLINDER)
		object = get_cylinder(config);
	else if (objname == STR_CONE)
		object = get_cone(config);
	else
	{
		ft_printf_fd(STDERR_FILENO, "object: [%s]\n", objname);
		raise_error(ERR_UNKNOWN_OBJ);
		return ((t_object){});
	}
	print_object(object);
	return (object);
}

t_light		get_light(const char *config)
{
	t_light		light;

	light.type = get_light_type(get_string(config, "type("));
	light.intensity = get_float_number(config, "intensity(");
	light.pos = (cl_float3){};
	light.dir = (cl_float3){};
	if (light.type == POINT)
		light.pos = get_vector(config, "pos(");
	if (light.type == DIRECTIONAL)
		light.dir = get_vector(config, "dir(");
	return (light);
}

int 		get_objects_by_name(
		const char *config,
		const char *objname,
		t_object *objects,
		int	*out_obj_index
		)
{
	int				obj_count;
	int				count_last_iter;
	const size_t	objname_size = ft_strlen(objname);
	char			*ptr_i;

	obj_count = 0;
	while (21)
	{
		count_last_iter = obj_count;
		if ((ptr_i = ft_strstr(config, objname)))
		{
			config = ptr_i + objname_size;
			if (objects)
			{
				objects[*out_obj_index] = get_object(config, objname);
				(*out_obj_index)++;
			}
			obj_count++;
		}
		if (obj_count == count_last_iter)
			break ;

	}
	return (obj_count);
}

int 		get_lights_by_name(
		const char *config,
		t_light *lights,
		int	*out_light_index
)
{
	int				light_count;
	int				count_last_iter;
	const size_t	objname_size = sizeof(STR_LIGHT);
	char			*ptr_i;

	light_count = 0;
	while (21)
	{
		count_last_iter = light_count;
		if ((ptr_i = ft_strstr(config, STR_LIGHT)))
		{
			config = ptr_i + objname_size;
			if (lights)
			{
				lights[*out_light_index] = get_light(config);
				(*out_light_index)++;
			}
			light_count++;
		}
		if (light_count == count_last_iter)
			break ;

	}
	return (light_count);
}

int				count_all_objects(const char *config)
{
	int				obj_count;

	obj_count = 0;
	obj_count += get_objects_by_name(config, STR_CONE, NULL, NULL);
	obj_count += get_objects_by_name(config, STR_PLANE, NULL, NULL);
	obj_count += get_objects_by_name(config, STR_CYLINDER, NULL, NULL);
	obj_count += get_objects_by_name(config, STR_SPHERE, NULL, NULL);
	return (obj_count);
}

void	init_objects(const char *filename, t_scene *out_scene)
{
	const char	*config = ft_readfile(open(filename, O_RDONLY), NULL);
	const int	obj_nbr = count_all_objects(config);
	const int	lights_nbr = get_lights_by_name(config, NULL, NULL);
	int			obj_index;
	int			light_index;

	out_scene->obj_nbr = obj_nbr;
	if (!(out_scene->objects = malloc(sizeof(t_object) * obj_nbr)))
		raise_error(ERR_MALLOC);
	obj_index = 0;
	get_objects_by_name(config, STR_CONE, out_scene->objects, &obj_index);
	get_objects_by_name(config, STR_PLANE, out_scene->objects, &obj_index);
	get_objects_by_name(config, STR_CYLINDER, out_scene->objects, &obj_index);
	get_objects_by_name(config, STR_SPHERE, out_scene->objects, &obj_index);
	out_scene->lights_nbr = lights_nbr;
	if (!(out_scene->lights = malloc(sizeof(t_light) * lights_nbr)))
		raise_error(ERR_MALLOC);
	light_index = 0;
	get_lights_by_name(config, out_scene->lights, &light_index);
	correct_lights_intensity(out_scene);
	correct_objects(out_scene);
}
