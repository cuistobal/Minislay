# include <stdio.h>
# include <ctype.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <dirent.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct exec
{
	pid_t		pid;
	int			pipe[2];
	char		**command;
	char		**environ;
	void		(*func)(char **, char **);
	struct exec	*next;
}	t_exec;

void	execution(char **command, char **env)
{
	execve(*command, command + 1, env);
}

/*
t_exec	*create_execution_node(char **command, char **envp)
{
	t_exec	*new;
	int		pipefd[2];

	new = malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	pipe(pipefd);
	new->environ = envp;
	new->pipe[0] = pipefd[0];
	new->pipe[1] = pipefd[1];
	new->command = command;
	new->func = execution;
	new->next = NULL;
	return (new);
}
*/
int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		status;
	pid_t	pids[argc - 1];
	char	**command = NULL;
	t_exec	*new_command = NULL;	
	t_exec	*execution_queue = NULL;
	t_exec	*head = execution_queue;

	if (argc > 1)
	{
		for (i = 1; argv[i]; i++)
		{
			command = malloc(sizeof(char *) * 2);
			command[0] = argv[i];
			command[1] = NULL;
			new_command = create_execution_node(command, envp);
			if (!execution_queue)
			{
				execution_queue = new_command;
				head = new_command;
			}
			else
			{
				execution_queue->next = new_command;
				execution_queue = execution_queue->next;
			}
			new_command = new_command->next;
		}
	}
	for (i = 0; head; i++)
	{
		head->pid = fork();
		if (head->pid > 0)
		{
			pids[i] = head->pid;
			waitpid(pids[i], &status, WEXITED);
			if (WIFEXITED(status))
				printf("exit status for %d = %d\n", i, WEXITSTATUS(status));
		}
		else
			head->func(head->command, head->environ);
		t_exec *current = head;	
		head = head->next;	
		free(current->command);
		free(current);
	}
}
