#include "minislay.h"

//void	create_process()

//
void	execute_command(char **commands, char **env)
{
	char	*command;
	char	**arguments;

	command = *commands;
	arguments = commands + 1;
	exit(execve(command, arguments, env));
}

//
void	execute_builtin(char **command, char **env)
{
			
}

//
static bool	join_env(char **joined, char *temp[3])
{
	char	*merged;

	merged = ft_strjoin(strdup(temp[0]), strdup("\""));
	if (!merged)
		return (free(merged), merged = NULL, false);
	merged = ft_strjoin(merged, strdup(temp[1]));
	if (!merged)
		return (free(merged), merged = NULL,false);
	return (*joined = merged, true);
}

//
void	create_child_process(t_shel	*minishell, char **command, char **env)
{
	int status;

	pid_t pid = fork();
	if (pid == 0)
		execute_command(command, env);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			printf("%d\n", WEXITSTATUS(status));
	}
}

// Had to declare a current pointer bc the original minishel pointer is moved
// for some reason.
static char	**rebuild_env(t_shel *minishell, int *size)
{
	int		index;
	char	**env;
	char	*temp[2];
	t_env	*current;

	index = 0;
	current = minishell->envp;	
	env = (char **)malloc(sizeof(char *) * *size);
	if (!env)
		return (NULL);
	reset_array(env, 0, *size);	
	while (current)
	{
		reset_array(temp, 0, 2);
		if (index == *size - 1)
			env = (char **)resize_array(env, sizeof(char *), size);
		if (!env)
			return (NULL);
		temp[0] = current->var[0];
		temp[1] = current->var[1];
		if (!join_env(&env[index++], temp))
			return (free_array(env, *size), NULL);
		current = current->next;
	}
	return (env);
}

//Main travsersal function of the AST
//
//We need to implement the Operators logic.
bool	traverse_ast(t_shel **minishell, t_tree *ast)
{
	int		size;
	char	**env;
	char	**command;

	size = 1;
	env = NULL;
	command = NULL;
	if (ast)
	{
		traverse_ast(minishell, ast->left);
		if (ast->tokens && !is_amp_pipe(*ast->tokens->value))
		{
			if (ast->tokens->type & OPAR)
				handle_subshell(*minishell, ast);
			else
			{
				command = prepare_for_exec(minishell, ast);	
				if (!command)
					return (error_message("Command alloc failed.\n"));
				env = rebuild_env(*minishell, &size);
				if (!env)
					return (free_array(env, size), error_message("env alloc failed.\n"));
				if (!is_builtin(*command))
					create_child_process(*minishell, command, env);
				else
					execute_builtin(command, env);
			}
		}
		traverse_ast(minishell, ast->right);
	}
	return (!ast);
}
