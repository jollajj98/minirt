#include "objects.h"
#include <stdlib.h>
#include "matrix.h"

void	assign_vertices(t_quad *q)
{
	t_matrix		local_to_world;
	t_vector3		up_edge;
	t_vector3		right_edge;

	local_to_world = camera_to_world_space(init_v3(0, 0, 0), q->orientation);
	up_edge = init_v3(0, q->size / 2, 0);
	right_edge = init_v3(q->size / 2, 0, 0);
	up_edge = matrix_transform(local_to_world, up_edge);
	right_edge = matrix_transform(local_to_world, right_edge);
	up_edge = normalize_v3(up_edge);
	right_edge = normalize_v3(right_edge);
	q->vert1 = add_v3(q->center, scale_v3(up_edge, q->size / 2));
	q->vert1 = add_v3(q->vert1, scale_v3(right_edge, q->size / 2));
	q->vert2 = add_v3(q->center, scale_v3(up_edge, q->size / 2));
	q->vert2 = subtract_v3(q->vert2, scale_v3(right_edge, q->size / 2));
	q->vert3 = subtract_v3(q->center, scale_v3(up_edge, q->size / 2));
	q->vert3 = add_v3(q->vert3, scale_v3(right_edge, q->size / 2));
	q->vert4 = subtract_v3(q->center, scale_v3(up_edge, q->size / 2));
	q->vert4 = subtract_v3(q->vert4, scale_v3(right_edge, q->size / 2));
}

t_quad	*quad_constructor(t_quad quad)
{
	t_quad	*quad_alloc;

	quad_alloc = (t_quad *)malloc(sizeof(t_quad));
	if (!quad_alloc)
		return (0);
	quad_alloc->center = quad.center;
	quad_alloc->orientation = normalize_v3(quad.orientation);
	quad_alloc->size = quad.size;
	quad_alloc->color = quad.color;
	assign_vertices(quad_alloc);
	return (quad_alloc);
}

t_cylinder	*cylinder_constructor(t_cylinder cyl)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	cylinder->center = cyl.center;
	cylinder->orientation = normalize_v3(cyl.orientation);
	cylinder->radius = cyl.radius / 2;
	cylinder->height = cyl.height;
	cylinder->color = cyl.color;
	cylinder->start_pos = cyl.center;
	cylinder->end_pos = add_v3(cyl.center, scale_v3(cylinder->orientation,
				cyl.height));
	return (cylinder);
}
