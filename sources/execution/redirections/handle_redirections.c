/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:33:52 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/18 16:39:08 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Function to open an output file in append mode
bool open_outfile_append(t_tokn **redirections)
{
	int	fd;

	if (*redirections)
	{
        move_pointer(redirections);
		if (*redirections)
		{
			if (!(*redirections)->next || is_state_active((*redirections)->next->type, WORD))			
			{
				fd = open((*redirections)->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
				if (fd == -1)
					return (printf("Unable to open %s\n", (*redirections)->value), false);
				(*redirections)->type = fd; 
				if ((*redirections)->next)
					close((*redirections)->type);
        		return (move_pointer(redirections));
			}
			//Error message -> Ambiguous syntax
			printf("Ambiguous syntax\n");
			return (false);	
		}
	}
    return (!*redirections);
}

// Function to open a here-document
bool open_here_doc(t_shell *minishell, t_tokn **redirections)
{
	if (*redirections)
	{
        move_pointer(redirections);
		if (*redirections)
		{
			if (!(*redirections)->next || is_state_active((*redirections)->next->type, WORD))			
				return (handle_here_doc(minishell, redirections));
				/*
				fd = open((*redirections)->value, O_APPEND | O_CREAT | O_RDWR, 0644);
				if (fd == -1)
				{
					printf("Unable to open %s\n", (*redirections)->value);
					return (false);
				}
				(*redirections)->type = fd; 
        		return (move_pointer(redirections));
				*/
			//Error message -> Ambiguous syntax
			printf("Ambiguous syntax\n");
			return (false);	
		}
	}
    return (!*redirections);
}

// Function to open an output file in overwrite mode
bool open_outfile(t_tokn **redirections)
{
	int	fd;

	if (*redirections)
	{
        move_pointer(redirections);
		if (*redirections)
		{
			if (!(*redirections)->next || is_state_active((*redirections)->next->type, WORD))			
			{
				fd = open((*redirections)->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1)
					return (printf("Unable to open %s\n", (*redirections)->value), false);
				(*redirections)->type = fd; 
				if ((*redirections)->next)
					close((*redirections)->type);
        		return (move_pointer(redirections));
			}
			//Error message -> Ambiguous syntax
			printf("Ambiguous syntax\n");
			return (false);	
		}
	}
    return (!*redirections);
}

/*
// Function to open an input file
static bool open_infile(t_tokn **redirections)
{
	int	fd;

	if (*redirections)
	{
        move_pointer(redirections);
		if (*redirections)
		{
			if (!(*redirections)->next || is_state_active((*redirections)->next->type, WORD))			
			{
				fd = open((*redirections)->value, O_RDONLY);
				if (fd == -1)
					return (printf("Unable to open %s\n", (*redirections)->value), false);
				(*redirections)->type = fd; 
				if ((*redirections)->next)
					close((*redirections)->type);
        		return (move_pointer(redirections));
			}
			//Error message -> Ambiguous syntax
			printf("Ambiguous syntax\n");
			return (false);	
		}
	}
    return (!*redirections);
}
*/

// Function to open an input file
bool open_infile(t_tokn **redirections)
{
	int	fd;

	if (!*redirections)
		return (false);
	move_pointer(redirections);
	if (!*redirections)
		return (printf("Ambiguous syntax\n"), false);

	if (!(*redirections)->next || is_state_active((*redirections)->next->type, WORD))			
	{
		fd = open((*redirections)->value, O_RDONLY);
		if (fd == -1)
			return (printf("Unable to open %s\n", (*redirections)->value), false);
		(*redirections)->type = fd; 
		if ((*redirections)->next)
			close((*redirections)->type);
		return (move_pointer(redirections));
	}

    return (!*redirections);
}

/*
 * TEST
static void	open_file(t_tokn **redirections)
{
	while (*redirections)
	{
		move_pointer(redirections);
		(*redirections)->type = open((*redirections)->value, O_CREAT | O_RDWR, 0644);
		if ((*redirections)->type < 0)
			printf("Failed to open %s\n", (*redirections)->value);
		if ((*redirections)->next)
		{
			printf("%s\n", (*redirections)->value);
			close((*redirections)->type);
			unlink((*redirections)->value);
		}
		move_pointer(redirections);	
	}
}
*/

// Function to handle redirections
bool	handle_redirection_list(t_shell *minishell, t_tokn **list)
{
	t_tokn	*redirections;

	redirections = *list;
   	while (redirections)
   	{
	//	open_file(&redirections);
		///*
       	if (!valid_lexeme(redirections, IRED, ARED))
			return (printf("Error: Unexpected token %s\n", redirections->value), false);
		if (redirections->type == IRED)
			open_infile(&redirections);
		else if (redirections->type == ORED)
			open_outfile(&redirections);
		else if (redirections->type == ARED)
			open_outfile_append(&redirections);
		else if (redirections->type == HDOC)
			open_here_doc(minishell, &redirections);
       	move_pointer(&redirections);
		//*/
   	}
    return (true);
}
