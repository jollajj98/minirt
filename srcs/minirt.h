#ifndef MINIRT_H
# define MINIRT_H

# include "vectors.h"
# include "../mlx/mlx.h"
# include "./lists/ft_list.h"

# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define ESC_KEY 53
# define SPACE_KEY 49
# define UP_KEY 126
# define DOWN_KEY 125
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define TAB_KEY 48
# define EPSILON 0.0001

struct s_setup{
	void			*mlx;
	void			*window;
	void			*image;
	void			*animation_img;
	void			*animation_img_address;
	int				animate;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	char			*img_address;
	int				width;
	int				height;
	double			inv_width;
	double			inv_height;
	double			aspect_ratio;
	struct s_scene	*scene;
	float			time;
};

struct s_hit{
	t_vector3		albedo;
	t_vector3		pos;
	t_vector3		normal;
	double			hit_distance;
};

typedef struct t_rays{
	t_vector3	direction;
	t_vector3	origin;
}t_ray;

struct s_scene{
	t_list		*objects;
	t_list		*spheres;
	t_list		*planes;
	t_list		*triangles;
	t_list		*lights;
	t_list		*quads;
	t_list		*cylinders;
	t_vector3	ambient_light;
	t_list		*current_camera;
	t_list		*cameras;
	int			cameras_amount;
	void		(*fun_ptr_arr[5])(struct s_hit*,
				struct s_scene*, struct t_rays*);
};

void			handle_triangles(struct s_hit	*hit,
					struct s_scene *scene, t_ray *t_ray);
void			handle_spheres(struct s_hit *hit,
					struct s_scene *scene, t_ray *t_ray);
void			handle_planes(struct s_hit	*hit,
					struct s_scene *scene, t_ray *t_ray);
unsigned int	shade(struct s_scene *scene, struct s_hit *hit);
void			render(struct s_setup *data, struct s_scene *scene);
void			handle_quads(struct s_hit	*hit,
					struct s_scene *scene, t_ray *t_ray);
void			handle_cylinders(struct s_hit	*hit,
					struct s_scene *scene, t_ray *t_ray);
struct s_hit	intersect_all(struct s_scene *scene,
					t_ray *t_ray, double max_distance);

#endif
