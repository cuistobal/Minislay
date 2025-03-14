#include "minislay.h"

//We use this module to split tokens after their expansion.
bool	word_splitting(t_shel *minishell, t_tokn **current, char *expanded)
{
	t_tokn	*new;
	t_tokn	*next;
	char	*save;
	char	*delimiter;

	new = NULL;
	save = expanded;
	delimiter = minishell->special[DIFSI];
	if (*current)
	{
		next = (*current)->next;
		free((*current)->value);
		(*current)->value = save;
		while (strtok_r(save, delimiter, &save))
		{
			if (*save)
			{
				new = create_token_node(save, (*current)->type);
				if (!new)
					break ;
				(*current)->next = new;
				*current = new;	
			}
		}
		(*current)->next = next;
		*current = next;
	}
	return (!save);
}
