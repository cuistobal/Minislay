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
    sources/parsing/parsing.c \
    sources/parsing/handle_char.c \
    sources/parsing/create_tokens.c \
    minishell.c

OBJ = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
