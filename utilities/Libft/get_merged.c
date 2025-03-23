#include "minislay.h"

//We use this function to merge to arrays and free their original memory adress
bool	get_merged(char **merged, char **temp, char **expanded)
{
	*merged = ft_strjoin(*temp, *expanded);
	if (*merged)
	{
		if (*temp)
		{
			free(*temp);
			*temp = NULL;
		}
		*expanded = *merged;
		return (true);
	}
	else
	{
		if (*temp)
		{
			free(*temp);
			*temp = NULL;
		}
		free(*expanded);
		*expanded = NULL;
	}
	return (false);
}

