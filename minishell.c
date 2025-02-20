/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/20 17:48:33 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
int main(int argc, char **argv. char **envp)
{
	t_tokn	*tokens;
	char 	*user_prompt;

	tokens = NULL;
	*user_prompt = NULL;
	if (argc == 2)
	{
		user_prompt = readline();		
	}
	printf("Usage\n");
}*/

//
static void	free_tokens(t_tokn *tokens)
{
	t_tokn *temp;

	temp = tokens;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->value)
			free (temp->value);
		free (temp);
	}
}

//
static void	print_tokens(t_tokn *tokens)
{
	int	index;

	index = 0;
	while (tokens)	
	{
		printf("%d	->	%d	%s\n", index, tokens->type, tokens->value);
		tokens = tokens->next;
		index++;
	}
}

/*
static void	print_list(t_bloc *list)
{
	int	index;

	index = 0;
	while (list)
	{
		printf("Command bloc %d:\n", index);
		print_tokens(list->token);
		list = list->next;
		index++;
	}
}*/
/*
//Will become minishell for subshells recursive calls.
int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_tokn	*tokens;

	(void)envp;
	input = NULL;
	tokens = NULL;	
	if (argc == 2)
	{
		input = argv[1];
		if (parsing(&tokens, input))
		{
			print_tokens(tokens);
			free_tokens(tokens);
		}
	}
	else
		printf("Usage\n");
}*/

static void	print_ast_DFS(t_tree *ast, int lvl, char c)
{
	if (ast)
	{
		printf("%c level %d\n", c, lvl);
		while (ast->tokens)
		{
			printf("%s\n", ast->tokens->value);
			ast->tokens = ast->tokens->next;
		}
		print_ast_DFS(ast->left, lvl + 1, 'g');
		print_ast_DFS(ast->right, lvl + 1, 'd');
	}
}

int	minishell(char *input)
{
//	t_bloc	*list;
	t_tree	*ast;
	t_tokn	*tokens;

	ast = NULL;
//	list = NULL;
	tokens = NULL;
	if (tokenize(&tokens, input, strlen(input)))
	{
    //	print_tokens(tokens);
		//	lexer(tokens) ? print_tokens(tokens) : printf("Syntax error.\n");
   	//	parse_script(&list, tokens, tokens) ? print_list(list) : printf("Syntax error.\n");
	//	parse_script(&list, tokens, tokens) ? print_tokens(tokens) : printf("Syntax error.\n");
		parse_script(&ast, tokens) ? print_tokens(tokens) : printf("Syntax error.\n");
	}
	else
		printf("Tokenization error.\n");
	print_ast_DFS(ast, 0, 'r');
	free_tokens(tokens);
	return (0);
}

int main(void)
{
    char	*user_input;

    while (1)
	{
        user_input = readline(MINISLAY);
        if (user_input[0] != '\0')
            add_history(user_input);
        if (strcmp(user_input, "EXIT") == 0)
		{
        	free(user_input);
			break;
		}
		else
			minishell(user_input);
        free(user_input);
    }
    return 0;
}
