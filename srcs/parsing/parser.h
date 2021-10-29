#ifndef PARSER_H
# define PARSER_H

# include "./../utils.h"
# include "./../objects.h"

int		is_numeric(char c);
int		get_next_line(int fd, char **line);
int		parse_number(char *line, int *value, int *index);
double	double_atoi(char *str, int *index);
void	parse_file(char *file_name, struct s_setup *setup);
int		parse_double(char *line, double *value, int *index, int skip_spaces);
int		parse_vector(char *line, t_vector3 *value, int *index);
int		check_range(double start_range, double end_range, double value);
int		validate_orientation_vec(t_vector3 v);
int		validate_camera(t_camera cam);
int		setup_camera(struct s_setup *setup, t_camera cam);
int		setup_plane(struct s_setup *setup, t_plane plane);
int		parse_color(char *line, t_vector3 *value, int *index);
int		setup_sphere(struct s_setup *setup, t_sphere sphere);
int		parse_line_2(char *line, struct s_setup *setup, t_error *error);
int		parse_line_3(char *line, struct s_setup *setup, t_error *error);
int		light_setup(struct s_setup *setup, t_light light);
int		triangle_setup(struct s_setup *setup, t_triangle triangle);
int		parse_triangle(char *line, struct s_setup *s);
int		quad_setup(struct s_setup *setup, t_quad quad);
int		cyl_setup(struct s_setup *setup, t_cylinder cyl);
void	validate_scene(struct s_setup *setup, t_error *error);
int		validate_config_file(char *file, struct s_setup *setup, t_error *error);

#endif
