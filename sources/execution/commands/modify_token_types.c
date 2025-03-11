#include "minislay.h"

//A retravailler
static void	append_redirections(t_tokn *redirections, t_tokn **current)
{
	t_tokn	*save;

	save = *current;
	if (!redirections)
		redirections = *current;
	move_pointer(current);
	if (*current)
	{
		set_state(&(*current)->type, FILENAME);
		save = *current;
		move_pointer(current);
		if (*current)
			save->next = NULL;
	}
}

//
void	modify_token_types(t_tokn **expanded, t_tokn **redirections, int *count)
{
	bool	command;
	t_tokn	*current;

	*count = 0;
	command = false;
	current = *expanded;
	while (current)
	{
		if (valid_lexeme(current->type, IRED, ARED))
			append_redirections(redirections, current);
		else
		{
			if (command)
				set_state(&(*expanded)->type, ARGUMENT);
			else
			{
				command = true;
				set_state(&(*expanded)->type, COMMAND);
				if (is_buitin((*expanded)->value))
					set_state(&(*expanded)->type, BUILTIN);
			}
			(*count)++;
			move_pointer(&current);
		}
	}
}
