#ifndef COLOR_UTILS_H
# define COLOR_UTILS_H

int				create_trgb(int t, int r, int g, int b);
t_vector3		multiply_color(t_vector3 a, t_vector3 b);
t_vector3		add_color(t_vector3 a, t_vector3 b);
unsigned int	get_pixel_color(struct s_setup *img, int x, int y, void *addr);
#endif
