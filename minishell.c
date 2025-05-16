/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/16 08:38:03 by chrleroy         ###   ########.fr       */
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
	t_exec	*execution;

	ast = NULL;
	tokens = NULL;
	parser = NULL;	
	execution = NULL;
	if (!input)
		return (GENERAL_ERROR);
	if (!tokenize(&tokens, input, strlen(input)))
		return (printf(TOKENIZATION), free_tokens(tokens), GENERAL_ERROR);
	if (!get_stacked(NULL, NULL, 0))
		return (printf("%s unmatched '('\n", SYNTAX), GENERAL_ERROR);
	if (!define_parser(&parser, &ast, tokens) || !parse_script(&parser))
		return (printf(PARSING), free_tokens(tokens), free_tree(ast), GENERAL_ERROR);
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

	traverse_ast(minishell, ast, &execution);

/*
	if (is_state_active(code, EXIT_STATUS))
		return (free_tree(ast), EXIT_STATUS);
*/
	return (free_tree(ast), 0);
}

//
int	mini_loop(t_shel **minishell, char *terminal_name)
{
    int             retcode;
    char			*user_input;

    while (1)
    {
        user_input = readline(terminal_name);
        add_history(user_input);
        retcode = get_minishelled(minishell,user_input);
        free(user_input);
        user_input = NULL;
    }
    return (retcode);
}

//
t_env	*build_environement(char **envp)
{
    t_env	*new;
    t_env	*tail;
    t_env	*head;

	head = NULL;
	while (*envp)
	{	
		if (!head)
		{
			new = create_env_node(&head, strdup(*envp));
			if (!new)
				return (false);
			tail = head;
		}
		else
		{
			new = create_env_node(&tail, strdup(*envp));
			if (!new)
				return (false);
		}
		envp++;
	}
	return (head);	
}

//
bool	build_env(t_shel **minishell, char **envp)
{
    int     index;
    t_env	*head;
	t_avlt	*root;

    index = 0;
    if (!*minishell)
		return (false);
	root = NULL;
	(*minishell)->envp = build_environement(envp);
	head = (*minishell)->envp;
	while (head)
	{
		insert_avlt_node(&root, head, strlen(head->var[KEY]));
		head = head->next;
	}
	(*minishell)->expt = root;
	append_specials(minishell);
	return (true);
}

//
int	main(int argc, char **argv, char **envp)
{
	t_shel	*minishell;
    char	*user_input;
	char	rl_prompt[BUFFER_SIZE];

	minishell = (t_shel *)malloc(sizeof(t_shel));
	if (!minishell)
		return (GENERAL_ERROR);
	if (!build_env(&minishell, envp))
		return (GENERAL_ERROR);
	build_rl_prompt(rl_prompt, argv[0]);
    return (mini_loop(&minishell, rl_prompt));
}
