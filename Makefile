# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jdijkman <jdijkman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/07/30 14:24:14 by jdijkman      #+#    #+#                  #
#    Updated: 2024/08/26 13:59:27 by jdijkman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

SRC = 	main.c \
		state_change.c \
		utils.c \
		thread_utils.c \
		mutex_utils.c \
		mutex_utils2.c \
		execution.c \
		parsing.c \
		cleanup.c

OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

all:	$(NAME)

$(NAME): $(OBJS)
		cc $(CFLAGS) $(SRC) -o $(NAME) -pthread

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

# valgrind --tool=helgrind
.PHONY: all clean fclean re