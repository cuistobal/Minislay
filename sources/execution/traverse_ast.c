#include "minislay.h"

//void	create_process()

void	execute_command(char **command, char **env)
{
	
	exit(execve(*command, command + 1, env));
//	if (execve(*command, command + 1, env) == -1)
//		printf("exec failed\n");
//	if (execve(*command, command + 1, env))
//		exit(-1);
}

//
static bool	join_env(char **joined, char *temp[3])
{
	char	*merged;

	merged = ft_strjoin(strdup(temp[0]), strdup(temp[1]));
	if (!merged)
		return (free(merged), merged = NULL,false);
	merged = ft_strjoin(merged, strdup(temp[2]));
	if (!merged)
		return (free(merged), merged = NULL,false);
	return (*joined = merged, true);
}

//
static void	*resize_array(void *array, int array_type, int *size)
{
	int		len;
	void	*new;

	len = *size;
	*size = *size << 1;
	new = realloc(array, array_type * *size);
	if (!new)
		return (NULL);
	memset(new, 0, (array_type *len));
	return (new);
}

static void	reset_array(char **array, int start, int end)
{
	int	reset;

	reset = 0;
	if (!array)
		return ;
	while (reset < end - start )
		array[start + reset++] = NULL;
}
//
static char	**rebuild_env(t_shel *minishell, int *size)
{
	int		index;
	char	**env;
	char	*temp[3];

	index = 0;
	env = (char **)malloc(sizeof(char *) * *size);
	if (!env)
		return (NULL);
	reset_array(env, 0, *size);	
	while (minishell->envp)
	{
		reset_array(temp, 0, 3);
		temp[1] = "=";
		if (index == *size - 1)
			env = (char **)resize_array(env, sizeof(char *), size);
		if (!env)
			return (NULL);
		temp[0] = minishell->envp->var[0];
		temp[2] = minishell->envp->var[1];
		if (!join_env(&env[index++], temp))
			return (free_array(env, *size), NULL);
		minishell->envp = minishell->envp->next;
	}
	return (env);
}

//Main travsersal function of the AST
//
//We need to implement the Operators logic.
void	traverse_ast(t_shel **minishell, t_tree *ast)
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
			//	prepare_for_exec(minishell, ast);	
				command = prepare_for_exec(minishell, ast);	
				if (!command)
				{
					printf("command is NULL\n");
					return ;
				}
		//Turn into a bool to check alloc failure (?)	
				env = rebuild_env(*minishell, &size);
				
				if (!env)
					free_array(env, size);
		//end	
		
				int status;

				pid_t pid = fork();
				if (pid == 0)
					execute_command(command, env);
				else
				{
					waitpid(pid, &status, WIFEXITED(status));
					printf("%d\n", WEXITSTATUS(status));
				}
	
				//	Append error code && return
				/*
				{
					for (int  i = 0; command[i]; i++)
						printf("%s ", command[i]);
					printf("\n");
				}
				*/
//				create_process();	
//				execute(command);	
			//	print_tokens(ast->tokens);
			}
		}
		traverse_ast(minishell, ast->right);
	}
}
