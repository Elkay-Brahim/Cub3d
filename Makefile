NAME = cub3D
NAMEB = cub3Dbonus

HEADERM = $(addprefix mandatory/,parsing_map/parsing.h parsing_map/get_next_line/get_next_line.h cub3d.h)
HEADERB = $(addprefix bonus/,parsing_map/parsing.h parsing_map/get_next_line/get_next_line.h cub3d.h)

SRCB = $(addprefix bonus/, _dda.c _fold_of_view.c backgrand.c check_state_door.c break_of_x.c break_of_y.c calcul_destance_x.c calcul_destance_y.c mouse_hook.c color.c dda_draw.c \
		draw__line.c draw_line.c esc.c fold_of_view.c ft_free_all.c ft_init.c close_door.c ft_textur.c get_destance.c init_beta.c init_env_raycasting.c key_hook.c \
		left_right.c main.c mouvement.c player_represent.c randring.c ray_effect_x.c ray_effect_y.c raycasting.c up_down.c \
		$(addprefix parsing_map/, parsing.c get_data_map.c get_map_element.c get_map.c get_world.c final_map.c\
			$(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)\
			$(addprefix utils/, ft_strlen.c ft_split.c ft_calloc.c ft_bzero.c ft_strchr.c ft_strdup.c \
									ft_substr.c ft_atoi.c ft_strjoin.c)))

SRCM = $(addprefix mandatory/, _fold_of_view.c backgrand.c cross.c break_of_x.c break_of_y.c calcul_destance_x.c calcul_destance_y.c  color.c dda_draw.c \
		draw__line.c draw_line.c esc.c fold_of_view.c ft_free_all.c ft_init.c ft_textur.c get_destance.c init_beta.c init_env_raycasting.c key_hook.c \
		left_right.c main.c mouvement.c player_represent.c ray_effect_x.c ray_effect_y.c raycasting.c up_down.c \
		$(addprefix parsing_map/, parsing.c get_data_map.c get_map_element.c get_map.c get_world.c final_map.c\
			$(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)\
			$(addprefix utils/, ft_strlen.c ft_split.c ft_calloc.c ft_bzero.c ft_strchr.c ft_strdup.c \
									ft_substr.c ft_atoi.c ft_strjoin.c)))


OBJM = $(SRCM:.c=.o)
OBJB = $(SRCB:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

$(NAME) : $(OBJM) $(HEADERM) 
		$(CC) $(CFLAGS) $(SRCM) -lmlx -framework OpenGL -framework AppKit   -o cub3D
$(NAMEB) : $(OBJB) $(HEADERB) 
		$(CC) $(CFLAGS) $(SRCB) -lmlx -framework OpenGL -framework AppKit   -o cub3D

all : $(NAME)

bonus : $(NAMEB)

clean :
	rm -rf $(OBJM) $(OBJB)

fclean : clean
	rm -rf $(NAME) $(NAMEB)

re : fclean all

.PHONY: all clean fclean re bonus