/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/23 17:38:38 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

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
}
*/
/*
static void	print_ast_BFS(t_tree *ast)
{
    int front = 0, rear = 0;
    t_tree **queue, *current;

	current = NULL;
	if (ast)
	{
   		queue = (t_tree **)malloc(1000 * sizeof(t_tree*)); // Taille fixe pour simplifier
    	queue[rear++] = ast;
	    while (front < rear)
		{
    		current = queue[front++];
        	printf("%s ", current->tokens->value);
        	if (current->left)
            	queue[rear++] = current->left;
        	if (current->right)
            	queue[rear++] = current->right;
    		}
    	free(queue);
	}
}*/

static void	print_ast_DFS(t_tree *ast, int lvl, char *c, char *s)
{
	if (ast)
	{
		printf("\n%s	%d	%s\n", c, lvl, s);
		while (ast->tokens)
		{
			printf("%s ", ast->tokens->value);
			ast->tokens = ast->tokens->next;
		}
		printf("\n");

		print_ast_DFS(ast->left, lvl + 1, "left", c);
		
		print_ast_DFS(ast->right, lvl + 1, "right", c);
	}
}

int	minishell(char *input)
{
//	t_bloc	*list;
	t_tree	*ast;
//	t_tokn	*list;
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
	//	parse_script(tokens) ? print_tokens(tokens) : printf("Syntax error.\n");
	}
	else
		printf("Tokenization error.\n");
	ast ? print_ast_DFS(ast, 0, "root", "root") : printf("L AST EST VIDE SES GRAND MORTS OUAIS\n");
//	ast ? print_ast_BFS(ast) : printf("L AST EST VIDE SES GRAND MORTS OUAIS\n");
	//print_list(list);	
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
