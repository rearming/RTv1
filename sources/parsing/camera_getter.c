#include "scene_parsing.h"

void		get_camera(const char *config, t_camera *out_camera)
{
	if (!(config = ft_strstr(config, "camera")))
		return ;
	out_camera->pos = get_vector(config, STR_POS);
	out_camera->rotation = get_vector(config, STR_ROTATION);
}
