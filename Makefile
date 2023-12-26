NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra

VALGRIND = callgrind --leak-check=full --show-leak-kinds=all -s
# CFLAGS = -Wall -Werror -Wextra -fsanitize=address

LIB_RL_FLAG = -L/usr/include -lreadline 

RM = rm -rf

#FOR UTIL
LIBFT_PATH = ./libft/
LIBFT_FILE = ${wildcard ${LIBFT_PATH}*.c}
LIBFT_SRC = ${LIBFT_FILE}

#FOR HEADER
HEADER_PATH = ./header/
HEADER_FILE = ${wildcard ${HEADER_PATH}*.h}
HEADER_SRC = ${LIBFT_FILE}

## FOR ENV
ENV_PATH = ./env_handle/
ENV_FILE = env_util.c get_value_from_key.c init_env.c env_join.c env_edit.c
ENV_SRC = ${addprefix ${ENV_PATH}, ${ENV_FILE}}

## FOR EXE
EXE_PATH = ./exe/
EXE_FILE = exe.c get_exe_data.c exe_error.c open_file.c get_next_line.c
EXE_SRC = ${addprefix ${EXE_PATH}, ${EXE_FILE}}

## FOR FREE
FREE_PATH = ./free/
FREE_FILE = free_token.c
FREE_SRC  = ${addprefix ${FREE_PATH}, ${FREE_FILE}}

## FOR PARSER
PARSER_PATH = ./parser/
PARSER_FILE = parser.c print_tok.c set_mode.c expand.c error_parser.c ft_split_special.c ft_split_pipe.c ft_split_sp_util.c
PARSER_SRC  = ${addprefix ${PARSER_PATH}, ${PARSER_FILE}}

## FOR BUILTIN
BUILTIN_PATH = ./builtin/
BUILTIN_FILE = pwd.c env.c
BUILTIN_SRC  = ${addprefix ${BUILTIN_PATH}, ${BUILTIN_FILE}}



RM = rm -rf

SRC =  ${LIBFT_SRC} ${ENV_SRC} ${FREE_SRC} ${PARSER_SRC} ${EXE_SRC} ${BUILTIN_SRC} minishell.c
OBJ =  $(SRC:.c=.o)

%.o: %.c ${HEADER_FILE}
	@ echo "compiling $@ object file...."
	@ ${CC} -c $< -o $@
	# @ clear

$(NAME) : $(OBJ)
	@ $(CC) $(CFLAGS) $(OBJ) $(LIB_RL_FLAG) -o $(NAME)
	@ echo "compile with [${CFLAGS}] finish\nRUN ./minishell to run minishell"

all : $(NAME)

valgrind : ${NAME}
	${VALGRIND} ./${NAME}

leaks :
	leaks -atExit -- ./${NAME}

clean :
	@ $(RM) $(OBJ)
fclean : clean
	@ $(RM) $(NAME)

re : fclean all

.PHONY : re fclean clean all
