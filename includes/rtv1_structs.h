#ifndef RTV1_STRUCTS_H
# define RTV1_STRUCTS_H

typedef struct			s_quadratic_eq
{
	double				a;
	double				b;
	double				c;
	double				discriminant;
	double				x1;
	double				x2;
}						t_quadratic_eq;

typedef struct			s_vector
{
	double				x;
	double				y;
	double				z;
}						t_vector;

typedef struct			s_dpoint
{
	double				x;
	double				y;
	double				z;
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
	double				viewport_distance;
	t_vector			pos;
}						t_camera;

typedef struct			s_sphere
{
	t_vector			center;
	double				raduis;
	int					color;
}						t_sphere;

typedef struct			s_scene
{
	t_sphere			*spheres;
	int					objects;
}						t_scene;

typedef struct			s_rtv1
{
	void				*mlx_ptr;
	void				*win_ptr;
	void				*mlx_img;
	int					*img_data;
	t_camera			camera;
	t_scene				scene;
}						t_rtv1;

#endif
