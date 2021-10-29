#include "minirt.h"
#include "matrix.h"
#include "utils.h"
#include "color_utils.h"
#include "animate.h"
#include "objects.h"

struct s_hit	intersect_all(struct s_scene *scene,
					t_ray *t_ray, double max_distance)
{
	struct s_hit	hit_point;
	int				i;
	t_list			*current_list;

	hit_point.hit_distance = INFINITY;
	i = 0;
	current_list = scene->objects;
	while (i < 5)
	{
		if (current_list->content != 0)
		{
			(*scene->fun_ptr_arr[i])(&hit_point, scene, t_ray);
			if (hit_point.hit_distance < max_distance && max_distance > 0)
				return (hit_point);
		}
		current_list = current_list->next;
		i++;
	}
	return (hit_point);
}

unsigned int	trace(struct s_scene *scene, t_ray *t_ray)
{
	int				pixel_color;
	struct s_hit	hit_point;

	hit_point = intersect_all(scene, t_ray, -1);
	if (hit_point.hit_distance == INFINITY)
	{
		pixel_color = create_trgb(0, 0, 0, 0);
		return (pixel_color);
	}
	pixel_color = shade(scene, &hit_point);
	return (pixel_color);
}

void	setup_t_ray(t_ray *t_ray, double x_world,
			double y_world, t_camera *camera)
{
	t_ray->origin = camera->pos;
	t_ray->direction = init_v3(x_world, y_world, 1);
	t_ray->direction = matrix_transform(camera->matrix, t_ray->direction);
	t_ray->direction = subtract_v3(t_ray->direction, camera->pos);
	t_ray->direction = normalize_v3(t_ray->direction);
}

/* convert pixel coordinates to world coordinates
cast a t_ray that goes in the direction of othe center of the pixel */
unsigned int	t_ray_through_pixel(t_camera *cam,
					struct s_setup *d, int x, int y)
{
	double		x_world;
	double		y_world;
	t_ray		t_ray;

	x_world = (2 * ((x + 0.5) * d->inv_width) - 1) * cam->angle
		* d->aspect_ratio;
	y_world = (1 - 2 * ((y + 0.5) * d->inv_height)) * cam->angle;
	setup_t_ray(&t_ray, x_world, y_world, cam);
	return (trace(d->scene, &t_ray));
}

void	render(struct s_setup *data, struct s_scene *scene)
{
	t_camera			*camera;
	t_coord				point;
	unsigned int		pixel_color;

	camera = (t_camera *)scene->current_camera->content;
	camera->matrix = camera_to_world_space(camera->pos, camera->orientation);
	point.x = 0;
	point.y = 0;
	while (point.y < data->height)
	{
		point.x = 0;
		while (point.x < data->width)
		{
			pixel_color = t_ray_through_pixel(camera, data, point.x, point.y);
			my_pixel_put(data, new_coord(data->width - point.x - 1, point.y),
				pixel_color, data->img_address);
			point.x++;
		}
		point.y++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	if (data->animate)
		animate(data);
}
