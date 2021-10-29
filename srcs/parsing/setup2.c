#include "../utils.h"
#include "../objects.h"

int	quad_setup(struct s_setup *setup, t_quad quad)
{
	t_quad	*quad_inst;
	t_list	*quad_element;

	quad_inst = quad_constructor(quad);
	quad_element = ft_lstnew(quad_inst);
	if (quad_element == 0 || quad_inst == 0)
		print_error(0, setup);
	if (setup->scene->quads == 0)
		setup->scene->quads = quad_element;
	else
		ft_lstadd_back(&(setup->scene->quads), quad_element);
	return (1);
}

int	cyl_setup(struct s_setup *setup, t_cylinder cyl)
{
	t_cylinder	*cyl_inst;
	t_list		*cyl_element;

	if (cyl.height < 0. || cyl.radius < 0.)
		return (-1);
	cyl_inst = cylinder_constructor(cyl);
	cyl_element = ft_lstnew(cyl_inst);
	if (cyl_element == 0 || cyl_inst == 0)
		print_error(0, setup);
	if (setup->scene->cylinders == 0)
		setup->scene->cylinders = cyl_element;
	else
		ft_lstadd_back(&(setup->scene->cylinders), cyl_element);
	return (1);
}
