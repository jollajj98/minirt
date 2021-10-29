#ifndef UTILS_H
# define UTILS_H
# include "minirt.h"

typedef struct t_errors {
	char	*message;
	int		line;
}				t_error;
typedef struct t_coords {
	int	x;
	int	y;
}				t_coord;

void	my_pixel_put(struct s_setup *img, t_coord pixel,
			unsigned int colour, void *img_address);
double	clamp(double x, double lower, double upper);
void	free_all(struct s_setup *setup);
void	print_error(t_error *error, struct s_setup *setup);
t_coord	new_coord(int x, int y);
#endif