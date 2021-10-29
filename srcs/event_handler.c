#include <stdlib.h>
#include "utils.h"
#include "objects.h"

int	close_window(void *str)
{
	struct s_setup	*data;

	data = str;
	if (data->mlx != 0)
	{
		mlx_destroy_image(data->mlx, data->image);
		mlx_destroy_window(data->mlx, data->window);
	}
	free_all(data);
	exit(0);
}

void	camera_movement(int keycode, void *str)
{
	struct s_setup		*data;
	t_camera			*current_cam;
	t_vector3			movement;

	data = str;
	current_cam = (t_camera *)data->scene->current_camera->content;
	if (keycode == W_KEY)
		movement = init_v3(0, 0, 1);
	else if (keycode == A_KEY)
		movement = init_v3(-1, 0, 0);
	else if (keycode == S_KEY)
		movement = init_v3(0, 0, -1);
	else
		movement = init_v3(1, 0, 0);
	current_cam->pos = add_v3(current_cam->pos, movement);
	render(data, data->scene);
}

void	camera_rotation(int keycode, void *str)
{
	struct s_setup		*data;
	t_camera			*current_cam;
	t_vector3			orientation;

	data = str;
	current_cam = (t_camera *)data->scene->current_camera->content;
	if (keycode == UP_KEY)
		orientation = init_v3(0, 0.2, 0);
	else if (keycode == DOWN_KEY)
		orientation = init_v3(0, -0.2, 0);
	else if (keycode == LEFT_KEY)
		orientation = init_v3(-0.2, 0, 0);
	else
		orientation = init_v3(0.2, 0, 0);
	current_cam->orientation = add_v3(current_cam->orientation, orientation);
	current_cam->orientation = normalize_v3(current_cam->orientation);
	render(data, data->scene);
}

void	switch_cameras(void *str)
{
	struct s_setup	*data;

	data = str;
	if (data->scene->cameras_amount > 1)
	{
		if (data->scene->current_camera->next != 0)
			data->scene->current_camera = data->scene->current_camera->next;
		else
			data->scene->current_camera = data->scene->cameras;
		render(data, data->scene);
	}
}

int	key_press(int keycode, void *str)
{
	if (keycode == ESC_KEY)
		close_window(str);
	else if (keycode == W_KEY || keycode == A_KEY || keycode == S_KEY
		|| keycode == D_KEY)
		camera_movement(keycode, str);
	else if (keycode == UP_KEY || keycode == DOWN_KEY || keycode == LEFT_KEY
		|| keycode == RIGHT_KEY)
		camera_rotation(keycode, str);
	else if (keycode == SPACE_KEY)
		switch_cameras(str);
	return (1);
}
