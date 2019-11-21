#ifndef RTV1_STRUCTS_H
# define RTV1_STRUCTS_H

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*rend;
	SDL_Texture			*texture;
	int					pitch;
}						t_sdl;

typedef struct			s_opencl
{
	cl_context			context;
	cl_command_queue	queue;
	cl_platform_id		platform_id;
	cl_uint				ret_num_platforms;
	cl_uint				ret_num_devices;
	cl_device_id		device_id;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				scene;
	cl_mem				camera;
	cl_mem				img_data;
}						t_opencl;

typedef struct			s_quadratic_eq
{
	float				a;
	float				b;
	float				c;
	float				discriminant;
	float				x1;
	float				x2;
}						t_quadratic_eq;

typedef struct			s_vector
{
	float				x;
	float				y;
	float				z;
}						t_vector;

typedef struct			s_dpoint
{
	float				x;
	float				y;
	float				z;
}						t_dpoint;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	int					color;
}						t_point;

typedef struct			s_line
{
	t_point				start;
	t_point				end;
	t_point				point;
	t_point				delta;
	int					steep;
	int					error;
	int					ystep;
}						t_line;

typedef struct			s_camera
{
	int					viewport_width;
	int					viewport_height;
	float				viewport_distance;
	t_vector			pos;
}						t_camera;

/*
** Objects
*/

typedef struct			s_light
{
	int					type;
	float				intensity;
	t_vector			pos;
	t_vector			dir;
}						t_light;

typedef struct	s_plane 	t_plane;
typedef struct	s_cone		t_cone;
typedef struct	s_cylinder	t_cylinder;

typedef struct			s_sphere
{
	t_vector			center;
	float				raduis;
}						t_sphere;

typedef struct			s_object
{
	int					type;
	int					color;
	void				*obj;
}						t_object;

typedef struct			s_scene
{
	t_object			*objects;
	int					obj_nbr;
	t_light				*lights;
	int					lights_nbr;
}						t_scene;

typedef struct			s_rtv1
{
	t_sdl				sdl;
	t_opencl			cl;
	int					*img_data;
	t_camera			camera;
	t_scene				scene;
}						t_rtv1;

# define CL_BUFF_SIZE 10000

typedef struct			s_cl_gnl
{
	char				*temp_str;
	char				*backup;
	char				buf[CL_BUFF_SIZE + 1];
	int					read_res;
	size_t				sum_len;
}						t_cl_gnl;

#endif
