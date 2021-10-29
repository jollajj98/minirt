#include "objects.h"

int	intersect_triangle(t_triangle *tr, t_ray *ray, double *inters)
{
	t_vector3	cross_t_raydir_edge2;
	t_vector3	t_rayorig_to_vert1;
	t_vector3	cross_t_raytovert_edge1;
	t_vector3	bary;
	double		inv_determinant;

	cross_t_raydir_edge2 = cross_product(ray->direction, tr->edge_2);
	inv_determinant = dot_v3(tr->edge_1, cross_t_raydir_edge2);
	if (fabs(inv_determinant) < EPSILON)
		return (0);
	inv_determinant = 1.0 / inv_determinant;
	t_rayorig_to_vert1 = subtract_v3(ray->origin, tr->vert1);
	bary.x = dot_v3(t_rayorig_to_vert1, cross_t_raydir_edge2) * inv_determinant;
	if (bary.x < 0.0 || bary.x > 1.0)
		return (0);
	cross_t_raytovert_edge1 = cross_product(t_rayorig_to_vert1, tr->edge_1);
	bary.y = dot_v3(ray->direction, cross_t_raytovert_edge1) * inv_determinant;
	if (bary.y < 0.0 || bary.x + bary.y > 1.0)
		return (0);
	*inters = dot_v3(tr->edge_2, cross_t_raytovert_edge1) * inv_determinant;
	if (*inters < 0)
		return (0);
	return (1);
}

void	handle_triangles(struct s_hit	*hit, struct s_scene *scene, t_ray *ray)
{
	t_list		*current_triangle;
	t_triangle	*triangle;
	double		intersection;

	current_triangle = scene->triangles;
	triangle = (t_triangle *)(current_triangle->content);
	while (current_triangle != 0)
	{
		triangle = current_triangle->content;
		intersection = INFINITY;
		if (intersect_triangle(triangle, ray, &intersection))
		{
			if (intersection < hit->hit_distance)
			{
				hit->hit_distance = intersection;
				hit->pos = add_v3(ray->origin, scale_v3(ray->direction,
							hit->hit_distance));
				hit->normal = triangle->normal;
				hit->albedo = triangle->color;
			}
		}
		current_triangle = current_triangle->next;
	}
}
