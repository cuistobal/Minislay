/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_process_communications.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:31:39 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/07 12:16:41 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
int	my_dup(int source)
{
	int	newfd;

	newfd = dup(source);
	if (newfd < 0)
		error_message(DUP_FAILED);
	return (newfd);
}

//
int	my_dup2(int oldfd, int newfd)
{
	int	ret;

	ret = dup2(oldfd, newfd);
	if (ret < 0)
	{
		error_message(DUP_FAILED);
		return (GENERAL_ERROR);
	}
	return (SUCCESS);
}

//
void	get_or_restore_stds(int fds[2], bool set)
{
	if (set)
	{
		fds[0] = dup(STDIN_FILENO);
		fds[1] = dup(STDOUT_FILENO);
	}
	else
	{
	//	dup2(fds[0], STDIN_FILENO);
		dup2(STDIN_FILENO, fds[0]);
		close(fds[0]);
	//	dup2(fds[1], STDOUT_FILENO);
		dup2(STDOUT_FILENO, fds[1]);
		close(fds[1]);
	}
}

/*
void	redirections_in_parent(t_exec *node, int pipe[][2], int index)
{
	if (!node->next)
		return ;
	close(pipe[index][1]);
    if (node->redirs[INFILE] >= 0)
        close(node->redirs[INFILE]);
    if (node->redirs[OUTFILE] >= 0)
        close(node->redirs[OUTFILE]);
}
*/

void	redirections_in_parent(t_exec *node, int pipe[][2], int index)
{
    if (!node->next)
        return;
    
    // Fermeture du pipe courant
    close(pipe[index][WRITE_END]);
    if (index > 0)
        close(pipe[index - 1][READ_END]);

    // Fermeture des redirections
    if (node->redirs[INFILE] >= 0)
        close(node->redirs[INFILE]);
    if (node->redirs[OUTFILE] >= 0)
        close(node->redirs[OUTFILE]);
}

static int stdin_management(t_exec *node, int pipefd[][2], int index)
{
    int old;
    int infile;

    infile = node->redirs[INFILE];
    if (infile != -1)
    {
        if (my_dup2(infile, STDIN_FILENO) != SUCCESS)
            return (GENERAL_ERROR);
        close(infile);
    }
    else if (index > 0)
    {
        old = pipefd[index - 1][READ_END];
        if (my_dup2(pipefd[index - 1][READ_END], STDIN_FILENO) != SUCCESS)
            return (GENERAL_ERROR);
        close(old);
    }
	return (SUCCESS);
}

static int stdout_management(t_exec *node, int pipefd[][2], int index)
{
    int old;
    int outfile;

    outfile = node->redirs[OUTFILE];
	if (outfile != -1)
	{
		if (my_dup2(outfile, STDOUT_FILENO) != SUCCESS)
			return (GENERAL_ERROR);
		close(outfile);
	}
	else if (node->next)
	{
        old = pipefd[index][WRITE_END];
		if (my_dup2(pipefd[index][WRITE_END], STDOUT_FILENO) != SUCCESS)
			return (GENERAL_ERROR);
        close(old);
	}
	return (SUCCESS);
}

static int close_unused_pipes(t_exec *node, int pipefd[][2], int index)
{
	if (index > 0)
	{
		close(pipefd[index - 1][READ_END]);
		close(pipefd[index - 1][WRITE_END]);
	}
	if (node->next)
	{
		close(pipefd[index][READ_END]);
		close(pipefd[index][WRITE_END]);
	}
	return (SUCCESS);
}

int	setup_redirections_in_child(t_exec *node, int pipefd[][2], int index)
{

    int ret;

	ret = stdin_management(node, pipefd, index);
	if (ret != SUCCESS)
		return (ret);
	ret = stdout_management(node, pipefd, index);
	if (ret != SUCCESS)
		return (ret);
	ret = close_unused_pipes(node, pipefd, index);
	if (ret != SUCCESS)
		return (ret);
	// Gestion de l'entrée
	/*
	if (infile != -1)
	{
		if (my_dup2(infile, STDIN_FILENO) != SUCCESS)
			return (GENERAL_ERROR);
		close(infile);
	}
	else if (index > 0)
	{
		if (my_dup2(pipefd[index - 1][READ_END], STDIN_FILENO) != SUCCESS)
			return (GENERAL_ERROR);
	}
	*/
	/*
    // Gestion de l'entrée
    if (infile != -1)
    {
        if (my_dup2(infile, STDIN_FILENO) != SUCCESS)
            return (GENERAL_ERROR);
        close(infile);
    }
    else if (index > 0)
    {
        if (my_dup2(pipefd[index - 1][READ_END], STDIN_FILENO) != SUCCESS)
            return (GENERAL_ERROR);
    }
*/
    // Gestion de la sortie
    // if (outfile != -1)
    // {
    //     if (my_dup2(outfile, STDOUT_FILENO) != SUCCESS)
    //         return (GENERAL_ERROR);
    //     close(outfile);
    // }
    // else if (node->next)
    // {
    //     if (my_dup2(pipefd[index][WRITE_END], STDOUT_FILENO) != SUCCESS)
    //         return (GENERAL_ERROR);
    // }

    // Fermeture des pipes inutiles
    // if (index > 0)
    // {
    //     close(pipefd[index - 1][READ_END]);
    //     close(pipefd[index - 1][WRITE_END]);
    // }
    // if (node->next)
    // {
    //     close(pipefd[index][READ_END]);
    //     close(pipefd[index][WRITE_END]);
    // }
    return (SUCCESS);
}

/*
//Integrer la gestion d'erreur piur les dup()
int	setup_redirections_in_child(t_exec *node, int pipefd[][2], int index)
{
    int infile;
	int outfile;

	infile = node->redirs[INFILE];
	outfile = node->redirs[OUTFILE];
    if (infile != -1)
    {
        dup2(infile, STDIN_FILENO);
        close(infile);
    }
	else if (index > 0)
    {
        dup2(pipefd[index - 1][READ_END], STDIN_FILENO);
        close(pipefd[index - 1][READ_END]);
    }
    if (outfile != -1)
    {
        dup2(outfile, STDOUT_FILENO);
        close(outfile);
    }
    else if (node->next)
    {
        dup2(pipefd[index][WRITE_END], STDOUT_FILENO);
        close(pipefd[index][WRITE_END]);
    }
}
	*/
