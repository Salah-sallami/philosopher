NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror -pthread
HEADER = philo.h
RM = rm -f

SRC = main.c utils.c utils2.c routine.c monitor.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
