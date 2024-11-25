NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror -g
LFT_FLAGS = -lft
#READLINE_INC = -I/opt/homebrew/opt/readline/include
#READLINE_LIB = -L/opt/homebrew/opt/readline/lib -lreadline
RM = rm -fr
MAIN = minishell.c
SRC = Utils/*.c Parse/*.c Execution/*.c Commands/*.c
SRC_LFT = libft
OBJ = obj/*.o

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -L $(SRC_LFT) $(LFT_FLAGS) -lreadline -o $(NAME)
#	@$(CC) $(FLAGS) $(OBJ) -L $(SRC_LFT) $(LFT_FLAGS) $(READLINE_LIB) -o $(NAME)

$(OBJ): $(MAIN) $(SRC)
	@make -C $(SRC_LFT) -s
	@mkdir -p obj
	@$(CC) $(FLAGS) -c $(SRC) $(MAIN)
#	@$(CC) $(FLAGS) $(READLINE_INC) -c $(SRC) $(MAIN)
	@mv *.o obj/

clean:
	@$(RM) $(OBJ) $(BONUS_OBJ) obj obj_bonus
	@make clean -C $(SRC_LFT) -s

fclean:
	@$(RM) $(OBJ) $(BONUS_OBJ) $(NAME) $(BONUS_NAME) obj obj_bonus
	@make fclean -C $(SRC_LFT) -s
#	@$(RM) libft

re: fclean all
