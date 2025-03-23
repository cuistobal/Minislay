#include "minislay.h"

bool	wait_for_child(pid_t pid, int *status)
{
	waitpid()
}

void	create_process()
{
	pid_t	pid;
	int 	status;

	pid = fork();
	if (pid < 0)
		//error message -> fork failed
		return ;
	else
	{
		if (pid == 0)
		{
			child
		}
		else
		{
			wait_for_child(pid, status);
			parent
		}
	}
}
