#include "minislay.h"

//void	mock_execution(char **command, char **env)
void	mock_execution(char **command)
{
//	execve(*command, command + 1, env);
	execve(*command, command + 1, NULL);
}
