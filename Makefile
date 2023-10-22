NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra

LIB_RL_FLAG = -L/usr/include -lreadline



RM = rm -rf

#FOR UTIL
LIBFT_PATH = ./libft/
LIBFT_FILE = ${lib}
LIBFT_SRC = ${addprefix ${LIBFT_PATH}, ${LIBFT_FILE}}

# FOR BUILT-IN
BUILT_PATH = ./built_in/
BUILT_FILE = cd.c echo.c env.c exit.c export.c pwd.c unset.c
BUILT_SRC = ${addprefix ${BUILT_PATH}, ${BUILT_FILE}}

## FOR ENV
ENV_PATH = ./env_handle/
ENV_FILE = env_util.c get_value_from_key.c init_env.c
ENV_SRC = ${addprefix ${ENV_PATH}, ${ENV_FILE}}

RM = rm -rf

SRC =  ${LIBFT_SRC} ${ENV_SRC} minihell.c
OBJ = $(SRC:.c=.o)

$(NAME) : $(HEADER) $(lib) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_RL_FLAG) -o $(NAME)

all : $(NAME)

lib :
	(cd ${LIBFT_PATH} && make)

lib_clean :
	(cd ${LIBFT_PATH} && make fclean)

clean :
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : re fclean clean all
