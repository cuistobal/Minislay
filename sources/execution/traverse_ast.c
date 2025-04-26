/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/26 13:13:12 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
static const char *g_b[BCNT] = {BCDD, BPWD, BENV, BECO, BEXT, BUST, BEXP};
static const void (*g_f[BCNT])(void) = {cd, echo, env, my_export, my_exit, pwd, unset};
*/
//
void	execute_command(char **commands, char **env)
{
	char	*command;
	char	**arguments;

	command = *commands;
	arguments = commands + 1;
	exit(execve(command, arguments, env));
}

/*
//
void	execute_builtin(t_shel *minishell, char **command, char **env)
{
	int	index;

	if (!minishell || (!command || !*command) || (!env || !*env))
		return ;
	index = 0;
	while (index < X)
	{
		if (strcmp(*command, g_b[index]) == 0)
			g_f[index];
	}

}
*/
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

	if (!minishell)
		return ;
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

t_exec	*create_execution_node(char **command, char **envp)
{
	t_exec	*new;
	int		pipefd[2];

	new = malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	if (pipe(pipefd) < 0)
		return (free(new), error_message(PIPE_FAILED), NULL);
	new->environ = envp;
	new->pipe[0] = pipefd[0];
	new->pipe[1] = pipefd[1];
	new->command = command;
	new->func = NULL;
	new->next = NULL;
	return (new);
}

static bool	get_command_and_env(t_shel **minishell, t_tree *ast, t_exec *exec)
{
	int		size;
	char	**env;
	char	**command;

	if (!minishell || !ast)
		return (false);
	size = 1;
	env = NULL;
	command = NULL;
	command = prepare_for_exec(minishell, ast);	
	if (!command)
		return (error_message(INV_COMMAND));
	env = rebuild_env(*minishell, &size);
	if (!env)
		return (free_array(env, size), error_message(INV_ENV));
	if (exec)
		exec->next = create_execution_node(command, env);	
	else
		exec = create_execution_node(command, env);	
	return (true);
}

//Main travsersal function of the AST
//
//We need to implement the Operators logic.
void	traverse_ast(t_shel **minishell, t_tree *ast, t_exec *execution)
{
//	t_exec	*head;
//
//	head = execution;
	if (ast)
	{
		if (is_state_active(ast->tokens->type, PIPE))
			printf("%s\n", ast->tokens->value);
		traverse_ast(minishell, ast->left, execution);
		if (ast->tokens && !is_amp_pipe(*ast->tokens->value))
		{
			if (ast->tokens->type & OPAR)
				handle_subshell(*minishell, ast);
			else
			{
			// Need to append the error_code
				if (!get_command_and_env(minishell, ast, execution))
					return ;
				/*
				if (!is_state_active(ast->tokens->type, PIPE))
				{
					print_tokens(ast->tokens);
					printf("No pipe\n");
				}
				else
				{
					print_tokens(ast->tokens);
					printf("Pipe\n");
				}
				*/
			// Need to implement the actual execution logic
				/*
				if (!is_builtin(*command))
					create_child_process(*minishell, command, env);
				else
					execute_builtin(command, env);
			//	*/
			}
		}
		traverse_ast(minishell, ast->right, execution);
	}
}
