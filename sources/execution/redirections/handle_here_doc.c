/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:14:55 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/18 16:18:31 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static char	*expand_line(t_shell *minishell, char *line, bool expansions)
{
	int		index;
	char	*temp;
	char	*value;
	char	*expanded;

	temp = NULL;
	value = NULL;
	expanded = NULL;
	if (line)
	{
		if (!expansions)
			expanded = strdup(line);
		else
		{
			index = 0;
			while (line[index])
			{
				if (!get_expanded(minishell, line, &value, &index))
					return (NULL);
				temp = expanded;
				if (!get_merged(&expanded, &temp, &value))
					return (NULL);
			}
		}
	}
	return (expanded);
}

//
static char	*limiter_handler(char *limiter, bool *expansions)
{
	int		index;
	char	*merged;

	merged = NULL;
	if (limiter)
	{
		index = 0;
		if (!is_quote(*limiter))
			return (ft_strjoin(limiter, "\n"));
		*expansions = false;
		merged = strdup(limiter + 1);
		if (merged)
		{
			while (merged[index])
			{
				if (merged[index] == '"')
					break ;
				index++;
			}
			merged[index] = '\n';
		}
	}
	return (merged);
}

//
static bool	append_heredoc(char *expanded, int fd)
{
	if (expanded)
	{
		if (!write(fd, expanded, strlen(expanded)))
			return false;
	}
	return (write(fd, "\n", 1));
}

//This utility creates a temporary file and fills it with the user's input. If
//the limiter is an unquoted token, lines get expanded.
bool	handle_here_doc(t_shell *minishell, t_tokn **redirections)
{
	int		fd;
	char	*line;
	char	*limiter;
	char	*expanded;
	bool	expansions;

	expanded = NULL;
	expansions = true;
	limiter = limiter_handler((*redirections)->value, &expansions);
	if (limiter)
	{
	//	free((*redirections)->value);
	//	(*redirections)->value = limiter;
		fd = open(HEREDOC, O_APPEND | O_CREAT | O_RDWR, 0644);
		if (fd >= 0)
		{
			(*redirections)->type = fd;
			line = readline(HERE);
			rl_on_new_line();
			while (line)
			{
				if (!strncmp(line, limiter, strlen(line)))
				{
					if (strlen(line) > 0)
						break ;
				}
				expanded = expand_line(minishell, line, expansions);
				append_heredoc(expanded, fd);
				if (expanded)
					free(expanded);
				free(line);
				line = readline(HERE);
				rl_on_new_line();
			}
			return (free(line), close(fd), true);
		}
	}
	return (printf("Unable to open heredoc with %s\n", (*redirections)->value), false);
}

//
void	insert_heredoc_in_list(t_tokn **head, t_tokn **tail, t_tokn *current)
{
	if (!current)
		return ;
	if (!*head)
	{
		*head = current;
		*tail = current->next;
	}
	else
	{
		(*tail)->next = current;
		//*tail = (*tail)->next;
		move_pointer(tail);
		move_pointer(tail);
	}
}
