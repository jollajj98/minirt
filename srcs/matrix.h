#ifndef MATRIX_H
# define MATRIX_H
# include "vectors.h"

typedef struct s_matrix
{
	double	m[4][4];
}				t_matrix;

t_matrix		camera_to_world_space(t_vector3 from, t_vector3 to);
t_vector3		matrix_transform(t_matrix matrix, t_vector3 v);

#endif
