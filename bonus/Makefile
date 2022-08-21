CFLAGS =			-Wall -Wextra -Werror -fsanitize=address -g

LIBS =				-L./libft -lft -L /usr/include -lreadline

HDRS =				minishell.h pipex.h get_next_line.h

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

SRC =				parser/expand_dolar.c parser/expand_dollar2.c parser/token_list.c parser/parser.c\
					parser/env_list.c parser/copy_pipes.c parser/copy_pipes2.c parser/utils.c parser/cleaning.c\
					parser/fill_token.c parser/check.c exec/exec.c exec/exec2.c\
					pipex/pipex.c pipex/parents.c pipex/fork.c\
					utils/error_managment.c pipex/validation.c pipex/get_next_line.c\
					pipex/get_next_line_utils.c  pipex/child_fd.c pipex/check_func.c\
					export/export.c export/exp_func_two.c export/export_utils.c export/export_utils_two.c\
					export/exp_func.c\
					export/update.c export/unset.c export/unset_utils.c\
					export/same_for_export.c env/env.c exit/exit.c cd/cd.c main.c\
					echo/echo.c pwd/pwd.c wildcard/wldcard.c wildcard/wldcard2.c

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
