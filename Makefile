NAME        = philo

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

SRCS        = srcs/philo.c srcs/ft_atol.c srcs/ft_utils.c


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
