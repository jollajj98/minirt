#include "minirt.h"
#include "utils.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_vector3	multiply_color(t_vector3 a, t_vector3 b)
{
	t_vector3	res;

	res.x = a.x * b.x / 255;
	res.y = a.y * b.y / 255;
	res.z = a.z * b.z / 255;
	return (res);
}

unsigned int	get_pixel_color(struct s_setup *img, int x, int y, void *addr)
{
	char	*dst;
	int		offset;

	offset = y * img->size_line + x * (img->bits_per_pixel / 8);
	dst = addr + offset;
	return (*(unsigned int *)dst);
}

t_vector3	add_color(t_vector3 a, t_vector3 b)
{
	t_vector3	res;

	res.x = clamp((a.x + b.x), 0, 255);
	res.y = clamp((a.y + b.y), 0, 255);
	res.z = clamp((a.z + b.z), 0, 255);
	return (res);
}
