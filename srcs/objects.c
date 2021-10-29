#include "objects.h"
#include <stdlib.h>

t_sphere	*sphere_constructor(double diam, t_vector3 center, t_vector3 color)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	sphere->diameter = diam;
	sphere->radius = diam * 0.5;
	sphere->center = center;
	sphere->surface_color = init_v3(color.x, color.y, color.z);
	return (sphere);
}

t_light	*light_constructor(t_vector3 pos, double intensity, t_vector3 color)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (0);
	light->pos = pos;
	light->intensity = intensity;
	light->color = color;
	return (light);
}

t_camera	*camera_constructor(t_vector3 pos, t_vector3 orientation, int fov )
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (!camera)
		return (0);
	camera->pos = pos;
	camera->orientation = normalize_v3(orientation);
	camera->fov = fov;
	camera->angle = tan(M_PI * 0.5 * (double)camera->fov / 180.);
	return (camera);
}

t_plane	*plane_constructor(t_vector3 origin, t_vector3 orient, t_vector3 color)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		return (0);
	plane->origin = origin;
	plane->normal = normalize_v3(orient);
	plane->surface_color = color;
	return (plane);
}

t_triangle	*triangle_constructor(t_vector3 v1, t_vector3 v2,
				t_vector3 v3, t_vector3 color)
{
	t_triangle	*triangle;

	triangle = (t_triangle *)malloc(sizeof(t_triangle));
	if (!triangle)
		return (0);
	triangle->vert1 = v1;
	triangle->vert2 = v2;
	triangle->vert3 = v3;
	triangle->color = color;
	triangle->edge_1 = subtract_v3(v2, v1);
	triangle->edge_2 = subtract_v3(v3, v1);
	triangle->normal = normalize_v3(cross_product(triangle->edge_1,
				triangle->edge_2));
	return (triangle);
}
