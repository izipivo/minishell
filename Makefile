CFLAGS =			-Wall -Wextra -Werror -fsanitize=address

LIBS =				-L./libft -lft -L /usr/include -lreadline

HDRS =				minishell.h

HDRS_DIR =			includes/

CC =				cc

RM =				rm -rf

PWD_CMD =			pwd

CD_CMD =			cd

ECHO_CMD =			echo

PWD =				$(addprefix ${BINDIR}, ${PWD_CMD})

CD =				$(addprefix ${BINDIR}, ${CD_CMD})

ECHO =				$(addprefix ${BINDIR}, ${ECHO_CMD})

NAME =				minishell

SRC =				parser.c exec.c env_list.c

SRC_PWD =			pwd.c

SRC_CD =			cd.c

SRC_ECHO =			echo.c

SRC_DIR =			./src/

PWD_DIR =			./src/pwd/

CD_DIR =			./src/cd/

ECHO_DIR =			./src/echo/

HEADERS =			$(addprefix ${HDRS_DIR}, ${HDRS})

SOURCES =			$(addprefix ${SRC_DIR}, ${SRC})

SOURCES_PWD =		$(addprefix ${PWD_DIR}, ${SRC_PWD})

SOURCES_CD =		$(addprefix ${CD_DIR}, ${SRC_CD})

SOURCES_ECHO =		$(addprefix ${ECHO_DIR}, ${SRC_ECHO})

BUILDIR =			./obj/

BINDIR =			./bin/

PIPEX =				.bin/pipex

PIPEXDIR =			./pipex/

OBJS =				$(addprefix ${BUILDIR}, ${SRC:.c=.o})

OBJS_PWD =			$(addprefix ${BUILDIR}, ${SRC_PWD:.c=.o})

OBJS_CD =			$(addprefix ${BUILDIR}, ${SRC_CD:.c=.o})

OBJS_ECHO =			$(addprefix ${BUILDIR}, ${SRC_ECHO:.c=.o})

LIBFT_NAME =		libft.a

LIBFTDIR =			./libft/

LIBFT =				$(addprefix ${LIBFTDIR}, ${LIBFT_NAME})

.PHONY:				clean all fclean re

all:				${LIBFT} ${BINDIR} ${PIPEX} ${BUILDIR} ${PWD} ${CD} ${ECHO} ${NAME}

${PIPEX}:
					${MAKE} bonus -C ${PIPEXDIR}

${LIBFT}:
					${MAKE} -C ${LIBFTDIR}

${NAME}:			${OBJS} ${HEADERS}
					${CC} ${CFLAGS} ${LIBS} ${OBJS} -o $@

${BUILDIR}:
					mkdir -p ${BUILDIR}

${BINDIR}:
					mkdir -p ${BINDIR}

${PWD}:				${OBJS_PWD} ${HEADERS}
					${CC} ${CFLAGS} ${LIBS} ${OBJS_PWD} -o $@

${CD}:				${OBJS_CD} ${HEADERS}
					${CC} ${CFLAGS} ${LIBS} ${OBJS_CD} -o $@

${ECHO}:			${OBJS_ECHO} ${HEADERS}
					${CC} ${CFLAGS} ${LIBS} ${OBJS_ECHO} -o $@

${BUILDIR}%.o:		${SRC_DIR}%.c ${HEADERS} Makefile
					${CC} -c ${CFLAGS} $< -o $@

${BUILDIR}%.o:		${PWD_DIR}%.c ${HEADERS} Makefile
					${CC} -c ${CFLAGS} $< -o $@

${BUILDIR}%.o:		${CD_DIR}%.c ${HEADERS} Makefile
					${CC} -c ${CFLAGS} $< -o $@

${BUILDIR}%.o:		${ECHO_DIR}%.c ${HEADERS} Makefile
					${CC} -c ${CFLAGS} $< -o $@

clean:
					${MAKE} clean -C ${LIBFTDIR}
					${MAKE} clean -C ${PIPEXDIR}
					${RM} ${BUILDIR}

fclean:				clean
					${MAKE} fclean -C ${LIBFTDIR}
					${MAKE} fclean -C ${PIPEXDIR}
					${RM} ${BINDIR}
					${RM} ${NAME}

re:					fclean all

