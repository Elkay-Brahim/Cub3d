NAME = cub3d

HEADER = parsing_map/parsing.h parsing_map/get_next_line/get_next_line.h cub3d.h

SRC = ft_init.c draw_line.c raycasting.c $(addprefix parsing_map/, parsing.c get_data_map.c \
								$(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)\
								$(addprefix utils/, ft_strlen.c ft_split.c ft_calloc.c ft_bzero.c ft_strchr.c ft_strdup.c \
									ft_substr.c ft_atoi.c ft_strjoin.c))


OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = 

$(NAME) : $(OBJ) $(HEADER) 
		$(CC) $(CFLAGS) $(SRC) -lmlx -framework OpenGL -framework AppKit  -fsanitize=address -g -o $(NAME) 

all : $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re