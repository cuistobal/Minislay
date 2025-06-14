/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 15:31:11 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Needs rename -> it's currently the entrey to lexing && parsing
//Has to return an ast for exec // Needs to take an ast pointer as parameter
int	get_minishelled(t_shell **minishell, char *input)
{
	int				ret;
	t_tree			*ast;
	t_pars			*parser;
	t_tokn			*tokens;

	ast = NULL;
	tokens = NULL;
	parser = NULL;
	if (!input)
		return (GENERAL_ERROR);
	if (!tokenize(&tokens, input, strlen(input)))
		return (free_tokens(tokens), append_exit_code(*minishell, \
					PARSING_ERROR), PARSING_ERROR);
	if (!get_stacked(NULL, NULL, 0))
		return (free_tokens(tokens), append_exit_code(*minishell, \
					GENERAL_ERROR), parenthesis_error(), GENERAL_ERROR);
	parser = define_parser(&ast, tokens);
	if (!parser || !parse_script(&parser))
		return (free_tokens(tokens), free_tree(ast), free(parser), \
				append_exit_code(*minishell, GENERAL_ERROR), GENERAL_ERROR);
	free(parser);
	(*minishell)->ast = ast;
	ret = traverse_ast(minishell, ast);
	return (free_tree((*minishell)->ast), ret);
}

//
int	main(int argc, char **argv, char **envp)
{
	int		ret;
	t_shell	*minishell;
	char	rl_prompt[BUFFER_SIZE];

	(void)argc;
	(void)argv;
	minishell = (t_shell *)malloc(sizeof(t_shell));
	if (!minishell)
		return (GENERAL_ERROR);
	minishell->execution = NULL;
	minishell->ast = NULL;
	minishell->pids = NULL;
	minishell->pipefd = NULL;
	minishell->original_stds[0] = -1;
	minishell->original_stds[1] = -1;
	if (!build_env(&minishell, envp))
		return (GENERAL_ERROR);
	build_rl_prompt(rl_prompt, argv[0]);
	ret = start_process(&minishell, rl_prompt);
	free_minishell(minishell);
	minishell = NULL;
	return (ret);
}
