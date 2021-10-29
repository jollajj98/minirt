#include <math.h>
#include "vectors.h"
#include "utils.h"

double	distance_v3(t_vector3 a, t_vector3 b)
{
	double	dist;

	dist = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
	return (dist);
}

t_coord	new_coord(int x, int y)
{
	t_coord	new;

	new.x = x;
	new.y = y;
	return (new);
}
