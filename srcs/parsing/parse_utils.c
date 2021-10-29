#include "parser.h"

int	parse_double(char *line, double *value, int *index, int skip_spaces)
{
	if (skip_spaces)
	{
		while (line[*index] == ' ' || line[*index] == '\t')
			(*index)++;
	}
	if (!is_numeric(line[*index]) && line[*index] != '-')
		return (-1);
	*value = double_atoi(line, index);
	return (1);
}

int	parse_vector(char *line, t_vector3 *value, int *index)
{
	int	ret;

	ret = parse_double(line, &(value->x), index, 1);
	if (ret == -1 || line[*index] != ',')
		return (-1);
	(*index)++;
	ret = parse_double(line, &(value->y), index, 0);
	if (ret == -1 || line[*index] != ',')
		return (-1);
	(*index)++;
	ret = parse_double(line, &(value->z), index, 0);
	if (ret == -1)
		return (-1);
	return (1);
}

int	parse_color(char *line, t_vector3 *value, int *index)
{
	int	ret;
	int	valid_range;
	int	current_value;

	ret = parse_number(line, &current_value, index);
	valid_range = check_range(0, 255, current_value);
	if (ret == -1 || line[*index] != ',' || valid_range == -1)
		return (-1);
	value->x = (double)current_value;
	(*index)++;
	ret = parse_number(line, &current_value, index);
	valid_range = check_range(0, 255, current_value);
	if (ret == -1 || line[*index] != ',' || valid_range == -1)
		return (-1);
	value->y = (double)current_value;
	(*index)++;
	ret = parse_number(line, &current_value, index);
	if (line[*index] != 0)
		return (-1);
	valid_range = check_range(0, 255, current_value);
	if (ret == -1 || valid_range == -1)
		return (-1);
	value->z = (double)current_value;
	return (1);
}
