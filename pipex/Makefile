CFLAGS = -Wall -Wextra -Werror

HDRS = pipex.h get_next_line.h

HDRS_BONUS = pipex_bonus.h get_next_line_bonus.h

HEADERS = $(addprefix includes/, ${HDRS})

CC = cc

RM = rm -f

LFT = -L ${LIBFTDIR} -lft

BINDIR = ../bin/

NAME = $(addprefix ${BINDIR}, pipex)

SRC = pipex.c validation.c parents.c error_managment.c fork.c\
		get_next_line.c get_next_line_utils.c

LIBFT_NAME = libft.a

LIBFTDIR = ../libft/

BUILDIR = ../obj/

OBJS = $(addprefix ${BUILDIR}, ${SRC:.c=.o})

LIBFT = $(addprefix ${LIBFTDIR}, ${LIBFT_NAME})

SOURCES = $(addprefix src/, ${SRC})

.PHONY:	clean all fclean re

all:			${NAME}

${LIBFT}:
				${MAKE} re -C ${LIBFTDIR}

${NAME}:		${LIBFT} ${BINDIR} ${OBJS}
				${CC} ${FLAGS} ${OBJS} -o $@ ${LFT}

${BINDIR}:
				mkdir ${BINDIR}

${BUILDIR}:
				mkdir ${BUILDIR} 

${BUILDIR}%.o:	src/%.c ${HEADERS} ${{BUILDIR} ${LIBFT} Makefile
				${CC} ${FLAGS} -c $< -o $@


clean:
				@${MAKE} clean -C ${LIBFTDIR}

fclean:			clean
				@${RM} ${NAME}
				@${MAKE} fclean -C ${LIBFTDIR}

re:				fclean all
