#include "scene_parsing.h"

int			get_objects_by_name(
		const char *config,
		const char *objname,
		t_object *objects,
		int *out_obj_index)
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

int			get_lights_by_name(
		const char *config,
		t_light *lights,
		int *out_light_index)
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
