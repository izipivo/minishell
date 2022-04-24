CFLAGS = -Wall -Wextra -Werror -L/usr/include -lreadline

HDRS = minishell.h

HDRS_DIR = includes/

CC = cc

RM = rm -rf

NAME = minishell

SRC = main.c

SRC_DIR = ./src/

HEADERS = $(addprefix ${HDRS_DIR}, ${HDRS})

SOURCES = $(addprefix ${SRC_DIR}, ${SRC})

PREOBJS = $(patsubst %.c, %.o, ${SOURCES})

BUILDIR = ./obj/

OBJS = $(addprefix ${BUILDIR}, ${SRC:.c=.o})

.PHONY:	clean all fclean re

all:	${BUILDIR} ${NAME}

#%.o :	%.c ${HEADERS} Makefile
#	${CC} -c ${CFLAGS} $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEADERS}
	${CC} ${CFLAGS} ${OBJS} -o $@

${BUILDIR}:
	mkdir -p ${BUILDIR}

${BUILDIR}%.o:	${SRC_DIR}%.c ${HEADERS} Makefile
	${CC} -c ${CFLAGS} $< -o $@

clean:
	${RM} ${BUILDIR}

fclean:		clean
	${RM} ${NAME}

re:	fclean all

