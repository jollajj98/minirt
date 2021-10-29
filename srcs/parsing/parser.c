#include <unistd.h>
#include "parser.h"
#include <stdlib.h>

int	parse_sphere(char *line, struct s_setup *setup)
{
	int			i;
	int			ret;
	t_sphere	sphere;

	i = 2;
	ret = parse_vector(line, &(sphere.center), &i);
	if (ret == -1)
		return (-1);
	ret = parse_double(line, &(sphere.diameter), &i, 1);
	if (ret == -1)
		return (-1);
	if (sphere.diameter < 0.)
		return (-1);
	ret = parse_color(line, &(sphere.surface_color), &i);
	if (ret == -1)
		return (-1);
	ret = setup_sphere(setup, sphere);
	return (ret);
}

int	parse_cameras(char *line, struct s_setup *setup)
{
	int			i;
	t_camera	cam;
	int			ret;

	i = 1;
	ret = parse_vector(line, &(cam.pos), &i);
	if (ret == -1)
		return (-1);
	ret = parse_vector(line, &(cam.orientation), &i);
	if (ret == -1)
		return (-1);
	if (ret == -1)
		return (-1);
	ret = parse_number(line, &(cam.fov), &i);
	ret = validate_camera(cam);
	if (line[i] || ret == -1)
		return (-1);
	ret = setup_camera(setup, cam);
	return (ret);
}

int	parse_resolution(char *line, struct s_setup *setup)
{
	int	i;
	int	ret;

	i = 1;
	if (setup->width != -1)
		return (-1);
	ret = parse_number(line, &(setup->width), &i);
	if (ret == -1 || setup->width <= 0 || setup->width > 5120)
		return (-1);
	ret = parse_number(line, &(setup->height), &i);
	if (ret == -1 || setup->height <= 0 || setup->height > 2880)
		return (-1);
	if (line[i])
		return (-1);
	return (1);
}

int	parse_line(char *line, struct s_setup *setup, t_error *error)
{
	int		ret;

	if (line[0] == '\0' || line[0] == '#')
		return (0);
	else if (line[0] == 'R')
	{
		ret = parse_resolution(line, setup);
		error->message = "Resolution not set correctly";
	}
	else if (line[0] == 'c' && line[1] != 'y')
	{
		ret = parse_cameras(line, setup);
		error->message = "t_cameras not set correctly";
	}
	else if (line[0] == 's' && line[1] == 'p')
	{
		ret = parse_sphere(line, setup);
		error->message = "t_sphere not set correctly";
	}
	else
		ret = parse_line_2(line, setup, error);
	if (ret == -1)
		print_error(error, setup);
	return (1);
}

void	parse_file(char *file_name, struct s_setup *setup)
{
	char	*line;
	int		fd;
	int		ret;
	t_error	error;

	line = 0;
	error.line = 1;
	error.message = "Configuration file not found";
	ret = 1;
	fd = validate_config_file(file_name, setup, &error);
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			print_error(0, setup);
		parse_line(line, setup, &error);
		if (line)
			free(line);
		error.line++;
	}
	close(fd);
	validate_scene(setup, &error);
}
