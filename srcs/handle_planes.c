#include "objects.h"

int	intersect_plane(t_plane *plane, t_ray *t_ray, double *intersect)
{
	double		denom;
	t_vector3	difference;
	double		t;

	denom = dot_v3(plane->normal, t_ray->direction);
	if (fabs(denom) > EPSILON)
	{
		difference = subtract_v3(plane->origin, t_ray->origin);
		t = dot_v3(difference, plane->normal) / denom;
		if (t > EPSILON)
		{
			*intersect = t;
			return (1);
		}
	}
	return (0);
}

void	handle_planes(struct s_hit	*hit, struct s_scene *scene, t_ray *t_ray)
{
	t_list	*current_plane;
	t_plane	*plane;
	double	intersection;

	current_plane = scene->planes;
	plane = (t_plane *)(current_plane->content);
	while (current_plane != 0)
	{
		plane = current_plane->content;
		intersection = INFINITY;
		if (intersect_plane(plane, t_ray, &intersection))
		{
			if (intersection < hit->hit_distance)
			{
				hit->hit_distance = intersection;
				hit->pos = add_v3(t_ray->origin, scale_v3(t_ray->direction,
							hit->hit_distance));
				hit->normal = plane->normal;
				hit->albedo = plane->surface_color;
			}
		}
		current_plane = current_plane->next;
	}
}
