/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:12:01 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/05 14:33:36 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
static void sort_nodes(t_tokn **list, t_tokn *new)
{
    t_tokn  *prev;
    t_tokn  *current;

    current = *list;
    if (!*list)
        *list = new;
    else
    {
        while (current)
        {
            prev = current;
            if (strcmp(current->value, new->value) < 0)   

            move_pointer(&current);
        }
    }
      
}
*/
//
static bool	insert_globing_result(t_tokn **list, char *filename, bool *init, int *count)
{
    t_tokn  *new;
	char	*value;

    new = NULL;
	value = strdup(filename);
	if (!value)
		return (false);
	if (!*init)
    {
		free((*list)->value);
		(*list)->value = value;
		*init = true;
		return (true);
    }
	new = create_token_node(value, (*list)->type);
	if (!new)
		return (free(value), false);
	(*count)++;
	(*list)->next = new;
	return (move_pointer(list));
}

//
static bool	globing_loop(t_tokn **list, char **patterns, DIR *stream, int *count)
{
	int				i;
    bool            init;
	t_tokn			*next;
	struct dirent	*current;

	i = 0;
    init = false;
	current = NULL;
	next = (*list)->next;
	if (!patterns || !stream)
		return (false);
	current = readdir(stream);
	while (current)
	{
		if (match_pattern(patterns, current->d_name, &i))
		{
        	if (!insert_globing_result(list, current->d_name, &init, count))
        		break ;
		}
		i = 0;
		current = readdir(stream);
	}
	(*list)->next = next;
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
