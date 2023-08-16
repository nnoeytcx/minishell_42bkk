NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIBFLAG = -L/usr/include -lreadline

SRC = minihell.c

RM = rm -rf

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFLAG) -o $(NAME)

all : $(NAME)

clean :
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : re fclean clean all
