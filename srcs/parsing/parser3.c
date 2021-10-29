#include "parser.h"

int	parse_quad(char *line, struct s_setup *setup)
{
	int		i;
	int		ret;
	t_quad	quad;

	i = 2;
	ret = parse_vector(line, &(quad.center), &i);
	if (ret == -1)
		return (-1);
	ret = parse_vector(line, &(quad.orientation), &i);
	if (ret == -1)
		return (-1);
	ret = validate_orientation_vec(quad.orientation);
	if (ret == -1)
		return (-1);
	ret = parse_double(line, &(quad.size), &i, 1);
	if (ret == -1)
		return (-1);
	if (quad.size < 0.)
		return (-1);
	ret = parse_color(line, &(quad.color), &i);
	if (ret == -1)
		return (-1);
	ret = quad_setup(setup, quad);
	return (ret);
}

int	parse_cyl(char *line, struct s_setup *setup)
{
	int			i;
	int			ret;
	t_cylinder	cyl;

	i = 2;
	ret = parse_vector(line, &(cyl.center), &i);
	if (ret == -1)
		return (-1);
	ret = parse_vector(line, &(cyl.orientation), &i);
	if (ret == -1)
		return (-1);
	ret = validate_orientation_vec(cyl.orientation);
	if (ret == -1)
		return (-1);
	ret = parse_double(line, &(cyl.radius), &i, 1);
	if (ret == -1)
		return (-1);
	ret = parse_double(line, &(cyl.height), &i, 1);
	if (ret == -1)
		return (-1);
	ret = parse_color(line, &(cyl.color), &i);
	if (ret == -1)
		return (-1);
	ret = cyl_setup(setup, cyl);
	return (ret);
}

int	parse_line_4(char *line, struct s_setup *setup, t_error *error)
{
	int	ret;

	ret = 1;
	if (line[0] == 'a' && line[1] == 'n' && line[2] == 'i'
		&& line[3] == '\0')
		setup->animate = 1;
	else
	{
		error->message = "Invalid identifier at beginning of line";
		return (-1);
	}
	return (ret);
}

int	parse_line_3(char *line, struct s_setup *setup, t_error *error)
{
	int	ret;

	ret = 1;
	if (line[0] == 't' && line[1] == 'r')
	{
		ret = parse_triangle(line, setup);
		error->message = "t_triangle not set correctly";
	}
	else if (line[0] == 's' && line[1] == 'q')
	{
		ret = parse_quad(line, setup);
		error->message = "t_quad not set correctly";
	}
	else if (line[0] == 'c' && line[1] == 'y')
	{
		ret = parse_cyl(line, setup);
		error->message = "Cylinder not set correctly";
	}
	else
		ret = parse_line_4(line, setup, error);
	return (ret);
}
