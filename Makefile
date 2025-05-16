NAME = minislay

CC = gcc

CFLAGS = -Wall -Wextra -g3 -I$(INCLUDES)

BFLAGS = -Wall -Wextra -g3 -I$(INCLUDES_BONUS)

LDFLAGS = -lreadline

INCLUDES = includes

INCLUDES_BONUS = includes

SOURCES = \
    utilities/boolean_checks/tokenizer_bools_2.c \
    utilities/boolean_checks/state_management.c \
    utilities/boolean_checks/tokenizer_bools_1.c \
    utilities/my_strtok_r.c \
    utilities/tokens_utils.c/tokens_utils1.c \
    utilities/tokens_utils.c/parsing_utils.c \
    utilities/tokens_utils.c/parser_utils.c \
	utilities/builtins_utils/env_node.c \
	utilities/Libft/ft_strjoin.c \
	utilities/Libft/get_merged.c \
	utilities/free_utils.c \
	utilities/messages.c \
	utilities/mem_utils.c \
	utilities/misc.c \
	utilities/find_key.c \
	utilities/update_key_value.c \
	utilities/avl_tree/avl_tree_utils1.c \
	utilities/avl_tree/avl_tree_utils2.c \
	utilities/avl_tree/rotations.c \
	utilities/Libft/ft_itoa.c \
	utilities/inline_utilities.c \
	sources/initialisation.c\
	sources/builtins/cd/cd.c \
	sources/builtins/echo/echo.c \
	sources/builtins/env/env.c \
	sources/builtins/exit/exit.c \
	sources/builtins/pwd/pwd.c \
	sources/builtins/builtins.c \
    sources/parsing/tokenization/handle_special_chars.c \
    sources/parsing/tokenization/create_tokens.c \
    sources/parsing/tokenization/tokenizer.c \
    sources/parsing/algorithm/build_tree.c \
    sources/parsing/algorithm/parse_list.c \
    sources/parsing/algorithm/parse_non_terminal.c \
    sources/parsing/algorithm/parse_terminals.c \
    sources/parsing/algorithm/parse_terminals1.c \
	sources/execution/subshells/subshells.c \
	sources/execution/split_list.c \
	sources/execution/create_execution_node.c \
	sources/execution/traverse_ast.c \
	sources/execution/prepare_for_execution.c \
	sources/execution/expansions/expand.c \
	sources/execution/expansions/key_management.c \
	sources/execution/expansions/word_splitting.c \
	sources/execution/expansions/bonus/globing.c \
	sources/execution/expansions/bonus/match_pattern.c \
	sources/execution/expansions/bonus/test_globing_patterns.c \
	sources/execution/commands/command_types.c \
	sources/execution/commands/retrieve_path.c \
	sources/execution/commands/modify_token_types.c \
	sources/execution/commands/get_command_and_arguments.c \
	sources/execution/redirections/handle_redirections.c \
	sources/execution/redirections/handle_here_doc.c \
	sources/execution/processes/create_process.c \
	sources/execution/processes/ipc_module.c \
	sources/execution/processes/wait_module.c \
	sources/execution/handlers/handle_pipeline.c \
	minishell.c \
    minitester/utils/minislays_test_utils.c

SOURCES_BONUS = \


OBJ = $(SOURCES:.c=.o)

OBJ_BONUS = $(SOURCES_BONUS:.c=.o)

all: $(NAME)
	@ echo "G3t r34dy t0 5l4y (:"

$(NAME): $(OBJ)
	@ $(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c
	@ $(CC) $(CFLAGS) -c $< -o $@

$(BONUS): $(OBJ_BONUS)
	@ $(CC) $(BFLAGS) -c $< -o $@

bonus:
	@ echo "G3t r34dy t0 B0NU5 5l4y (:"

clean:
	@ rm -rf $(OBJ)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
