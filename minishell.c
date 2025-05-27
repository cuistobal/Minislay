/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/27 12:08:44 by chrleroy         ###   ########.fr       */
=======
/*   Updated: 2025/05/24 04:29:21 by ynyamets         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Needs rename -> it's currently the entrey to lexing && parsing
//Has to return an ast for exec // Needs to take an ast pointer as parameter
int	get_minishelled(t_shell **minishell, char *input)
{
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

	traverse_ast(minishell, ast);

	return (free_tree(ast), 0);
}

//
int	start_process(t_shell **minishell, char *terminal_name)
{
    int             retcode;
    char			*user_input;

	init_signals();
    while (1)
    {
        user_input = readline(terminal_name);
<<<<<<< HEAD
        add_history(user_input);
	//	rl_on_new_line();
        retcode = get_minishelled(minishell,user_input);
        free(user_input);
        user_input = NULL;
		//rl_replace_line("", 0);
	//	rl_redisplay();
=======
        if (user_input == NULL)  // Gestion du Ctrl-D
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(0);
		}
		if (g_signal_status == SIGQUIT)
		{
			g_signal_status = 0;
			free(user_input);
			continue; // Ne pas parser une ligne vide suite à SIGQUIT
		}
		if (*user_input)
			add_history(user_input);
		retcode = get_minishelled(minishell, user_input);
		free(user_input);
		user_input = NULL;
>>>>>>> main
    }
	rl_clear_history();
    return (retcode);
}

//
t_env	*build_environement(char **envp)
{
    t_env	*tail;
    t_env	*head;

	head = NULL;
	while (*envp)
	{	
		if (!head)
		{
			head = create_env_node(strdup(*envp));
			if (!head)
				return (NULL);
			tail = head;
		}
		else
		{
			tail->next = create_env_node(strdup(*envp));
			if (!tail->next)
				return (NULL);
			tail = tail->next;
		}
		envp++;
	}
	return (head);	
}

//
bool	build_env(t_shell **minishell, char **envp)
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
	(*minishell)->local = NULL;
	(*minishell)->command = NULL;
	append_specials(minishell);
	return (true);
}

//
int	main(int argc, char **argv, char **envp)
{
	t_shell	*minishell;
    char	*user_input;
	char	rl_prompt[BUFFER_SIZE];

	minishell = (t_shell *)malloc(sizeof(t_shell));
	if (!minishell)
		return (GENERAL_ERROR);
	if (!build_env(&minishell, envp))
		return (GENERAL_ERROR);
	build_rl_prompt(rl_prompt, argv[0]);
    return (start_process(&minishell, rl_prompt));
}
