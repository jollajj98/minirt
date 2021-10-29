#include "../utils.h"
#include "../objects.h"

int	triangle_setup(struct s_setup *setup, t_triangle triangle)
{
	t_triangle	*triangle_inst;
	t_list		*triangle_element;

	triangle_inst = triangle_constructor(triangle.vert1, triangle.vert2,
			triangle.vert3, triangle.color);
	triangle_element = ft_lstnew(triangle_inst);
	if (triangle_element == 0 || triangle_inst == 0)
		print_error(0, setup);
	if (setup->scene->triangles == 0)
		setup->scene->triangles = triangle_element;
	else
		ft_lstadd_back(&(setup->scene->triangles), triangle_element);
	return (1);
}

int	light_setup(struct s_setup *setup, t_light light)
{
	t_light	*light_inst;
	t_list	*light_element;

	light_inst = light_constructor(light.pos, light.intensity, light.color);
	light_element = ft_lstnew(light_inst);
	if (light_element == 0 || light_inst == 0)
		print_error(0, setup);
	if (setup->scene->lights == 0)
		setup->scene->lights = light_element;
	else
		ft_lstadd_back(&(setup->scene->lights), light_element);
	return (1);
}

int	setup_sphere(struct s_setup *setup, t_sphere sp)
{
	t_sphere	*sphere_inst;
	t_list		*sp_element;

	sphere_inst = sphere_constructor(sp.diameter, sp.center, sp.surface_color);
	sp_element = ft_lstnew(sphere_inst);
	if (sp_element == 0 || sphere_inst == 0)
		print_error(0, setup);
	if (setup->scene->spheres == 0)
		setup->scene->spheres = sp_element;
	else
		ft_lstadd_back(&(setup->scene->spheres), sp_element);
	return (1);
}

int	setup_camera(struct s_setup *setup, t_camera cam)
{
	t_camera	*cam_inst;
	t_list		*cam_element;

	cam_inst = camera_constructor(cam.pos, cam.orientation, cam.fov);
	cam_element = ft_lstnew(cam_inst);
	if (cam_element == 0 || cam_inst == 0)
		print_error(0, setup);
	if (setup->scene->current_camera == 0)
	{
		setup->scene->current_camera = cam_element;
		setup->scene->cameras = setup->scene->current_camera;
	}
	else
		ft_lstadd_back(&(setup->scene->current_camera), cam_element);
	setup->scene->cameras_amount ++;
	return (1);
}

int	setup_plane(struct s_setup *setup, t_plane pl)
{
	t_plane	*plane_inst;
	t_list	*plane_element;

	plane_inst = plane_constructor(pl.origin, pl.normal, pl.surface_color);
	plane_element = ft_lstnew(plane_inst);
	if (plane_inst == 0 || plane_element == 0)
		print_error(0, setup);
	if (setup->scene->planes == 0)
		setup->scene->planes = plane_element;
	else
		ft_lstadd_back(&(setup->scene->planes), plane_element);
	return (1);
}
