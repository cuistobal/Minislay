/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/22 14:58:06 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
//	TESTS
//
#include <stdio.h>
#include <stdlib.h>

static void	print_tokens(t_tokn *tokens);



// Fonction pour calculer la hauteur de l'arbre
int height(t_tree* root)
{
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Fonction pour imprimer un niveau de l'arbre
void printLevel(t_tree* root, int level, int h)
{
    if (root == NULL)
        return;
    if (level == 1)
	{
        for (int i = 0; i < h; i++)
            printf("  ");
			printf("%d	&&	%d	", level, h);	
		while (root->tokens)
		{
			printf("%s ", root->tokens->value);
			root->tokens = root->tokens->next;
		}
		printf("\n");
        for (int i = 0; i < h; i++)
            printf("  ");
    }
	else if (level > 1)
	{
        printLevel(root->left, level - 1, h - 1);
        printLevel(root->right, level - 1, h + 1);
    }
}

// Fonction pour imprimer l'arbre par niveau
void printTree(t_tree* root)
{
    int h = height(root);

    for (int i = 1; i <= h; i++)
	{
        printLevel(root, i, 0);
        printf("\n");
    }
}

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
}

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
}*/

int	minishell(char *input)
{
//	t_bloc	*list;
//	t_tree	*ast;
//	t_tokn	*list;
	t_tokn	*tokens;

//	ast = NULL;
//	list = NULL;
	tokens = NULL;
	if (tokenize(&tokens, input, strlen(input)))
	{
    //	print_tokens(tokens);
		//	lexer(tokens) ? print_tokens(tokens) : printf("Syntax error.\n");
   	//	parse_script(&list, tokens, tokens) ? print_list(list) : printf("Syntax error.\n");
	//	parse_script(&list, tokens, tokens) ? print_tokens(tokens) : printf("Syntax error.\n");
	//	parse_script(&ast, tokens) ? print_tokens(tokens) : printf("Syntax error.\n");
		parse_script(tokens) ? print_tokens(tokens) : printf("Syntax error.\n");
	}
	else
		printf("Tokenization error.\n");
	//ast ? print_ast_DFS(ast, 0, 'r') : printf("L AST EST VIDE SES GRAND MORTS OUAIS\n");
	//ast ? printTree(ast) : printf("L AST EST VIDE SES GRAND MORTS OUAIS\n");
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
