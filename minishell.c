/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/17 15:09:15 by chrleroy         ###   ########.fr       */
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

int	minishell(char *input)
{
	t_tokn	*tokens;

	tokens = NULL;
	if (tokenize(&tokens, input, strlen(input)))
	{
    	//print_tokens(tokens);
		//	lexer(tokens) ? print_tokens(tokens) : printf("Syntax error.\n");
   		 	parse_script(tokens) ? print_tokens(tokens) : printf("Syntax error.\n");
	}
	else
		printf("Tokenization error.\n");
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
