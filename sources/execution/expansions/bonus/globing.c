/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:12:01 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/10 14:52:32 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
** Creates a new token node for globbing result
** - Duplicates filename and creates new token
** - Returns false if memory allocation fails
*/
static bool	add_to_expanded_list(t_tokn **expanded, char *filename, int type)
{
	t_tokn	*new;
	t_tokn	*tail;
	char	*value;

	tail = NULL;
	value = strdup(filename);
	if (!value)
		return (false);
	new = create_token_node(value, type);
	if (!new)
		return (free(value), false);
	append_token_list(expanded, &tail, new);
	return (true);
}

/*
** Inserts sorted globbing results into main token list
** - Updates first node value
** - Links sorted results
** - Preserves original list continuation
** Returns success status
*/
static bool	insert_sorted_results(t_tokn **list, t_tokn *sorted, t_tokn *next)
{
	t_tokn	*temp;

	if (!sorted || !list || !*list)
		return (false);
	free((*list)->value);
	(*list)->value = strdup(sorted->value);
	if (!(*list)->value)
		return (false);
	(*list)->next = sorted->next;
	temp = *list;
	while (temp->next)
		move_pointer(&temp);
	temp->next = next;
	free(sorted);
	return (true);
}

static bool	globing_loop(t_tokn **list, char **patterns, \
	DIR *stream, int *count)
{
	int				i;
	t_tokn			*temp;
	t_tokn			*sorted;
	t_tokn			*expanded;
	struct dirent	*current;

	i = 0;
	temp = (*list)->next;
	sorted = NULL;
	expanded = NULL;
	if (!patterns || !stream)
		return (false);
	current = readdir(stream);
	while (current)
	{
		if (match_pattern(patterns, current->d_name, &i))
		{
			if (!add_to_expanded_list(&expanded, current->d_name, \
				(*list)->type))
				return (free_tokens(expanded), false);
			(*count)++;
		}
		i = 0;
		current = readdir(stream);
	}
	if (*count > 0)
	{
		sort_token_list(&expanded);
		if (!insert_sorted_results(list, expanded, temp))
			return (false);
	}
	return (!current);
}

//
static bool	open_directory(const char *dir_path, DIR **dir_stream)
{
	if (!*dir_stream && dir_path)
	{	
		*dir_stream = opendir(dir_path);
		return (*dir_stream);
	}
	return (false);
}

//
bool	globing(t_tokn **list, const char *path, int *count)
{
	char	**patterns;
	DIR		*dir_stream;

	patterns = NULL;
	dir_stream = NULL;
	if (!*list)
		return (false);
	if (!open_directory(path, &dir_stream))
		return (false);
	patterns = identify_globing_patterns((*list)->value);
	if (!patterns)
		return (false);
	if (globing_loop(list, patterns, dir_stream, count))
		return (closedir(dir_stream), free_array(patterns, 0), true);
	free_array(patterns, 0);
	return (closedir(dir_stream), false);
}
