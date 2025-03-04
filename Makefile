NAME = minislay

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -I$(INCLUDES)
LDFLAGS = -lreadline

INCLUDES = includes

SOURCES = \
    utilities/boolean_checks/tokenizer_bools_2.c \
    utilities/boolean_checks/state_management.c \
    utilities/boolean_checks/tokenizer_bools_1.c \
    utilities/my_strtok_r.c \
    utilities/tokens_utils.c/tokens_utils1.c \
    utilities/tokens_utils.c/parsing_utils.c \
    utilities/tokens_utils.c/parser_utils.c \
	utilities/builtins_utils/env_node.c \
	sources/initialisation.c \
	sources/parsing/tokenization/check_word_content.c \
    sources/parsing/tokenization/modify_tokens.c \
    sources/parsing/tokenization/handle_special_chars.c \
    sources/parsing/tokenization/create_tokens.c \
    sources/parsing/tokenization/tokenizer.c \
    sources/parsing/tokenization/check_sub_tokens.c \
    sources/parsing/algorithm/build_tree.c \
    sources/parsing/algorithm/parse_list.c \
    sources/parsing/algorithm/parse_non_terminal.c \
    sources/parsing/algorithm/parse_terminals.c \
    sources/parsing/algorithm/parse_terminals1.c \
    minishell.c \
    minitester/utils/minislays_test_utils.c

OBJ = $(SOURCES:.c=.o)

all: $(NAME)
	@ echo "G3t r34dy t0 5l4y (:"

$(NAME): $(OBJ)
	@ $(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	
%.o: %.c
	@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	@ rm -rf $(OBJ)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
