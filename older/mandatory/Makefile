NAME= pipex
CC= cc
CFLAGS= -Wall -Werror -Wextra

SRCS=	./arg_checker.c\
		./command_handler.c\
		./utils.c\
		./pipex.c

LIBFT= ../sources
LIBFT_A= $(LIBFT)/libft.a

OBJS= $(SRCS:.c=.o)


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all:$(NAME)
$(NAME):$(OBJS)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT_A) -o $(NAME)


clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT)


fclean:clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT)


re: fclean all

.PHONY: all clean fclean re
