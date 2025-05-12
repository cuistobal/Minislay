/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/12 19:48:18 by ynyamets         ###   ########.fr       */
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
	if (!tokenize(&tokens, input, strlen(input)))
		return (printf(TOKENIZATION), free_tokens(tokens), -1);
	if (!get_stacked(NULL, NULL, 0))
		return (printf("%s unmatched '('\n", SYNTAX), -1);
	if (!define_parser(&parser, &ast, tokens) || !parse_script(&parser))
		return (printf(PARSING), free_tokens(tokens), free_tree(ast), -1);
	/*
 	 *
	 *	I forgot an important point here ->	redirections are handled first, then
	 *	the tree is traversed for execution.
	 *
	 *	We need to make decision about this implementation.
	 *	IMO, we could handle it gracefully by splitting redirections and
	 *	treating them first, hence we'd only have to perform the dup()'s while
	 *	executing.
	 *	Otherwise, we could choose to traverse the tree twice. First we'd check
	 *	redirections and ssecond execute commands.
	 *
 	 */


	traverse_ast(minishell, ast);
	return (free_tree(ast), 0);
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
	*minishell = malloc(sizeof(t_shel));
	if (!*minishell)
		return (false);
	(*minishell)->envp = NULL;
	(*minishell)->local = NULL;
	(*minishell)->command = NULL;
	(*minishell)->expt = NULL;
	if (!set_env(minishell, envp))
	return (false);
	if (!append_specials(minishell))
		return (false);
	return true;
}

//
int	main(int argc, char **argv, char **envp)
{
	t_shel	*minishell;

	/*while (*envp)
	{
    	printf("%s\n", *envp);
    	envp++;
	}*/

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
