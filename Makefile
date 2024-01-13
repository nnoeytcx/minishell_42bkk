NAME = minishell

CC = cc

LIB_RL_PATH = $(shell brew --prefix readline)

CFLAGS = -I${LIB_RL_PATH}/include/ -Wall -Werror -Wextra -g 

VALGRIND = valgrind --leak-check=full -s --track-fds=yes

# CFLAGS = -Wall -Werror -Wextra -fsanitize=address --show-leak-kinds=all 

LIB_RL_FLAG =  -lreadline -L${LIB_RL_PATH}/lib/

RM = rm -rf

LIBFT_DIR = ./libft/
LIBFT_FILE = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c \
			ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
			ft_lstsize.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
			ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
			ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
			ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
			ft_tolower.c ft_toupper.c

ENV_DIR = ./env_handle/
ENV_FILE = get_value_from_key.c init_env.c env_join.c env_edit.c

EXE_DIR = ./exe/
EXE_FILE = execute.c get_exe_data.c exe_error.c open_file.c execute_util.c \
		child_and_parent.c here_doc_event.c

FREE_DIR = ./free/
FREE_FILE = free_token.c free.c

PARSER_DIR = ./parser/
PARSER_FILE = in_file.c expand_util.c parser.c print_tok.c set_mode.c expand.c error_parser.c \
			ft_split_special.c ft_split_pipe.c ft_split_sp_util.c util.c

BUILTIN_DIR = ./builtin/
BUILTIN_FILE = pwd.c env.c cd.c echo.c exit.c export.c unset.c is_builtin.c cd_helper.c 

LIBFT_SRC = ${addprefix ${LIBFT_DIR}, ${LIBFT_FILE}}
EXE_SRC = ${addprefix ${EXE_DIR}, ${EXE_FILE}}
ENV_SRC = ${addprefix ${ENV_DIR}, ${ENV_FILE}}
FREE_SRC  = ${addprefix ${FREE_DIR}, ${FREE_FILE}}
PARSER_SRC  = ${addprefix ${PARSER_DIR}, ${PARSER_FILE}}
BUILTIN_SRC  = ${addprefix ${BUILTIN_DIR}, ${BUILTIN_FILE}}

SRC =  ${LIBFT_SRC} ${ENV_SRC} ${FREE_SRC} ${PARSER_SRC} ${EXE_SRC} ${BUILTIN_SRC} get_prompt_and_init.c minishell.c
OBJ =  $(SRC:.c=.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_RL_FLAG) -o $(NAME)

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
