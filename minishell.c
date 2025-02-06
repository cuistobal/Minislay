/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/06 13:45:03 by chrleroy         ###   ########.fr       */
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

void	print_tokens(t_tokn *tokens)
{
	int	index;

	index = 0;
	while (tokens)	
	{
		printf("%d	->	%s\n", index, tokens->token);
		tokens = tokens->next;
		index++;
	}
}

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
			print_tokens(tokens);
	}
	else
		printf("Usage\n");
}
