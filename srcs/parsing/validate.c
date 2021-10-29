#include "parser.h"
#include <fcntl.h>

int	validate_orientation_vec(t_vector3 v)
{
	int	ret;

	ret = 1;
	ret = (check_range(-1, 1, v.x));
	ret = (check_range(-1, 1, v.y));
	ret = (check_range(-1, 1, v.z));
	if (length_v3(v) == 0.)
		return (-1);
	return (ret);
}

int	validate_camera(t_camera cam)
{
	int	ret;

	ret = 1;
	ret = validate_orientation_vec(cam.orientation);
	if (ret == -1)
		return (ret);
	ret = (check_range(0., 180., (double)cam.fov));
	return (ret);
}

void	validate_scene(struct s_setup *setup, t_error *error )
{
	if (setup->width == -1)
	{
		error->line = 0;
		error->message = "No resolution has been set";
		print_error(error, setup);
	}
	if (setup->scene->cameras == 0)
	{
		error->line = 0;
		error->message = "No cameras have been set";
		print_error(error, setup);
	}
}

int	validate_config_file(char *file, struct s_setup *setup, t_error *error)
{
	int	fd;
	int	i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error(error, setup);
	i = 0;
	while (file[i])
		i++;
	if (file[i - 1] != 't' || file[i - 2] != 'r' || file[i - 3] != '.')
	{
		error->message = "Not a .rt file";
		print_error(error, setup);
	}
	return (fd);
}
