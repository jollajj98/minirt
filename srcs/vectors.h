#ifndef VECTORS_H
# define VECTORS_H

# include <math.h>

typedef struct vectors {
	double	x;
	double	y;
	double	z;

}				t_vector3;

t_vector3	init_v3(double x, double y, double z);
t_vector3	add_v3(t_vector3 a, t_vector3 b);
t_vector3	subtract_v3(t_vector3 a, t_vector3 b);
t_vector3	scale_v3(t_vector3 v, double f);
t_vector3	multiply_v3(t_vector3 a, t_vector3 b);
double		dot_v3(t_vector3 a, t_vector3 b);
double		length_v3(t_vector3 v);
t_vector3	normalize_v3(t_vector3 v);
t_vector3	negative_v3(t_vector3 v);
t_vector3	cross_product(t_vector3 a, t_vector3 b);
double		distance_v3(t_vector3 a, t_vector3 b);

#endif
