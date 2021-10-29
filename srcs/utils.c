#include <stdlib.h>
#include "utils.h"
#include "events.h"
#include <stdio.h>

void	my_pixel_put(struct s_setup *img, t_coord pixel,
			unsigned int colour, void *img_address)
{
	char	*dst;
	int		offset;

	offset = pixel.y * img->size_line + pixel.x * (img->bits_per_pixel / 8);
	dst = img_address + offset;
	*(unsigned int *)dst = colour;
}

double	clamp(double x, double lower, double upper)
{
	if (x < lower)
		return (lower);
	if (x > upper)
		return (upper);
	return (x);
}

void	free_object_list(struct s_setup *setup)
{
	int		i;
	t_list	*current_list;
	t_list	*next_list;

	i = 0;
	current_list = setup->scene->objects;
	while (i < 5)
	{
		next_list = current_list->next;
		free(current_list);
		i++;
		current_list = next_list;
	}
}

void	free_all(struct s_setup *setup)
{
	if (setup->scene->cameras)
		ft_lstclear(&(setup->scene->cameras), &free);
	if (setup->scene->spheres)
		ft_lstclear(&(setup->scene->spheres), &free);
	if (setup->scene->lights)
		ft_lstclear(&(setup->scene->lights), &free);
	if (setup->scene->planes)
		ft_lstclear(&(setup->scene->planes), &free);
	if (setup->scene->triangles)
		ft_lstclear(&(setup->scene->triangles), &free);
	if (setup->scene->quads)
		ft_lstclear(&(setup->scene->quads), &free);
	if (setup->scene->cylinders)
		ft_lstclear(&(setup->scene->cylinders), &free);
	if (setup->scene->objects)
		free_object_list(setup);
	if (setup->scene)
		free(setup->scene);
}

void	print_error(t_error *error, struct s_setup *setup)
{
	if (error == 0)
		printf("Error\nSomething went wrong!\n");
	else
		printf("Error\n%s at line %d\n", error->message, error->line);
	close_window((void *)setup);
}
