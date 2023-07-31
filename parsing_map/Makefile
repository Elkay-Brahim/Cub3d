NAME = parsing

HEADER = parsing.h get_next_line/get_next_line.h

SRC = parsing.c get_data_map.c $(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)\
				$(addprefix utils/, ft_strlen.c ft_split.c ft_calloc.c ft_bzero.c ft_strchr.c ft_strdup.c \
				ft_substr.c ft_atoi.c ft_strjoin.c)


OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror 

$(NAME) : $(OBJ) $(HEADER) 
		$(CC) $(CFLAGS) $(SRC) -o $(NAME) 

all : $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re

