#include "minirt.h"
#include "utils.h"
#include "color_utils.h"
#include "objects.h"

t_vector3	calculate_light_color(t_light *light, struct s_hit *hit)
{
	t_vector3	light_dir;
	double		incident_light;

	light_dir = subtract_v3(hit->pos, light->pos);
	light_dir = normalize_v3(light_dir);
	incident_light = dot_v3(hit->normal, negative_v3(light_dir));
	clamp(incident_light, 0., INFINITY);
	incident_light = clamp(incident_light * light->intensity, 0., 1.);
	return (scale_v3(light->color, incident_light));
}

int	is_shadow(struct s_scene *scene, struct s_hit *hit, t_light *light)
{
	t_ray			shadow_t_ray;
	struct s_hit	shadow_hit;
	double			max_distance;

	shadow_t_ray.origin = add_v3(hit->pos, scale_v3(hit->normal, EPSILON));
	shadow_t_ray.direction = normalize_v3(subtract_v3(light->pos,
				shadow_t_ray.origin));
	max_distance = distance_v3(hit->pos, light->pos);
	shadow_hit = intersect_all(scene, &shadow_t_ray, max_distance);
	if (shadow_hit.hit_distance < max_distance)
		return (1);
	return (0);
}

unsigned int	shade(struct s_scene *scene, struct s_hit *hit)
{
	t_list				*current_light;
	t_light				*light;
	t_vector3			hit_color;
	t_vector3			light_color;
	unsigned int		pixel_color;

	current_light = scene->lights;
	hit_color = init_v3(0, 0, 0);
	while (current_light != 0)
	{	
		light = (t_light *)(current_light->content);
		if (!is_shadow(scene, hit, light))
		{
			light_color = calculate_light_color(light, hit);
			hit_color = add_color(light_color, hit_color);
		}
		current_light = current_light->next;
	}
	hit_color = add_color(hit_color, scene->ambient_light);
	hit_color = multiply_color(hit_color, hit->albedo);
	pixel_color = create_trgb(0, hit_color.x, hit_color.y, hit_color.z);
	return (pixel_color);
}
