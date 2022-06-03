# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdursley <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 20:35:12 by pdursley          #+#    #+#              #
#    Updated: 2019/07/20 20:35:12 by pdursley         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../bin/pipex

LIST_INCL = ./mandatory/

LIST_FUNC = make_cmd.c pipex.c pipex_utils.c child.c

HDR_INCL = ./include/

HDR = pipex.h pipex_bonus.h

HDR_PIPEX = ${addprefix ${HDR_INCL}, ${HDR}}

CC = cc

FLAGS = -Wall -Werror -Wextra

UNITS_INCL = ./units/

UNITS_FUNC = ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c

GNL_INCL = ./gnl/

GNL_FUNC = get_next_line.c get_next_line_utils.c

UNITS_INCL_B = ./bonus/

UNITS_FUNC_B = pipex_bonus.c check_here_doc.c make_cmd_b.c in_out.c pipex_utils_b.c child_b.c

LIST = ${addprefix ${LIST_INCL}, ${LIST_FUNC}}

UNITS = ${addprefix ${UNITS_INCL}, ${UNITS_FUNC}}

UNITS_B = ${addprefix ${UNITS_INCL_B}, ${UNITS_FUNC_B}}

UNITS_GNL = ${addprefix ${GNL_INCL}, ${GNL_FUNC}}

OBJ1 = $(LIST:.c=.o)

OBJ2 = $(UNITS:.c=.o)

OBJ_B = $(UNITS_B:.c=.o)

OBJ_GNL = $(UNITS_GNL:.c=.o)

LIBFT = ../libft/libft.a

LIB = -L../libft -lft

${NAME}:	${OBJ1} ${OBJ2}
				${CC} ${FLAGS} $^ -o $@

%.o : %.c ${HDR_PIPEX} Makefile
	${CC} ${FLAGS} -c $< -o $@

all: ${NAME}

bonus: ${LIBFT} ${OBJ_GNL} ${OBJ_B} ${OBJ2} ${HDR_PIPEX}
			${CC} ${FLAGS} ${OBJ_GNL} ${OBJ_B} ${OBJ2} -o ${NAME} ${LIB}

${LIBFT}:
			make bonus -C ../libft

clean:
	rm -f ${OBJ1}
	rm -f ${OBJ2}
	rm -f ${OBJ_B}
	rm -f ${OBJ_GNL}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONNY : all bonus clean fclean re
