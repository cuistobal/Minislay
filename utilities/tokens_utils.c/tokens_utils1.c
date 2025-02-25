#include "minislay.h"

//This function frees the token list passed as parameter
void	free_tokens(t_tokn *tokens)
{
	t_tokn *temp;

	temp = tokens;
	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		if (temp->value)
			free (temp->value);
		free (temp);
	}
}

