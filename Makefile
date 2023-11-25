NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra

LIB_RL_FLAG = -L/usr/include -lreadline

RM = rm -rf

#FOR UTIL
LIBFT_PATH = ./libft/
LIBFT_FILE = ${wildcard ${LIBFT_PATH}*.c}
LIBFT_SRC = ${LIBFT_FILE}

# FOR BUILT-IN
BUILT_PATH = ./built_in/
BUILT_FILE = cd.c echo.c env.c exit.c export.c pwd.c unset.c
BUILT_SRC = ${addprefix ${BUILT_PATH}, ${BUILT_FILE}}

## FOR ENV
ENV_PATH = ./env_handle/
ENV_FILE = env_util.c get_value_from_key.c init_env.c env_join.c
ENV_SRC = ${addprefix ${ENV_PATH}, ${ENV_FILE}}

## FOR EXE
EXE_PATH = ./exe/
EXE_FILE = exe.c get_exe_data.c exe_error.c
EXE_SRC = ${addprefix ${EXE_PATH}, ${EXE_FILE}}

## FOR PARSER
PARSER_PATH = ./parser/
PARSER_FILE = parser.c print_tok.c set_mode.c expand.c error_parser.c
PARSER_SRC  = ${addprefix ${PARSER_PATH}, ${PARSER_FILE}}

RM = rm -rf

SRC =  ${LIBFT_SRC} ${ENV_SRC} ${PARSER_SRC} ${EXE_SRC} minishell.c
OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_RL_FLAG) -o $(NAME)

all : $(NAME)

clean :
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : re fclean clean all
