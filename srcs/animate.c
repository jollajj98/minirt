#include <math.h>
#include "utils.h"
#include "color_utils.h"

unsigned int	get_distortion_color(t_coord pixel,
				struct s_setup *data, t_vector3 awt)
{
	t_vector3			normalized_coord;
	int					new_y;
	unsigned int		color;

	normalized_coord.x = (float)pixel.x * data->inv_width;
	normalized_coord.y = sin(awt.y * normalized_coord.x
			+ awt.z + data->time) * awt.x;
	new_y = round((pixel.y * (float)data->inv_height
				+ normalized_coord.y) * data->height);
	new_y = clamp(new_y, 0, data->height - 1);
	color = get_pixel_color(data, pixel.x, new_y, data->animation_img_address);
	return (color);
}

int	sine_wave(struct s_setup *data)
{
	t_coord		point;
	t_vector3	awt;

	awt.x = 0.15;
	awt.y = 10.0 * M_PI;
	awt.z = 30 * M_PI / 180;
	while (point.y < data->height)
	{
		while (point.x < data->width)
		{
			my_pixel_put(data, point, get_distortion_color(point, data, awt),
				data->img_address);
			point.x++;
		}
		point.x = 0;
		point.y++;
	}
	data->time += 0.1;
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	mlx_loop_hook(data->mlx, &sine_wave, (void *)data);
	return (0);
}

void	copy_image(struct s_setup *data)
{
	t_coord			point;
	unsigned int	col;

	point.x = 0;
	point.y = 0;
	while (point.y < data->height)
	{
		while (point.x < data->width)
		{
			col = get_pixel_color(data, point.x, point.y, data->img_address);
			my_pixel_put(data, point, col, data->animation_img_address);
			point.x++;
		}
		point.y++;
		point.x = 0;
	}
}

void	animate(struct s_setup *data)
{
	data->animation_img = mlx_new_image(data->mlx, data->width, data->height);
	data->animation_img_address = mlx_get_data_addr(data->animation_img,
			&(data->bits_per_pixel), &(data->size_line), &(data->endian));
	copy_image(data);
	data->time = 0;
	sine_wave(data);
}
