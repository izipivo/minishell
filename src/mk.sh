#!/bin/bash
#MacOS
cc  -L../libft -lft -L /usr/include -lreadline env_list.c parser.c -o parser&&./parser

#linux
cc env_list.c parser.c -o parser -L../libft -lft -L /usr/include -lreadline&&./parser
