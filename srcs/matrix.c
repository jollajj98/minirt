#include "matrix.h"

t_vector3	matrix_transform(t_matrix mat, t_vector3 v)
{
	t_vector3	res;

	res.x = v.x * mat.m[0][0] + v.y * mat.m[1][0]
		+ v.z * mat.m[2][0] + mat.m[3][0];
	res.y = v.x * mat.m[0][1] + v.y * mat.m[1][1]
		+ v.z * mat.m[2][1] + mat.m[3][1];
	res.z = v.x * mat.m[0][2] + v.y * mat.m[1][2]
		+ v.z * mat.m[2][2] + mat.m[3][2];
	return (res);
}

t_matrix	matrix_init(t_vector3 right, t_vector3 up,
	t_vector3 forward, t_vector3 transl)
{
	t_matrix	ret;

	ret.m[0][0] = right.x;
	ret.m[0][1] = right.y;
	ret.m[0][2] = right.z;
	ret.m[0][3] = 0;
	ret.m[1][0] = up.x;
	ret.m[1][1] = up.y;
	ret.m[1][2] = up.z;
	ret.m[1][3] = 0;
	ret.m[2][0] = forward.x;
	ret.m[2][1] = forward.y;
	ret.m[2][2] = forward.z;
	ret.m[2][3] = 0;
	ret.m[3][0] = transl.x;
	ret.m[3][1] = transl.y;
	ret.m[3][2] = transl.z;
	ret.m[3][3] = 1;
	return (ret);
}

/* function is protected from situations where arbitrary
	vector and forward vector coincide */
t_matrix	camera_to_world_space(t_vector3 origin, t_vector3 forward)
{
	t_vector3		up;
	t_vector3		right;
	t_vector3		arbitrary;
	t_matrix		ret;

	if (forward.x == 0 && (forward.y == 1 || forward.y == -1) && forward.z == 0)
	{
		right = init_v3(1, 0, 0);
		if (forward.y == 1)
			up = init_v3(0, 0, -1);
		else
			up = init_v3(0, 0, 1);
	}
	else
	{
		arbitrary = init_v3(0, 1, 0);
		right = cross_product(arbitrary, forward);
		right = normalize_v3(right);
		up = cross_product(forward, right);
		up = normalize_v3(up);
	}
	ret = matrix_init(right, up, forward, origin);
	return (ret);
}
