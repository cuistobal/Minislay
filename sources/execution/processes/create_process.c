#include "minislay.h"

pid_t	create_process(t_shel **minishell, char **command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		//Error message. Fork failed.
		return -1;
	else if (pid == 0)
	{

	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
