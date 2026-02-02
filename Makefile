NAME        = philo

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

SRCS        = srcs/philo.c srcs/atol.c


OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
