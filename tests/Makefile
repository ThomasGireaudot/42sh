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
SOURCE	=	./test_split_str.c
OBJS	=	$(SOURCE:.c=.o)
OUT		=	../unit_tests
CC		=	gcc
CFLAGS	+=	-W -Wall -I../includes/ -fprofile-arcs -ftest-coverage

#####################################################
#
# 					RULES
#
#####################################################
all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(SOURCE) -o $(OUT) $(CFLAGS)

clean:
	$(RM) $(OBJS) *.gc* coverage.info

fclean: clean
	$(RM) $(OUT)
	$(RM) -r ../output

re: fclean all

run: re
	./$(OUT)

html_page: run
	gcov *.gcda
	lcov -c --directory . --output-file coverage.info
	genhtml coverage.info --output-directory ../output

.PHONY: all clean fclean re run html_page
