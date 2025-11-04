NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =	

OBJC=$(SRCS:.c=.o)

all:$(NAME)
$(NAME):$(OBJC)
	ar rcs $(NAME) $(OBJC)

clean:
	rm -rf $(OBJC)

fclean:clean
	rm -rf $(NAME)

re:fclean all

cc: 
	$(CC) $(CFLAGS) $(NAME)

norm:
	norminette $(SRCS)

run:all clean
	clear
	@$(CC) $(CFLAGS) main.c $(NAME)
	@./a.out

test: ## Run full test suite (regenerate expected outputs and run tests)
	@./tests/run_master.sh

.PHONY: all clean fclean re norm run cc 
