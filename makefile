# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakaddou <hakaddou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 19:53:46 by hakaddou          #+#    #+#              #
#    Updated: 2023/01/14 20:26:27 by hakaddou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= ft_usleep.c philo.c error_check.c struct_init.c philo_init.c \
					print.c src.c simulation.c 
					
OBJS			= $(SRCS:.c=.o)

CC				= gcc -pthread -g3
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= philo

all:			$(NAME)

$(NAME):		$(OBJS)
				 $(CC) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)
					rm *.o

exec:			re
				./$(NAME) && rm *.o

.PHONY:			all clean fclean re bonus

t1:
	@echo "philo will die after 800"
	@sleep 3
	./$(NAME) 1 800 200 200

# no die
t2:
	@echo "no philo should die"
	@sleep 3
	./$(NAME) 5 800 200 200

# no die. 'x is eating' should appear 7 times.
t3:
	@echo "no philo should die. should end after each philo eat 7 times"
	@sleep 3
	./$(NAME) 5 800 200 200 7

# no die.
t4:
	@echo "no philo should die"
	@sleep 3
	./$(NAME) 4 410 200 200

# die while waiting to eat. For instance 1 will die at 300 because 4 is still eating and will only release fork at 400.
t5:
	@echo "philo will die waiting to eat"
	@sleep 3
	./$(NAME) 4 310 200 100

# last but not least, test with small numbers. A philo should die.
t6:
	@echo "philo will die at 120"
	@sleep 3
	./$(NAME) 4 119 61 61
