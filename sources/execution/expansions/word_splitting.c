#include "minislay.h"

//We use this module to split tokens after their expansion.
bool	word_splitting(t_tokn **current, char *expanded, char *delimiter)
{
	t_tokn	*new;
	t_tokn	*next;
	char	*save;

	new = NULL;
	save = expanded;
	if (*current)
	{
		next = (*current)->next;
		while (strtok_r(save, delimiter, &save))
		{
			new = create_token_node(save, (*current)->type);
			if (new)
			{
				insert_token(current, new);
				
			}
		}
		(*current)->next = next;
	}
}
