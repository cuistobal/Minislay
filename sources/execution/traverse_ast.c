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

static bool	join_env(char **joined, char *temp[3])
{
	*joined = ft_strjoin(temp[0], temp[1]);
	if (!*joined)
		return (false);
	*joined = ft_strjoin(*joined, temp[2]);
	if (!*joined)
		return (false);
	return (true);
}

char	**rebuild_env(t_shel *minishell, int *size)
{
	int		index;
	char	**env;
	char	*temp[3];

	index = 0;
	temp[0] = NULL;	
	temp[1] = "=";	
	temp[2] = NULL;	
	env = (char **)malloc(sizeof(char *) * *size);
	if (!env)
		return (NULL);
	while (minishell->envp)
	{
		if (index == *size - 1)
		{
			*size = *size << 1;
			env = (char **)realloc(env, sizeof(char *) * *size);
			if (!env)
				return (NULL);
		}
		temp[0] = minishell->envp->var[0];
		temp[2] = minishell->envp->var[1];
		if (!join_env(&env[index], temp))
		{
			free_array(env, *size);
			return (NULL);
		}
		index++;
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

	size = 50;
	env = NULL;
	command = NULL;
	if (ast)
	{
		traverse_ast(minishell, ast->left);
		if (ast->tokens)
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
				execute_command(command, env);
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
