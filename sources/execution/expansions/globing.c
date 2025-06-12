/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:12:01 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 13:04:39 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static bool	add_to_expanded_list(t_tokn **expanded, char *filename, int type, \
		int *count)
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
	(*count)++;
	return (true);
}

//
static bool	insert_sorted_results(t_tokn **list, t_tokn **expanded, \
		t_tokn *next, int *count)
{
	t_tokn	*temp;

	if (!*expanded || !list || !*list)
		return (false);
	if (*count <= 0)
		return (true);
	else if (is_state_active((*list)->type, IRED | ARED | ORED) && *count != 1)
		return (*count = 0, false);
	free((*list)->value);
	(*list)->value = strdup((*expanded)->value);
	if (!(*list)->value)
		return (false);
	(*list)->next = (*expanded)->next;
	temp = *expanded;
	while (temp->next)
		temp = temp->next;
	temp->next = next;
	return (true);
}

//Loops through the current directory to find matching patterns
static bool	globing_loop(t_tokn **list, char *pattern, \
	DIR *stream, int *count)
{
	int				i;
	t_tokn			*expanded;
	struct dirent	*current;

	expanded = NULL;
	if (!pattern || !stream)
		return (false);
	current = readdir(stream);
	while (current)
	{
		i = 0;
		if (valid_star_expansion(pattern, current->d_name) && \
				match_pattern(pattern, current->d_name))
		{
			if (!add_to_expanded_list(&expanded, current->d_name, \
				(*list)->type, count))
				return (free_tokens(expanded), false);
		}
		current = readdir(stream);
	}
	if (!insert_sorted_results(list, &expanded, (*list)->next, count))
		return (free_tokens(expanded), false);
	return (free(expanded->value), free(expanded), true);
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
	char	*pattern;
	DIR		*dir_stream;

	dir_stream = NULL;
	if (!*list)
		return (false);
	if (!open_directory(path, &dir_stream))
		return (false);
	pattern = strdup((*list)->value);
	if (!pattern)
		return (false);
	if (globing_loop(list, pattern, dir_stream, count))
		return (closedir(dir_stream), free(pattern), true);
	free(pattern);
	return (closedir(dir_stream), false);
}
