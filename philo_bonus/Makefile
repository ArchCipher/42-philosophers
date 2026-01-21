#				Library and Project names
NAME			= philo_bonus

#				Includes
HEADER			= philo.h
INC				= -I.

#				Sources & Objects
MSRCS			= \
				philo parser init \
				threads routine monitor \
				philo_utils err

SRCS			= $(addprefix src/, $(addsuffix .c, $(MSRCS)))
OBJS			= $(SRCS:.c=.o)

#				Compiler and Flags
CC				= cc
FLAGS			= -Wall -Werror -Wextra
SFLAGS			= -fsanitize=address

CFLAGS			= $(FLAGS) $(SFLAGS) -g

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
