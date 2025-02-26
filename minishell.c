/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/26 09:07:34 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Needs rename -> it's currently the entrey to lexing && parsing
//Has to return an ast for exec // Needs to take an ast pointer as parameter
int	minishell(char *input)
{
	t_tree	*ast;
	t_pars	*parser;
	t_tokn	*tokens;

	ast = NULL;
	tokens = NULL;
	parser = NULL;
	if (tokenize(&tokens, input, strlen(input)))
	{
		if (define_parser(&parser, &ast, tokens))
		{
			if (parse_script(&parser))
				print_ast(ast, "ROOT", "ROOT", 0);
			else
				printf("Failed to parse.\n");
		}
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
