NAME = miniRT
SRCS = srcs/raytracer.c srcs/animate.c srcs/handle_quad.c \
srcs/handle_cylinder.c srcs/handle_cylinder_utils.c srcs/handle_triangles.c \
srcs/handle_planes.c srcs/color_utils.c srcs/vectors.c srcs/vectors2.c \
srcs/vectors3.c srcs/objects.c srcs/objects2.c srcs/utils.c \
srcs/lists/ft_list_utils.c srcs/matrix.c srcs/event_handler.c \
srcs/parsing/get_next_line.c srcs/parsing/parser.c srcs/parsing/setup.c \
srcs/parsing/setup2.c srcs/parsing/validate.c srcs/parsing/parse_utils.c \
srcs/parsing/parser2.c srcs/parsing/parser3.c \
srcs/parsing/get_next_line_utils.c srcs/parsing/parse_utils2.c \
srcs/handle_spheres.c srcs/main.c srcs/shade.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wextra -Werror -Wall
ASAN = -g -fsanitize=address
LIBMLX = ./mlx/libmlx.a
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(LIBMLX) :
	cd ./mlx; make

.c.o: $(SRCS)
	gcc -c $(FLAGS) $< -o $(<:.c=.o)

clean :
	cd ./mlx; make clean
	rm -f $(OBJS)

fclean : clean
		rm -f $(NAME)

re : clean all 

$(NAME): $(LIBMLX) $(OBJS)
	gcc $(OBJS) $(FLAGS) $(MLX_FLAGS) -o $(NAME)
