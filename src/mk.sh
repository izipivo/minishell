#!/bin/bash
#MacOS
cc -Werror -Wextra -Wall -fsanitize=address -L../libft -lft -L /usr/include -lreadline env_list.c parser.c exec.c -o parser&&./parser
cc -Werror -Wextra -Wall -L../libft -lft -L /usr/include -lreadline env_list.c parser.c exec.c -o parser&&./parser
#linux
cc -Werror -Wextra -Wall -fsanitize=address env_list.c parser.c exec.c -o parser -L../libft -lft -L /usr/include -lreadline&&./parser
cc -Werror -Wextra -Wall env_list.c parser.c exec.c -o parser -L../libft -lft -L /usr/include -lreadline&&./parser
