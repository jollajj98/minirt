#include <math.h>
#include "vectors.h"

double	dot_v3(t_vector3 a, t_vector3 b)
{
	double	res;

	res = a.x * b.x + a.y * b.y + a.z * b.z;
	return (res);
}

double	length_v3(t_vector3 v)
{
	double	res;

	res = v.x * v.x + v.y * v.y + v.z * v.z;
	return (sqrt(res));
}

t_vector3	normalize_v3(t_vector3 v)
{
	t_vector3	res;
	double		length;
	double		inv_len;

	res = v;
	length = length_v3(v);
	if (length > 0)
	{
		inv_len = 1 / length;
		res.x = v.x * inv_len;
		res.y = v.y * inv_len;
		res.z = v.z * inv_len;
	}
	return (res);
}

t_vector3	negative_v3(t_vector3 v)
{
	t_vector3	res;

	res.x = v.x * -1;
	res.y = v.y * -1;
	res.z = v.z * -1;
	return (res);
}

t_vector3	cross_product(t_vector3 a, t_vector3 b)
{
	t_vector3	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}
