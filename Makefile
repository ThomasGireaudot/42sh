##
## EPITECH PROJECT, 2020
## makefile
## File description:
## makefile template
##

#####################################################
#
# 					PARAMETERS
#
#####################################################
SOURCE	=	./main.c \
			./src/echo.c\
			./src/sh.c\
			./src/prompt_command.c\
			./src/hist_l.c\
			./src/split_str.c\
			./src/str_s/str_s.c\
			./src/str_s/str_s_pop.c\
			./src/format/check_format.c\
			./src/format/check_redirections.c\
			./src/format/check_pipe.c\
			./src/format/check_and_separator.c\
			./src/format/check_or_separator.c\
			./src/parsing/separators_parsing.c\
			./src/execution/separators_exec.c\
			./src/execution/pipes_exec.c\
			./src/execution/cmd_execute.c\
			./src/execution/exec_binaries.c\
			./src/execution/status_management.c\
			./src/execution/forking.c\
			./src/execution/my_chdir.c\
			./src/execution/my_setenv.c\
			./src/execution/my_unsetenv.c\
			./src/execution/error_binaries.c\
			./src/execution/redirections_management_nodup.c\
			./src/execution/child_process/child.c\
			./src/execution/child_process/redirections_management.c
OBJS	=	$(SOURCE:.c=.o)
OUT		=	42sh
CC		=	gcc
CFLAGS	+=	-W -Wall -Iincludes/

#####################################################
#
# 					RULES
#
#####################################################
all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

valgrind:
	gcc $(SOURCE) $(CFLAGS) -Iincludes/ -o $(OUT) -g

clean:
	$(RM) $(OBJS) *~ *# *.o *.gc* src/*.gc* src/*.o

fclean: clean
	$(RM) $(OUT)

re: fclean all

debug: CFLAGS += -ggdb3
debug: fclean $(OBJS)
	$(CC) $(OBJS) -ggdb3 -o $(OUT)

.PHONY: all clean fclean re debug
