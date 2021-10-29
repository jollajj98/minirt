#include "objects.h"

int	intersect_quad(t_quad *q, t_ray *ray, double *intersection)
{
	t_plane		plane;
	t_vector3	hit_point;
	double		x;
	double		y;

	plane.origin = q->center;
	plane.normal = q->orientation;
	if (!intersect_plane(&plane, ray, intersection))
		return (0);
	hit_point = add_v3(ray->origin, scale_v3(ray->direction, *intersection));
	x = dot_v3(subtract_v3(hit_point, q->vert1),
			subtract_v3(q->vert2, q->vert1));
	x = x / fabs((double)pow(distance_v3(q->vert2, q->vert1), 2));
	if (!(x >= 0 && x <= 1))
		return (0);
	y = dot_v3(subtract_v3(hit_point, q->vert1),
			subtract_v3(q->vert3, q->vert1));
	y = y / fabs((double)pow(distance_v3(q->vert3, q->vert1), 2));
	if (y >= 0 && y <= 1)
		return (1);
	return (0);
}

void	handle_quads(struct s_hit	*hit, struct s_scene *scene, t_ray *t_ray)
{
	t_list	*current_quad;
	t_quad	*quad;
	double	intersection;

	current_quad = scene->quads;
	quad = (t_quad *)(current_quad->content);
	while (current_quad != 0)
	{
		quad = current_quad->content;
		intersection = INFINITY;
		if (intersect_quad(quad, t_ray, &intersection))
		{
			if (intersection < hit->hit_distance)
			{
				hit->hit_distance = intersection;
				hit->albedo = quad->color;
				hit->pos = add_v3(t_ray->origin, scale_v3(t_ray->direction,
							hit->hit_distance));
				hit->normal = quad->orientation;
			}
		}
		current_quad = current_quad->next;
	}
}
