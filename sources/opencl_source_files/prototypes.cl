float				compute_lighting(
		__constant t_scene *scene,
		__constant t_light *lights,
		__constant t_object *objects,
		float3 point,
		float3 normal,
		float3 ray_dir,
		float closest_intersect,
		int closest_obj_index);

int					in_shadow(
		__constant t_scene *scene,
		__constant t_object *objects,
		float3 point,
		float3 light_dir,
		float ray_max);

float				compute_glare(
		float3 normal_vec,
		float3 light_vec,
		float3 ray_dir,
		float light_intensity,
		int specularity);

int 			in_range_inclusive(float number, float min, float max);
float3			canvas_to_viewport(__constant t_camera *camera, float3 canvas_point);
t_point			get_videomem_coord_system_point(t_point raw_point);
void			image_put_pixel(__global int *img_data, t_point point);
int				change_color_intensity(t_color color, float intensity);

void			ray_sphere_intersect(
		float3 camera_pos,
		float3 ray_dir,
		__constant t_object *sphere,
		float *out_x1,
		float *out_x2);

float3			compute_normal(float3 point, __constant t_object *intersect_obj);

float			compute_glare(
		float3 normal_vec,
		float3 light_vec,
		float3 ray_dir,
		float light_intensity,
		int specularity);

void 			find_intersection(
		float3 origin,
		float3 ray_dir,
		__constant t_object *object,
		float *out_intersect1,
		float *out_intersect2);

float				closest_intersection(
		__constant t_scene *scene,
		__constant t_object *objects,
		float3 origin,
		float3 ray_dir,
		float ray_min,
		float ray_max,
		int *out_closest_obj_index,
		t_color *out_result_color
);

int				trace_ray(
		__constant t_scene *scene,
		__constant t_camera *camera,
		__constant t_object *objects,
		__constant t_light *lights,
		float3 ray_dir,
		float ray_min,
		float ray_max);