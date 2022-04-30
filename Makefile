CFLAGS = -Wall -Wextra -Werror

LIBS = -L ./libft -L/usr/include -lft -lreadline

HDRS = minishell.h

HDRS_DIR = includes/

CC = cc

RM = rm -rf

NAME = parser

SRC = parser.c

SRC_DIR = ./src/

HEADERS = $(addprefix ${HDRS_DIR}, ${HDRS})

SOURCES = $(addprefix ${SRC_DIR}, ${SRC})

PREOBJS = $(patsubst %.c, %.o, ${SOURCES})

BUILDIR = ./obj/

OBJS = $(addprefix ${BUILDIR}, ${SRC:.c=.o})

LIBFT_NAME = libft.a

LIBFTDIR = ./libft/

LIBFT = $(addprefix ${LIBFTDIR}, ${LIBFT_NAME})

.PHONY:	clean all fclean re

all:	${LIBFT} ${BUILDIR} ${NAME}

${LIBFT}:
	${MAKE} -C ${LIBFTDIR}

${NAME}:	${OBJS} ${HEADERS}
	${CC} ${CFLAGS} ${OBJS} -o $@ ${LIBS}

${BUILDIR}:
	mkdir -p ${BUILDIR}

${BUILDIR}%.o:	${SRC_DIR}%.c ${HEADERS} Makefile
#	${CC} -c ${CFLAGS} $< -o $@ ${LIBS} 
	${CC} -c ${CFLAGS} $< -o $@

clean:
	${MAKE} clean -C ${LIBFTDIR}
	${RM} ${BUILDIR}

fclean:		clean
	${MAKE} fclean -C ${LIBFTDIR}
	${RM} ${NAME}

re:	fclean all

