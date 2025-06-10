/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:08:35 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/10 08:48:06 by chrleroy         ###   ########.fr       */
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
		return (printf(PARSING), free_tokens(tokens), free_tree(ast), \
                free(parser), GENERAL_ERROR);
	free(parser);
    (*minishell)->ast = ast;
	ret = traverse_ast(minishell, ast);	
    append_exit_code(*minishell, ret, false);
	free_tree(ast);
	return (ret);
}

/*
int start_process(t_shell **minishell, char *terminal_name)
{
    int             retcode;
    char            *user_input;
    struct termios  term;
    struct termios  old_term;

    init_signals();
    tcgetattr(STDIN_FILENO, &old_term);
    while (1)
    {
        // Configuration pour readline et heredoc
        tcgetattr(STDIN_FILENO, &term);
        // Ajout de ICANON pour heredoc
        term.c_lflag |= (ECHO | ICANON);  
        term.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

        user_input = readline(terminal_name);
        if (!user_input)
        {
            write(STDOUT_FILENO, "exit\n", 5);
            tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
            exit(0);
        }
        if (g_signal_status == SIGQUIT)
        {
            g_signal_status = 0;
            free(user_input);
            continue ;
        }
        if (*user_input)
        {
            add_history(user_input);
            retcode = get_minishelled(minishell, user_input);
            // Restauration des attributs du terminal après l'exécution
            tcgetattr(STDIN_FILENO, &term);
            term.c_lflag |= (ECHO | ICANON);
            term.c_lflag &= ~ECHOCTL;
            tcsetattr(STDIN_FILENO, TCSANOW, &term); 
            // Attente des processus
            while (wait(NULL) > 0)
                continue;
            
            free(user_input);
            if (retcode == EXIT_CODE)
                break;
            append_exit_code(*minishell, retcode, false);
        }
        rl_on_new_line();
        rl_replace_line("", 0);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    rl_clear_history();
    return (retcode);
}*/

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
