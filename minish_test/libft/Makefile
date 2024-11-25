NAME = libft.a
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -fr
SRC = ft*.c get_next_line.c
OBJ = obj/*.o

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ)

$(OBJ): $(SRC)
	@mkdir -p obj
	@$(CC) $(FLAGS) -c $(SRC)
	@mv *.o obj/

clean:
	@$(RM) $(OBJ) obj

fclean:
	@$(RM) $(OBJ) $(NAME) obj

re: fclean all
