CFLAGS =			-Wall -Wextra -Werror -fsanitize=address -g

LIBS =				-L./libft -lft -L /usr/include -lreadline

HDRS =				minishell_bonus.h pipex_bonus.h get_next_line_bonus.h

HDRS_DIR =			./includes/

INCLUDE = 			-I ${HDRS_DIR}

CC =				cc -D MAIN=0

ifeq ($(MAKECMDGOALS), t)
CC =				cc -D TEST=0
endif

ifeq ($(MAKECMDGOALS), g)
CC =				cc -D GDB=0
endif

RM =				rm -rf

NAME =				minishell_bonus

SRC =				parser/expand_dolar_bonus.c parser/expand_dollar2_bonus.c parser/token_list_bonus.c parser/parser_bonus.c\
					parser/env_list_bonus.c parser/copy_pipes_bonus.c parser/copy_pipes2_bonus.c parser/utils_bonus.c parser/cleaning_bonus.c\
					parser/fill_token_bonus.c parser/check_bonus.c exec/exec_bonus.c exec/exec2_bonus.c\
					pipex/pipex_bonus.c pipex/parents_bonus.c pipex/fork_bonus.c\
					utils/error_managment_bonus.c pipex/validation_bonus.c pipex/get_next_line_bonus.c\
					pipex/get_next_line_utils_bonus.c  pipex/child_fd_bonus.c pipex/check_func_bonus.c\
					export/export_bonus.c export/exp_func_two_bonus.c export/export_utils_bonus.c export/export_utils_two_bonus.c\
					export/exp_func_bonus.c\
					export/update_bonus.c export/unset_bonus.c export/unset_utils_bonus.c\
					export/same_for_export_bonus.c env/env_bonus.c exit/exit_bonus.c cd/cd_bonus.c main_bonus.c\
					echo/echo_bonus.c pwd/pwd_bonus.c wildcard/wldcard_bonus.c wildcard/wldcard2_bonus.c

SRC_DIR =			./src/

HEADERS =			$(addprefix ${HDRS_DIR}, ${HDRS})

SOURCES =			$(addprefix ${SRC_DIR}, ${SRC})

BUILDIR = 			./obj/

BUILDIRS =			echo/ wildcard/ cd/ env/ pwd/ utils/ pipex/ exec/ parser/ export/ exit/ libft/

BLDRS =				$(addprefix ${BUILDIR}, ${BUILDIRS})

OBJS =				$(addprefix ${BUILDIR}, ${SRC:.c=.o})

LIBFT_NAME =		libft.a

LIBFTDIR =			./libft/

LIBFT =				$(addprefix ${LIBFTDIR}, ${LIBFT_NAME})

.PHONY:				clean all fclean re

all:				${BUILDIR} ${BLDRS} ${LIBFT} ${NAME}

t:					all

g:					all

${LIBFT}:
					${MAKE} -C ${LIBFTDIR}

${NAME}:			${OBJS} ${HEADERS} 
					${CC} ${CFLAGS} ${OBJS} -o $@ ${LIBS}
					mv $@ ../

${BUILDIR}:
					mkdir -p $@

${BLDRS}:
					mkdir -p $@

${BUILDIR}%.o:		${SRC_DIR}%.c ${HEADERS} Makefile
					${CC} ${INCLUDE} -c ${CFLAGS} $< -o $@

clean:
					${MAKE} clean -C ${LIBFTDIR}
					${RM} ${BUILDIR}

fclean:				clean
					${MAKE} fclean -C ${LIBFTDIR}
					${RM} ../${NAME}

re:					fclean all
