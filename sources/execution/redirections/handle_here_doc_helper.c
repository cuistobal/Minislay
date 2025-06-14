/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:05:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 16:06:59 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
bool	rewind_heredoc(t_tokn *redirections)
{
	if (access(redirections->value, F_OK) != 0)
		return (false);
	close(redirections->type);
	redirections->type = open(redirections->value, O_RDONLY);
	return (redirections->type != -1);
}

//
char	*limiter_handler(char *limiter, bool *expansions)
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
bool	init_heredoc(t_tokn *redirections, bool *expansions, char **limiter, \
		int *len)
{
	int		fd;
	char	*heredocname;

	if (!redirections)
		return (NULL);
	*limiter = limiter_handler(redirections->value, expansions);
	if (!*limiter)
		return (false);
	*len = strlen(*limiter);
	heredocname = ft_strjoin(HEREDOC_PREFIX, redirections->value);
	if (!heredocname)
		return (free(*limiter), *limiter = NULL, false);
	free(redirections->value);
	redirections->value = heredocname;
	fd = open(heredocname, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd < 0)
		return (free(*limiter), *limiter = NULL, false);
	redirections->type = fd;
	return (true);
}
