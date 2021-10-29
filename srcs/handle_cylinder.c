#include "objects.h"

double	intersect_caps(t_ray *t_ray, t_cylinder *cyl)
{
	t_plane	cap_1;
	t_plane	cap_2;
	double	inter_1;
	double	inter_2;

	cap_1.origin = cyl->start_pos;
	cap_2.origin = cyl->end_pos;
	cap_1.normal = negative_v3(cyl->orientation);
	cap_2.normal = cyl->orientation;
	inter_1 = intersect_disc(t_ray, cap_1, cyl->radius);
	inter_2 = intersect_disc(t_ray, cap_2, cyl->radius);
	if (inter_2 < inter_1)
	{
		cyl->hit_cap_normal = cyl->orientation;
		return (inter_2);
	}
	else if (inter_1 < inter_2)
	{
		cyl->hit_cap_normal = negative_v3(cyl->orientation);
		return (inter_1);
	}
	return (INFINITY);
}

int	is_within_caps(t_cylinder *cyl, t_ray *t_ray, double a)
{
	t_vector3	hit_point;
	double		check;

	hit_point = add_v3(t_ray->origin, scale_v3(t_ray->direction, a));
	check = dot_v3(cyl->orientation, subtract_v3(hit_point, cyl->start_pos));
	if (check <= 0)
		return (0);
	check = dot_v3(cyl->orientation, subtract_v3(hit_point, cyl->end_pos));
	if (check >= 0)
		return (0);
	return (1);
}

double	intersect_infinite(t_cylinder *cyl, t_ray *t_ray)
{
	t_vector3	v1;
	t_vector3	v2;
	t_vector3	ray_to_cap;
	t_vector3	quadratic_vars;

	v1 = subtract_v3(t_ray->direction, scale_v3(cyl->orientation,
				dot_v3(t_ray->direction, cyl->orientation)));
	ray_to_cap = subtract_v3(t_ray->origin, cyl->start_pos);
	v2 = subtract_v3(ray_to_cap, scale_v3(cyl->orientation, dot_v3(ray_to_cap,
					cyl->orientation)));
	quadratic_vars.x = dot_v3(v1, v1);
	if (quadratic_vars.x == 0)
		return (INFINITY);
	quadratic_vars.y = 2 * dot_v3(v1, v2);
	quadratic_vars.z = dot_v3(v2, v2) - cyl->radius * cyl->radius;
	quadratic_vars.x = quadratic_solver(quadratic_vars.x, quadratic_vars.y,
			quadratic_vars.z);
	if (quadratic_vars.x <= 0)
		return (INFINITY);
	if (!is_within_caps(cyl, t_ray, quadratic_vars.x))
		return (INFINITY);
	return (quadratic_vars.x);
}

void	handle_cylinders(struct s_hit	*hit, struct s_scene *scene, t_ray *ray)
{
	t_list		*current_cyl;
	t_cylinder	*cyl;
	double		cyl_inters;
	double		cap_inters;

	current_cyl = scene->cylinders;
	cyl = (t_cylinder *)(current_cyl->content);
	while (current_cyl != 0)
	{
		cyl = current_cyl->content;
		cap_inters = intersect_caps(ray, cyl);
		cyl_inters = intersect_infinite(cyl, ray);
		if (cyl_inters < hit->hit_distance && cyl_inters < cap_inters)
		{
			assign_hit_info(hit, cyl, cyl_inters);
			hit->normal = cylinder_normal(hit, ray, cyl);
		}
		if (cap_inters < hit->hit_distance && cap_inters < cyl_inters)
		{
			assign_hit_info(hit, cyl, cap_inters);
			hit->normal = disc_normal(ray, cyl->hit_cap_normal, hit);
		}
		current_cyl = current_cyl->next;
	}
}
