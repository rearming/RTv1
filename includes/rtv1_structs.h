#ifndef RTV1_STRUCTS_H
# define RTV1_STRUCTS_H

typedef struct			s_rgb
{
#ifndef FT_OPENCL___
	cl_uchar			r;
	cl_uchar			g;
	cl_uchar			b;
	cl_uchar			a;
#else
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	unsigned char		a;
#endif
}						t_rgb;

typedef union 			u_color
{
#ifndef FT_OPENCL___
	cl_int			value;
#else
	int				value;
#endif
	t_rgb			rgb;
}						t_color;

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
	t_color				color;
}						t_point;

# ifndef FT_OPENCL___
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
	cl_mem				objects;
	cl_mem				lights;
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
# endif

typedef struct			s_camera
{
	int					viewport_width;
	int					viewport_height;
	float				viewport_distance;
#  ifndef FT_OPENCL___
	cl_float3			pos;
#  else
	float3				pos;
#  endif
}						t_camera;

/*
** Objects
*/

typedef enum		e_object_type
{
	SPHERE = 1,
	PLANE,
	CYLINDER,
	CONE,
}					t_object_type;

typedef enum		e_light_type
{
	AMBIENT = 1,
	POINT,
	DIRECTIONAL,
}					t_light_type;

typedef struct			s_light
{
#  ifndef FT_OPENCL___
	t_light_type		type;
	cl_float			intensity;
	cl_float3			pos;
	cl_float3			dir;
#  else
	t_light_type		type;
	float				intensity;
	float3				pos;
	float3				dir;
#  endif
}						t_light;

typedef struct			s_material
{
	t_color				color;
}						t_material;

typedef struct			s_object
{
#  ifndef FT_OPENCL___
	t_object_type		type;
	cl_float			radius;
	t_material			material;
	cl_float3			center;
#  else
	t_object_type		type;
	float				radius;
	t_material			material;
	float3				center;
#  endif
}						t_object;

typedef struct			s_scene
{
#ifndef FT_OPENCL___
	cl_int				obj_nbr;
	cl_int				lights_nbr;
	t_object			*objects;
	t_light				*lights;
#else
	int					obj_nbr;
	int					lights_nbr;
	t_object			*objects;
	t_light				*lights;
#endif
}						t_scene;

# ifndef FT_OPENCL___
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
# endif

#endif
