#!/bin/bash
cc  -L../libft -lft -L /usr/include -lreadline parser.c -o parser&&./parser
