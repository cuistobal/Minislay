NAME = minislay

CC = gcc
FLAGS = -Wall -Werror -Wextra -g3 -I$(INCLUDES)

INCLUDES = includes

SOURCES = \
    utilities/my_strtok_r.c \
    utilities/boolean_checks/tokenizer_bools_2.c \
    utilities/boolean_checks/state_management.c \
    utilities/boolean_checks/tokenizer_bools_1.c \
    utilities/stack_operations.c \
	sources/parsing/parser.c \
	sources/parsing/lexer.c \
	minishell.c

OBJ = $(SOURCES:.c=.o)

all: $(NAME)
	@ echo "G3t r34dy t0 5l4y (:"

$(NAME): $(OBJ)
	@ $(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	@ $(CC) $(FLAGS) -c $< -o $@

clean:
	@ rm -f $(OBJ)

fclean: clean
	@ rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
