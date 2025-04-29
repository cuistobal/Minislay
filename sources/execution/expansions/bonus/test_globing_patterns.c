/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_globing_patterns.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:11:56 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/29 10:11:58 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static char	*create_sub_string(const char *string, int length)
{
	if (string)
		return (strndup(string, length));
	return (NULL);
}

//
static char	*handle_words(const char *globing, int *index)
{
	int	start;

	if (!globing)
		return (NULL);
	start = *index;
	while (globing[*index])
	{
		(*index)++;
		if (!globing[*index] || globing[*index] == '*')
			break ;
	}
	return (create_sub_string(globing + start, *index - start));
}

//
static char	*handle_stars(const char *globing, int *index)
{
	int	start;

	if (!globing)
		return (NULL);
	start = *index;
	while (globing[*index])
	{
		(*index)++;
		if (!globing[*index] || globing[*index] != '*')
			break ;
	}
	return (create_sub_string(globing + start, 1));
}

//
static char *handle_pattern(char *globing, int *index)
{
	char	*new;

	new = NULL;
	if (globing[*index] == '*')
		new = handle_stars(globing, index);
	else
		new = handle_words(globing, index);
	return (new);
}

//
static bool	valid_pattern(const char globing, char ***patterns, int pindex)
{
	if (globing != '\0')
		return (free_array(*patterns, pindex), false);
	return (true);
}

//We use this function to identify the patterns within the the globing variable
char	**identify_globing_patterns(char *globing)
{
	int		index;
	int		pindex;
	char	**patterns;
	
	patterns = NULL;
	if (!globing)
		return (NULL);
	index = 0;	
	pindex = 0;
	while (globing[index])
	{	
		pindex++;

		//	Optimissable

		patterns = (char **)realloc(patterns, sizeof(char *) * (pindex + 1));
		if (!patterns)
			return (NULL);
		patterns[pindex - 1] = handle_pattern(globing, &index);
		patterns[pindex] = NULL;
		if (!patterns[pindex - 1])
			break ;
	}
	valid_pattern(globing[index], &patterns, pindex);
	//error -> invalid globing variable
	return (patterns);
}
/*
//TEST
int	main(int argc, char **argv)
{
	char	*temp;
	int		index;
	int		pindex;
	char	**patterns;

	pindex = 1;
	patterns = NULL;
	if (argc == 2)
	{
		patterns = identify_globing_patterns((const char *)argv[1], &pindex);
		if (patterns)
		{
			index = 0;
			while (patterns[index])
			{
				printf("%s\n", patterns[index]);
				index++;
			}
			free_array(patterns, pindex);
		}
		else
			printf("patterns is NULL.\n");
	}
	else
		printf("Invalid argc. Usage: ./a.out pattern\n");
	return 0;
}*/
