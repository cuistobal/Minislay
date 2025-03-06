/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/03/06 14:28:35 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Needs rename -> it's currently the entrey to lexing && parsing
//Has to return an ast for exec // Needs to take an ast pointer as parameter
int	get_minishelled(t_shel **minishell, char *input)
{
	t_tree	*ast;
	t_pars	*parser;
	t_tokn	*tokens;

	ast = NULL;
	tokens = NULL;
	parser = NULL;
	if (tokenize(&tokens, input, strlen(input)))
	{
		if (get_stacked(NULL, NULL, 0))
		{
			if (define_parser(&parser, &ast, tokens))
			{
				if (parse_script(&parser))
				{
				//	print_ast(ast, "ROOT", "ROOT", 0);
				//	print_env((*minishell)->envp);
          			traverse_ast(*minishell, ast);
				//	printf("%p\n", *minishell);//Shut down compilatione rro msg
				}
				else
					printf("Failed to parse.\n");
			}
		}
		else
			printf("Unmatched (.\n");
	}
	else
		printf("Tokenization error.\n");
	free_tokens(tokens);
	
	return (0);
}

//
int	mini_loop(t_shel **minishell)
{
    char	*user_input;

    while (1)
	{
        user_input = readline(MINISLAY);
        if (user_input)
        {
            add_history(user_input);
			get_minishelled(minishell,user_input);
            free(user_input);
        }
    }
    return 0;
}

//
static bool	mini_setup(t_shel **minishell, char **envp)
{
	*minishell = (t_shel *)malloc(sizeof(t_shel));
	if (*minishell)
	{
		(*minishell)->envp = NULL;
		(*minishell)->local = NULL;
		(*minishell)->expt = NULL;
        return (set_env(minishell, envp));
	}
	return (*minishell);
}

//
int	main(int argc, char **argv, char **envp)
{
	t_shel	*minishell;

	(void)argv;
	minishell = NULL;
	if (argc == 1)
	{
		if (mini_setup(&minishell, envp))
			return (mini_loop(&minishell));
	}
    return 0;
	//return (error());
}

