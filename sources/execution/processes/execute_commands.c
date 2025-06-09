/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:11:29 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/09 13:40:10 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static void child_cleanup(t_shell **minishell, int cmd)
{
    int index;

    index = 0;
    free_execution_node((*minishell)->execution);
    free_tree((*minishell)->ast);
    while (index < cmd + 1)
    {
        close((*minishell)->pipefd[index][READ_END]);
        close((*minishell)->pipefd[index][WRITE_END]);
        index++;
    }
    free((*minishell)->pipefd);
    free((*minishell)->pids);
    close((*minishell)->original_stds[0]);
    close((*minishell)->original_stds[1]);
    free_minishell(*minishell);
}


// This function sets up the redirections in the child process.
// It handles input and output redirections based on the node's redirs array.
int	execute_command_in_child(t_shell **minishell, char **command, char **envp, int cmd)
{
	int	code;

	if (!command || !*command || !env || !*env)
    {
        child_cleanup(minishell, cmd);
        exit(COMMAND_EXEC);
    }
	else if (execve(*command, command, envp) < 0)
	{
        child_cleanup(minishell, cmd);
		exit(COMMAND_EXEC);
	}
	return (SUCCESS);
}

//Creates a child process to execute the command.
//It sets up the necessary redirections and executes the command in the child process.
//If the fork fails, it returns -1.
//If the child process is created successfully, it sets up the signal handlers to default,
//sets up the redirections in the child process, and executes the command using execve.
//The function returns the child's PID on success, or -1 on failure.
// It is used to create a new process for executing commands in the shell.
// The child process will handle the command execution, while the parent process will manage
// the redirections and wait for the child to finish.
// It is a crucial part of the shell's execution model, allowing for concurrent command execution.
// It is used to create a new process for executing commands in the shell.
pid_t	create_and_execute_child(t_shell **minishell, t_exec *node, int pipefd[][2], int index)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return (-1);
	if (child == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		setup_redirections_in_child(node, pipefd, index);
		execute_command_in_child(minishell, (node)->command, (node)->environ, index);
	}
	return (child);
}

// static void setup_redirections_for_builtin(t_exec *node, int original[2], bool set)
// {
//     if (set)
//     {
//         original[INFILE] = dup(STDIN_FILENO);
//         original[OUTFILE] = dup(STDOUT_FILENO);
//         if (node->redirs[INFILE] != -1)
//             dup2(STDIN_FILENO, node->redirs[INFILE]);
//         if (node->redirs[OUTFILE] != -1)
//             dup2(STDOUT_FILENO, node->redirs[OUTFILE]);
//     }
//     else
//     { 
//         if (original[INFILE] != STDIN_FILENO)
//             dup2(STDIN_FILENO, original[INFILE]);
//         if (original[INFILE] != STDOUT_FILENO)
//             dup2(STDOUT_FILENO, original[OUTFILE]);
//         close(original[INFILE]);
//         close(original[OUTFILE]);
//     }
// }

//Cette fonction gère les redirections dans le processus enfant pour les builtins.
//Si set == true, elle duplique les descripteurs de fichiers d'entrée et de sortie
//et les redirige vers les fichiers spécifiés dans node->redirs.
//Si set == false, elle restaure les descripteurs de fichiers d'entrée et de sortie
//aux valeurs d'origine et ferme les descripteurs de fichiers redirigés.
// Elle est utilisée pour les builtins qui nécessitent des redirections, comme 'cd' ou 'export'.
static void setup_redirections_for_builtin(t_exec *node, int original[2], bool set)
{
    if (set)
    {
        original[INFILE] = dup(STDIN_FILENO);
        original[OUTFILE] = dup(STDOUT_FILENO);
        if (node->redirs[INFILE] != -1)
            dup2(node->redirs[INFILE], STDIN_FILENO);
        if (node->redirs[OUTFILE] != -1)
            dup2(node->redirs[OUTFILE], STDOUT_FILENO);
    }
    else
    {
        if (original[INFILE] != STDIN_FILENO)
            dup2(original[INFILE], STDIN_FILENO);
        if (original[INFILE] != STDOUT_FILENO)
            dup2(original[OUTFILE], STDOUT_FILENO);
        close(original[INFILE]);
        close(original[OUTFILE]);
    }
}

//
static pid_t execute_builtin(t_exec *current, int pipefd[][2], int index, t_shell **minishell)
{
	int 	ret;
    pid_t 	pid;
    int     original[2];

    if (current->next || index > 0)
    {
        pid = fork();
        if (pid < 0)
            return -1;
        if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            setup_redirections_in_child(current, pipefd, index);
            ret = exec_builtin(current->command, current->environ, minishell);
            child_cleanup(minishell, index);
            exit(ret);
        }
        return (redirections_in_parent(current, pipefd, index), pid);
    } 
    setup_redirections_for_builtin(current, original, true);
    ret = exec_builtin(current->command, current->environ, minishell);
    return (setup_redirections_for_builtin(current, original, false), ret);
}


//
static pid_t    execute_binay(t_shell **minishell, t_exec *current, int pipefd[][2], int index)
{
    pid_t   pid;

	pid = create_and_execute_child(minishell, current, pipefd, index);
	if (pid < 0)
		return (GENERAL_ERROR);
	redirections_in_parent(current, pipefd, index);
	return (pid);
}

static void close_pipes(int (*pipefd)[2], int count)
{
    int index;

    index = 0;
    while (index < count - 1)
    {
        close(pipefd[index][READ_END]);
        close(pipefd[index][WRITE_END]);
        index++; 
    }
}

//
int	execute_commands(t_shell **minishell, t_exec *node, int count)
{
	int		ret;
    int		index;
    
	index = 0;
    if (count <= 0)
        return (SUCCESS);
    (*minishell)->pids = malloc(sizeof(pid_t) * count);
    (*minishell)->pipefd = malloc(sizeof(int[2]) * (count - 1));
    if (!(*minishell)->pids || !(*minishell)->pipefd)
    	return (free((*minishell)->pids), free((*minishell)->pipefd), GENERAL_ERROR);
    while (node && index < count)
    {
        if ((!node->command || !*node->command) || \
            (node->next && pipe((*minishell)->pipefd[index]) < 0))
            return (free((*minishell)->pids), close_pipes((*minishell)->pipefd, index), \
                    free((*minishell)->pipefd), COMMAND_NOT_FOUND);
        if (!is_builtin(*node->command))
            ret = execute_binay(minishell, node, (*minishell)->pipefd, index);
        else
            ret = execute_builtin(node, (*minishell)->pipefd, index, minishell);
        node = node->next;
        index++;
    }
    return (free((*minishell)->pids), close_pipes((*minishell)->pipefd, count), \
            free((*minishell)->pipefd), wait_module((*minishell)->pids, index, ret));
}
