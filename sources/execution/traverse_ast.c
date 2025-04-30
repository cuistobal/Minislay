/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:39:12 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/30 08:22:03 by cuistobal        ###   ########.fr       */
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
    char    *cmd;
    char    **args;

    cmd = *commands;
    args = commands + 1;

    //  Unknown issue -> ssomew arguments don't work rn, ex -> ls -la

/*
    for (int  i = 0; commands[i]; i++)
        printf("%s\n", commands[i]);

    for (int  i = 0; env[i]; i++)
        printf("%s\n", env[i]);
    exit(execve(*commands, commands + 1 , env));
    */ 
    exit(execve(cmd, args , env));
}

//
void	insert_execution_node(t_exec *head, t_exec *new)
{
    t_exec  *tail;

    tail = NULL;
	if (!head)
		head = new;
	else
	{
        tail = head;
        while (tail)
            tail = tail->next;
		tail = new;
	}
}

//
t_exec  *create_execution_node(char **command, char **env)
{
    t_exec  *new;

    new = malloc(sizeof(t_exec));
    if (!new)
        return (NULL);
    new->pid = -1;
    new->pipe[0] = -1;
    new->pipe[1] = -1;
    new->command = command;
    new->environ = env;
    new->next = NULL;
    return (new);
}

//
static bool	join_env(char **joined, char *temp[2])
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
void	create_child_process(t_shel	*minishell, t_exec *list)
{
    pid_t   pid;
	int     status;

	if (!minishell || !list)
		return ;
	pid = fork();
	if (pid == 0)
		execute_command(list->command, list->environ);
	else
	{
       // list->pid = pid;
//		waitpid(list->pid, &status, 0);
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

//
static bool	get_command_and_env(t_shel **minishell, t_tree *ast, t_exec *exec)
{
	int		size;
    t_exec  *new;
    char    **command;
    char    **environ;

    command = NULL;
    environ = NULL;
	if (!minishell || !ast)
		return (false);
	size = 1;
	environ = rebuild_env(*minishell, &size);
	if (!environ)
		return (error_message(INV_ENV));
	command = prepare_for_exec(minishell, ast);
	if (!command)
	    return (free_array(environ, size), error_message(INV_COMMAND));
    new = create_execution_node(command, environ);
    if (!new)
        return (false);

    insert_execution_node(exec, new);

//	create_child_process(*minishell, new);

	return (true);
}

/*
static void	execute(t_exec **execution)
{
	t_exec	*current;

	current = NULL;
	printf("%s\n", *(*execution)->command);	
	while (*execution)
	{
		current = *execution;
		(*execution)->pid = fork();
		if ((*execution)->pid < 0)
		{
			error_message(FORK_FAILED);
			return ;
		}
		else if (current->pid == 0)
			execute_command((*execution)->command, (*execution)->environ);
		*execution = (*execution)->next;
	//	free_exec_node(current);
	}
}
*/

//Main travsersal function of the AST
//
//We need to implement the Operators logic.
void	traverse_ast(t_shel **minishell, t_tree *ast, t_exec **list)
{
	if (ast)
	{
		traverse_ast(minishell, ast->left, list);
		if (ast->tokens && !is_amp_pipe(*ast->tokens->value))
		{
			if (ast->tokens->type & OPAR)
				handle_subshell(*minishell, ast);
			else
			{
				if (!get_command_and_env(minishell, ast, *list))
					return ;

	          //  create_child_process(*minishell, *list);

			//	insert_execution_token(queue, new);
		/*
				command = prepare_for_exec(minishell, ast);	
				if (!command)
					return (error_message("Command alloc failed.\n"));
				env = rebuild_env(*minishell, &size);
				if (!env)
					return (free_array(env, size), error_message("env alloc failed.\n"));


				if (!is_builtin(*command))
					create_child_process(*minishell, command, env);
		*/
				/*
				else
					execute_builtin(command, env);
			//	*/
			}
		}
		traverse_ast(minishell, ast->right, list);
		/*
		if (!is_state_active(ast->tokens->type, PIPE))
			execute(head);	
		*/
	}
}
