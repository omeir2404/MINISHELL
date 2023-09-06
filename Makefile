NAME = minishell
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address,undefined
CFLAGS_EXTRA = -g
INC = -I include/
EXT_LIBRARY = libft/libft.a

FILES = $(shell find ./src/ -type f -name "*.c")

OBJS = $(FILES:.c=.o)

all: $(NAME)
#@echo $(OBJS)
	valgrind --leak-check=full --show-leak-kinds=all --log-file=log.txt ./$(NAME)
#./$(NAME)

$(NAME): $(OBJS)
	@make -C libft/ --no-print
	@$(CC) $(CFLAGS) $(CFLAGS_EXTRA) $(INC) $(OBJS) $(EXT_LIBRARY) -lreadline  -lncurses -o $(NAME)

%.o: %.c
	@printf "\033[0;32mMinishell: \033[0;33mTaking care of the software...\033[0m\r"
	$(CC) $(CFLAGS) $(CFLAGS_EXTRA) $(INC) -c $< -o $@


clean:
	@make clean -C libft/ --no-print
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft/ --no-print

re: fclean all

valgrind: $(NAME)
	@valgrind --leak-check=full ./$(NAME)