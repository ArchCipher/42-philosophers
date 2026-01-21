#				Library and Project names
NAME			= philo_bonus
LIB				= libftprintf.a
LIBDIR			= ft_printf

#				Includes
HEADER			= philo.h
INC				= -I. -I$(LIBDIR)

#				Sources & Objects
MSRCS			= \
				philo parser init \
				child monitor \
				philo_utils err

SRCS			= $(addprefix src/, $(addsuffix .c, $(MSRCS)))
OBJS			= $(SRCS:.c=.o)

#				Compiler and Flags
CC				= cc
FLAGS			= -Wall -Werror -Wextra
SFLAGS			= -fsanitize=address

CFLAGS			= $(FLAGS) $(SFLAGS) -g
LDFLAGS			= -L$(LIBDIR) -lftprintf

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: lib $(NAME)

lib:
	@make -C $(LIBDIR)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

clean:
	@make -C $(LIBDIR) clean
	rm -f $(OBJS)

fclean: clean
	@make -C $(LIBDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re lib
