NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread
INCLUDES = -I includes

SRCS = 	srcs/main.c \
		srcs/init.c \
		srcs/utils.c \
		srcs/routine.c \
		srcs/monitor.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
