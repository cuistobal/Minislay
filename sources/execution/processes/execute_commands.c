/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:11:29 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/03 11:34:24 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
int	execute_command_in_child(char **command, char **envp)
{
	int	code;

	if (!command || !*command || !env || !*env)
		return (GENERAL_ERROR);
	else if (execve(*command, command, envp) < 0)
	{
		free_array(command, 0);
		free_array(envp, 0);
		exit(GENERAL_ERROR);
	}
	return (SUCCESS);
}

//
pid_t	create_and_execute_child(t_exec *node, int pipefd[][2], int index)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return (-1);
	if (child == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_redirections_in_child(node, pipefd, index);
		execute_command_in_child((node)->command, (node)->environ);
	}
	return (child);
}

//
static pid_t execute_builtin(t_exec *current, int pipefd[][2], int index, t_shell **minishell)
{
	int 	ret;
    pid_t 	pid;

    if (current->next || index > 0)
    {
        pid = fork();
        if (pid < 0)
            return -1;
        if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            setup_redirections_in_child(current, pipefd, index);
            ret = exec_builtin(current->command, current->environ, minishell);
            exit(ret == EXIT_CODE ? 0 : ret);
        }
        redirections_in_parent(current, pipefd, index);
        return pid;
    }
    setup_redirections_in_child(current, pipefd, index);
    ret = exec_builtin(current->command, current->environ, minishell);
    redirections_in_parent(current, pipefd, index);
	return (ret);
}


//
static int	execute_binay(t_exec *current, pid_t pids[], int pipefd[][2], int index)
{
	pids[index] = create_and_execute_child(current, pipefd, index);
	if (pids[index] < 0)
		return (GENERAL_ERROR);
	redirections_in_parent(current, pipefd, index);
	return (SUCCESS);
}

static int	init_exec_arrays(pid_t **pids, int (**pipefd)[2], int count)
{
    *pids = malloc(sizeof(pid_t) * count);
    *pipefd = malloc(sizeof(int[2]) * (count - 1));
    if (!*pids || !*pipefd)
    {
        free(*pids);
        free(*pipefd);
        return (GENERAL_ERROR);
    }
    return (SUCCESS);
}

int	execute_commands(t_shell **minishell, t_exec *node, int count)
{
	int		ret;
    pid_t	*pids;
    int		index;
	int		(*pipefd)[2];
    
	index = 0;
    ret = init_exec_arrays(&pids, &pipefd, count);
    if (ret != SUCCESS)
        return (ret);
    while (node && index < count)
    {
        if ((!node->command || !*node->command) || \
            (node->next && pipe(pipefd[index]) < 0))
            return (GENERAL_ERROR);
        if (!is_builtin(*node->command))
            ret = execute_binay(node, pids, pipefd, index);
        else
            ret = execute_builtin(node, pipefd, index, minishell);
        if (ret == EXIT_CODE)
            return (EXIT_CODE);
        node = node->next;
        index++;
    }
    return (free(pids), free(pipefd), wait_module(pids, index, ret));
}