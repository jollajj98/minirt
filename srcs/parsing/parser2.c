#include "parser.h"

int	parse_triangle(char *line, struct s_setup *s)
{
	int			i;
	int			ret;
	t_triangle	triangle;

	i = 2;
	ret = parse_vector(line, &(triangle.vert1), &i);
	if (ret == -1)
		return (-1);
	ret = parse_vector(line, &(triangle.vert2), &i);
	if (ret == -1)
		return (-1);
	ret = parse_vector(line, &(triangle.vert3), &i);
	if (ret == -1)
		return (-1);
	ret = parse_color(line, &(triangle.color), &i);
	if (ret == -1)
		return (-1);
	ret = triangle_setup(s, triangle);
	return (ret);
}

int	parse_ambient_light(char *line, struct s_setup *s)
{
	double	intensity;
	int		ret;
	int		i;
	int		valid_range;

	i = 1;
	if (s->scene->ambient_light.x != -1)
		return (-1);
	ret = parse_double(line, &intensity, &i, 1);
	valid_range = check_range(0., 1., intensity);
	if (ret == -1 || valid_range == -1)
		return (-1);
	ret = parse_color(line, &(s->scene->ambient_light), &i);
	if (ret == -1)
		return (-1);
	s->scene->ambient_light = scale_v3(s->scene->ambient_light, intensity);
	return (ret);
}

int	parse_lights(char *line, struct s_setup *setup)
{
	int		i;
	int		ret;
	int		valid_range;
	t_light	light;

	i = 1;
	ret = parse_vector(line, &(light.pos), &i);
	if (ret == -1)
		return (-1);
	ret = parse_double(line, &(light.intensity), &i, 1);
	valid_range = check_range(0., 1., light.intensity);
	if (ret == -1 || valid_range == -1)
		return (-1);
	ret = parse_color(line, &(light.color), &i);
	if (ret == -1)
		return (-1);
	ret = light_setup(setup, light);
	return (ret);
}

int	parse_plane(char *line, struct s_setup *setup)
{
	int		i;
	int		ret;
	t_plane	plane;

	i = 2;
	ret = parse_vector(line, &(plane.origin), &i);
	if (ret == -1)
		return (-1);
	ret = parse_vector(line, &(plane.normal), &i);
	if (ret == -1)
		return (-1);
	ret = validate_orientation_vec(plane.normal);
	if (ret == -1)
		return (-1);
	ret = parse_color(line, &(plane.surface_color), &i);
	if (ret == -1)
		return (-1);
	ret = setup_plane(setup, plane);
	return (ret);
}

int	parse_line_2(char *line, struct s_setup *setup, t_error *error)
{
	int	ret;

	ret = 1;
	if (line[0] == 'l')
	{
		ret = parse_lights(line, setup);
		error->message = "t_lights not set correctly";
	}
	else if (line[0] == 'A')
	{
		ret = parse_ambient_light(line, setup);
		error->message = "Ambient light not set correctly";
	}
	else if (line[0] == 'p' && line[1] == 'l')
	{
		ret = parse_plane(line, setup);
		error->message = "t_plane not set correctly";
	}
	else
		ret = parse_line_3(line, setup, error);
	return (ret);
}
