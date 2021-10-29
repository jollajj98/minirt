#ifndef OBJECTS_H
# define OBJECTS_H

# include "matrix.h"
# include "minirt.h"

typedef struct t_spheres{
	t_vector3	center;
	double		radius;
	double		diameter;
	t_vector3	surface_color;
	t_vector3	current_hit_point;
}				t_sphere;

typedef struct t_lights{
	t_vector3	pos;
	double		intensity;
	t_vector3	color;
}				t_light;

typedef struct t_cameras{
	t_vector3		pos;
	t_vector3		orientation;
	int				fov;
	t_matrix		matrix;
	double			angle;
}				t_camera;

typedef struct t_plane{
	t_vector3	origin;
	t_vector3	normal;
	t_vector3	surface_color;
}				t_plane;

typedef struct t_triangle{
	t_vector3	vert1;
	t_vector3	vert2;
	t_vector3	vert3;
	t_vector3	color;
	t_vector3	edge_1;
	t_vector3	edge_2;
	t_vector3	normal;
}				t_triangle;

typedef struct t_cylinder{
	t_vector3	center;
	t_vector3	orientation;
	double		radius;
	double		height;
	t_vector3	color;
	t_vector3	start_pos;
	t_vector3	end_pos;
	int			hit_disk;
	t_vector3	disk_norm;
	t_vector3	hit_cap_normal;
}				t_cylinder;

typedef struct t_quad{
	t_vector3	center;
	t_vector3	orientation;
	double		size;
	t_vector3	color;
	t_vector3	vert1;
	t_vector3	vert2;
	t_vector3	vert3;
	t_vector3	vert4;

}				t_quad;

t_cylinder		*cylinder_constructor(t_cylinder cyl);
t_triangle		*triangle_constructor(t_vector3 v1, t_vector3 v2,
					t_vector3 v3, t_vector3 color);
t_plane			*plane_constructor(t_vector3 origin, t_vector3 orientation,
					t_vector3 color);
t_sphere		*sphere_constructor(double diameter, t_vector3 center,
					t_vector3 color);
t_light			*light_constructor(t_vector3 pos, double intensity,
					t_vector3 color);
t_camera		*camera_constructor(t_vector3 pos, t_vector3 orientation,
					int fov );
t_quad			*quad_constructor(t_quad quad);
double			quadratic_solver(double a, double b, double c);
int				intersect_plane(t_plane *plane, t_ray *t_ray,
					double *intersect);
void			assign_hit_info(struct s_hit *hit, t_cylinder *cyl,
					double inters);
t_vector3		cylinder_normal(struct s_hit *hit, t_ray *t_ray,
					t_cylinder *cyl);
double			intersect_disc(t_ray *t_ray, t_plane disc_plane, double radius);
t_vector3		disc_normal(t_ray *ray, t_vector3 pl_normal, struct s_hit *hit);

#endif
