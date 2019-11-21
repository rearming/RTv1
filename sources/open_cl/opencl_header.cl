typedef struct		s_sphere
{
	float3			center;
	float			radius;
}					t_sphere;

typedef struct		s_light
{
	int				type;
	float			intensity;
	float3			pos;
	float3	 		dir;
}					t_light;

typedef struct		s_object
{
	int				type;
	int 			color;
	void			*obj;
}					t_object;

typedef struct		s_scene
{
	t_object		*objects;
	int				obj_nbr;
	t_light			*lights;
	int 			lights_nbr;
}					t_scene;

typedef struct		s_camera
{
	int				viewport_width;
	int				viewport_height;
	float			viewport_distance;
	float3			pos;
}					t_camera;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

/*
**	Object types
*/

# define SPHERE 10
# define CONE 11
# define PLANE 12
# define CYLINDER 13

/*
** Light types
*/

# define AMBIENT 101
# define POINT 102
# define DIRECTIONAL 103

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

/*
**	Colors
*/

# define COL_NOT_SET (-1)
# define COL_RED 0xFF0000
# define COL_GREEN 0x00FF00
# define COL_BLUE 0x0000FF
# define COL_YELLOW 0xFFFF00
# define COL_WHITE 0xFFFFFF
# define COL_GREY 0x3A3635

# define COL_BG COL_GREY

