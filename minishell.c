/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 17:43:41 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Needs rename -> it's currently the entrey to lexing && parsing
//Has to return an ast for exec // Needs to take an ast pointer as parameter
int	get_minishelled(t_shel *minishell, char *input)
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
    t_env	*head;
	t_avlt	*root;

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
	
	return (true);
}


//
int	main(int argc, char **argv, char **envp)
{
	t_shel			*minishell;
	struct termios	tty_status;
    char			*user_input;
	char			rl_prompt[BUFFER_SIZE];

	minishell = (t_shel *)malloc(sizeof(t_shel));
	if (!minishell)
		return 1;
	if (!build_env(&minishell, envp))
		return 1;
	build_rl_prompt(rl_prompt, argv[0]);
    while (1)
	{
        user_input = readline(rl_prompt);
        if (user_input)
        {
			tcgetattr(STDIN_FILENO, &tty_status);
            add_history(user_input);	
			get_minishelled(minishell,user_input);
            free(user_input);
			tcsetattr(STDIN_FILENO, TCSANOW, &tty_status);
        }
    }
	return 0;
}
