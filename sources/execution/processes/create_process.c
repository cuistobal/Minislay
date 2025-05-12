/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:16:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/12 19:07:17 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*bool	create_child_process(t_shel	*minishell, char **command, char **env)
{
	pid_t	pid;
	int 	status;
	int		pipefd[2];
	printf("test :\n");

	if (command)
	{
		int i = 0;
		printf("Contenu de command :\n");
		while (command[i])
		{
			printf("command[%d] = %s\n", i, command[i]);
			i++;
		}
	}


	if (pipe(pipefd) != 0)
		return (error_message(PIPE_FAILED));
	pid = fork();
	if (pid < 0)
		return (error_message(FORK_FAILED));
	else if (pid == 0)
		execute_command(command, env);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			printf("%d\n", WEXITSTATUS(status));
	}
}
*/
void	create_child_process(t_shel *minishell, char **command, char **env)
{
	pid_t	pid;
	int		status;
	char	*temp;

	pid = fork();
	if (pid < 0)
	{
		error_message(FORK_FAILED);
		return ;
	}
	if (pid == 0)
	{
		if (is_builtin(command[0]))
			exit(exec_builtin(command, minishell));
		else
			execute_command(command, env);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			temp = minishell->special[DEXTI];
			minishell->special[DEXTI] = ft_itoa(WEXITSTATUS(status));
			free(temp);
		}
	}
}


