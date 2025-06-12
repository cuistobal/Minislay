/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:40:32 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static void	promote_command_exit_code(t_shell *minishell)
{
	int		cccode;
	t_env	*ccode;

	ccode = find_special_env_variable(minishell, 6);
	if (!ccode)
		printf("ALED\n");
	else if (ccode->var[KEY])
		cccode = atoi(ccode->var[KEY]);
	append_exit_code(minishell, cccode, false);
}

//Needs rename -> it's currently the entrey to lexing && parsing
//Has to return an ast for exec // Needs to take an ast pointer as parameter
int	get_minishelled(t_shell **minishell, char *input)
{
	int				ret;
	t_tree			*ast;
	t_pars			*parser;
	t_tokn			*tokens;
	struct termios	*initial_state;

	ast = NULL;
	tokens = NULL;
	parser = NULL;
	if (!input)
		return (GENERAL_ERROR);
	if (!tokenize(&tokens, input, strlen(input)))
		return (printf(TOKENIZATION), free_tokens(tokens), PARSING_ERROR);
	if (!get_stacked(NULL, NULL, 0))
		return (printf("%s unmatched '('\n", SYNTAX), free_tokens(tokens), \
				GENERAL_ERROR);
	parser = define_parser(&ast, tokens);
	if (!parser || !parse_script(&parser))
		return (error_message(PARSING), free_tokens_adress(&tokens), \
				free_tree(ast), free(parser), GENERAL_ERROR);
	free(parser);
	(*minishell)->ast = ast;
	ret = traverse_ast(minishell, ast);
	return (promote_command_exit_code(*minishell), free_tree(ast), \
			free_tokens_adress(&tokens), ret);
//	return (append_exit_code(*minishell, ret, false), free_tree(ast), \
			free_tokens_adress(&tokens), ret);
}

//
int	main(int argc, char **argv, char **envp)
{
	int		ret;
	t_shell	*minishell;
	char	*user_input;
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
