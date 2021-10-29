#include "objects.h"

int	intersect_sphere(t_sphere *sp, t_ray *ray, double *inter_1, double *inter_2)
{
	t_vector3	t_ray_to_center;
	double		tca;
	double		d2;
	double		thc;

	t_ray_to_center = subtract_v3(sp->center, ray->origin);
	tca = dot_v3(t_ray_to_center, ray->direction);
	d2 = dot_v3(t_ray_to_center, t_ray_to_center) - tca * tca;
	if (d2 > (sp->radius * sp->radius))
		return (0);
	thc = sqrt(sp->radius * sp->radius - d2);
	*inter_1 = tca - thc;
	*inter_2 = tca + thc;
	if (*inter_2 < 0)
		return (0);
	return (1);
}

void	calculate_sphere_normal(t_ray *ray, struct s_hit *hit, t_sphere *sphere)
{
	t_vector3	hit_point;
	t_vector3	temp;
	t_vector3	normal;

	temp = scale_v3(ray->direction, hit->hit_distance);
	hit_point = add_v3(ray->origin, temp);
	hit->pos = hit_point;
	normal = subtract_v3(hit_point, sphere->center);
	normal = normalize_v3(normal);
	if (dot_v3(ray->direction, normal) > 0)
		normal = negative_v3(normal);
	hit->normal = normal;
	hit->albedo = sphere->surface_color;
}

void	handle_spheres(struct s_hit *hit, struct s_scene *scene, t_ray *t_ray)
{
	t_list		*current_sphere;
	t_sphere	*sphere;
	double		intersection_1;
	double		intersection_2;

	current_sphere = scene->spheres;
	sphere = (t_sphere *)(current_sphere->content);
	while (current_sphere != 0)
	{
		sphere = current_sphere->content;
		intersection_1 = INFINITY;
		intersection_2 = INFINITY;
		if (intersect_sphere(sphere, t_ray, &intersection_1, &intersection_2))
		{
			if (intersection_1 < 0)
				intersection_1 = intersection_2;
			if (intersection_1 < hit->hit_distance)
			{
				hit->hit_distance = intersection_1;
				calculate_sphere_normal(t_ray, hit, sphere);
			}
		}
		current_sphere = current_sphere->next;
	}
}
