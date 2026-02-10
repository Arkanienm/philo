NAME        = philo

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

SRCS        = srcs/philo.c srcs/ft_atol.c srcs/ft_utils.c srcs/philo_manage.c \
			  srcs/philo_utils.c srcs/philo_monitor.c


OBJ_DIR     = obj/

OBJS        = $(SRCS:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: %.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
