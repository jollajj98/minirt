#include <stdlib.h>
#include "utils.h"
#include "parsing/parser.h"
#include "events.h"

int	initialise_scene(struct s_setup *setup)
{
	struct s_scene	*scene;

	scene = malloc(sizeof(struct s_scene));
	if (!scene)
		print_error(0, setup);
	setup->scene = scene;
	setup->width = -1;
	setup->mlx = 0;
	scene->current_camera = 0;
	scene->spheres = 0;
	scene->lights = 0;
	scene->ambient_light.x = -1;
	scene->planes = 0;
	scene->triangles = 0;
	scene->quads = 0;
	scene->cylinders = 0;
	scene->objects = 0;
	setup->animate = 0;
	scene->cameras = 0;
	scene->fun_ptr_arr[0] = &handle_spheres;
	scene->fun_ptr_arr[1] = &handle_planes;
	scene->fun_ptr_arr[2] = &handle_triangles;
	scene->fun_ptr_arr[3] = &handle_quads;
	scene->fun_ptr_arr[4] = &handle_cylinders;
	return (1);
}

void	initialise_image(struct s_setup *s)
{
	s->mlx = mlx_init();
	if (s->mlx == 0)
		print_error(0, s);
	s->window = mlx_new_window(s->mlx,
			s->width, s->height, "minirt");
	if (s->window == 0)
		print_error(0, s);
	s->image = mlx_new_image(s->mlx, s->width, s->height);
	if (s->image == 0)
		print_error(0, s);
	s->img_address = mlx_get_data_addr(s->image,
			&(s->bits_per_pixel), &(s->size_line), &(s->endian));
	if (s->img_address == 0)
		print_error(0, s);
}

void	initialise_data(struct s_setup *s)
{
	t_list	*spheres;
	t_list	*planes;
	t_list	*quads;
	t_list	*triangles;
	t_list	*cylinders;

	s->inv_width = 1. / (double)s->width;
	s->inv_height = 1. / (double)s->height;
	s->aspect_ratio = (double)s->width * s->inv_height;
	initialise_image(s);
	spheres = ft_lstnew(s->scene->spheres);
	planes = ft_lstnew(s->scene->planes);
	quads = ft_lstnew(s->scene->quads);
	triangles = ft_lstnew(s->scene->triangles);
	cylinders = ft_lstnew(s->scene->cylinders);
	s->scene->objects = spheres;
	ft_lstadd_back(&(s->scene->objects), planes);
	ft_lstadd_back(&(s->scene->objects), triangles);
	ft_lstadd_back(&(s->scene->objects), quads);
	ft_lstadd_back(&(s->scene->objects), cylinders);
}

int	main(int argc, char **argv)
{
	struct s_setup	data;

	(void)argc;
	initialise_scene(&data);
	parse_file(argv[1], &data);
	initialise_data(&data);
	render(&data, data.scene);
	mlx_hook(data.window, 17, 0, close_window, (void *)&data);
	mlx_hook(data.window, 2, 0, key_press, (void *)&data);
	mlx_loop(data.mlx);
}
