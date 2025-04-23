#include "minislay.h"

//void	create_process()

int	execute_command(char **command, char **env)
{
	if (!execve(*command, command + 1, env))
		exit(-1);
}

char	**rebuild_env(t_shel *minishell)
{
	int		index;
	char	**env;
	char	*temp[3];

	index = 0;
	temp[0] = NULL;	
	temp[1] = "=";	
	temp[2] = NULL;	
	env = (char **)malloc(sizeof(char *) * 50);
	if (!env)
		return (NULL);
	while (minishell->envp)
	{
		temp[0] = minishell->envp->var[0];
		temp[2] = minishell->envp->var[1];
		env[index] = join_env();		
		index++;
	}	
}

//Main travsersal function of the AST
//
//We need to implement the Operators logic.
void	traverse_ast(t_shel **minishell, t_tree *ast)
{
	char	**env;
	char	**command;

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
				env = rebuild_env(*minishell);
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
