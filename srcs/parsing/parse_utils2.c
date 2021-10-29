int	is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_range(double start_range, double end_range, double value)
{
	if (value < start_range || value > end_range)
		return (-1);
	return (1);
}

int	ft_atoi(char *str, int *index)
{
	int	nb;

	nb = 0;
	while (is_numeric(str[*index]))
	{
		nb = nb * 10 + str[*index] - 48;
		(*index)++;
	}
	return (nb);
}

double	double_atoi(char *str, int *index)
{
	double	nb;
	int		multiplier;
	int		divisor;

	nb = 0;
	multiplier = 1;
	divisor = 10;
	if (str[*index] == '-')
	{
		multiplier = -1;
		(*index)++;
	}
	nb = (double)ft_atoi(str, index);
	if (str[*index] == '.')
		(*index)++;
	while (is_numeric(str[*index]))
	{
		nb = nb + (str[*index] - 48) / (double)divisor;
		divisor *= 10;
		(*index)++;
	}
	nb *= multiplier;
	return (nb);
}

/* this functions skips spaces and looks for the next number. 
//if it finds unexpected characters, it also returns -1
//otherwise, it returns 1
//it sets the value it found at the value pointer, and sets 
the index so that it skips chars in the streing to after the value
 is found */

int	parse_number(char *line, int *value, int *index)
{
	while (line[*index] == ' ' || line[*index] == '\t')
		(*index)++;
	if (!is_numeric(line[*index]))
		return (-1);
	*value = ft_atoi(line, index);
	return (1);
}
