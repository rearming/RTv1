#ifndef CL_HEADER_H
# define CL_HEADER_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

typedef struct		s_sphere_cl
{
	cl_float3		center;
	float			radius;
}					t_sphere_cl;

typedef struct		s_object_cl
{
	int				type;
	int 			color;
	void			*obj;
}					t_object_cl;

typedef struct		s_light_cl
{
	int				type;
	float			intensity;
	cl_float3		pos;
	cl_float3 		dir;
}					t_light_cl;

typedef struct		s_scene_cl
{
	t_object_cl		*objects;
	int				obj_nbr;
	t_light_cl		*lights;
	int 			lights_nbr;
}					t_scene_cl;

typedef struct		s_camera_cl
{
	int				viewport_width;
	int				viewport_height;
	float			viewport_distance;
	cl_float3		pos;
}					t_camera_cl;

#endif
