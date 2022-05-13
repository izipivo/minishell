#!/bin/bash
#MacOS
cc -fsanitize=address -L../libft -lft -L /usr/include -lreadline env_list.c parser.c -o parser&&./parser
cc -L../libft -lft -L /usr/include -lreadline env_list.c parser.c -o parser&&./parser
#linux
cc -fsanitize=address env_list.c parser.c -o parser -L../libft -lft -L /usr/include -lreadline&&./parser
cc env_list.c parser.c -o parser -L../libft -lft -L /usr/include -lreadline&&./parser
