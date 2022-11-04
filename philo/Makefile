NAME= philo
FLAGS= -Wall -Wextra -Werror
CC= cc
RM= rm -rf
SRC= $(wildcard *.c)
OBJS= $(SRC:.c=.o)

%.o:%.c
	$(CC) $(FLAGS) -I. -c $< -o $@

all:$(NAME)


$(NAME):$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o ${NAME}
clean:
	$(RM) $(OBJS) ~/Library/Caches


fclean:clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re