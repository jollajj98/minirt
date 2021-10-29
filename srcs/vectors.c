#include <math.h>
#include "vectors.h"

t_vector3	init_v3(double x, double y, double z)
{
	t_vector3	v3;

	v3.x = x;
	v3.y = y;
	v3.z = z;
	return (v3);
}

t_vector3	add_v3(t_vector3 a, t_vector3 b)
{
	t_vector3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vector3	subtract_v3(t_vector3 a, t_vector3 b)
{
	t_vector3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vector3	scale_v3(t_vector3 v, double f)
{
	t_vector3	res;

	res.x = v.x * f;
	res.y = v.y * f;
	res.z = v.z * f;
	return (res);
}

t_vector3	multiply_v3(t_vector3 a, t_vector3 b)
{
	t_vector3	res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
	return (res);
}
