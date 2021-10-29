#include "objects.h"

t_vector3	cylinder_normal(struct s_hit *hit, t_ray *ray, t_cylinder *cyl)
{
	t_vector3	ctp;
	t_vector3	normal;

	hit->pos = add_v3(ray->origin, scale_v3(ray->direction, hit->hit_distance));
	ctp = subtract_v3(hit->pos, cyl->center);
	normal = subtract_v3(ctp, scale_v3(cyl->orientation,
				dot_v3(cyl->orientation, ctp)));
	normal = normalize_v3(normal);
	if (dot_v3(ray->direction, normal) > 0)
		normal = negative_v3(normal);
	return (normal);
}

double	quadratic_solver(double a, double b, double c)
{
	double	intersection;
	double	intersection_2;
	double	res;

	res = sqrt(b * b - 4 * a * c);
	intersection = INFINITY;
	if (res > 0)
	{
		intersection = (-b + res) / (2 * a);
		intersection_2 = (-b - res) / (2 * a);
		if (intersection_2 < intersection && intersection_2 > 0)
			intersection = intersection_2;
	}
	else if (res == 0)
		intersection = -b / (2 * a);
	return (intersection);
}

double	intersect_disc(t_ray *t_ray, t_plane disc_plane, double radius)
{
	double		inters;
	t_vector3	hit_point;

	inters = INFINITY;
	if (intersect_plane(&disc_plane, t_ray, &inters))
	{
		hit_point = add_v3(t_ray->origin, scale_v3(t_ray->direction, inters));
		if (distance_v3(hit_point, disc_plane.origin) > radius)
			inters = INFINITY;
	}
	return (inters);
}

void	assign_hit_info(struct s_hit *hit, t_cylinder *cyl, double inters)
{
	hit->albedo = cyl->color;
	hit->hit_distance = inters;
}

t_vector3	disc_normal(t_ray *ray, t_vector3 plane_normal, struct s_hit *hit)
{
	hit->pos = add_v3(ray->origin, scale_v3(ray->direction, hit->hit_distance));
	if (dot_v3(ray->direction, plane_normal) > 0)
		return (negative_v3(plane_normal));
	return (plane_normal);
}
