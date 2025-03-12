#include "minislay.h"

//A retravailler
static void	append_redirections(t_tokn **head, t_tokn **tail, t_tokn **current)
{
	if (*head)
		(*tail)->next = *current;
	else
	{
		*head = *current;
		*tail = *current;
	}
	move_pointer(current);
	if (*current)
	{
		set_state(&(*current)->type, FILENAM);
		*tail = *current;
		move_pointer(current);
		if (*current)
			(*tail)->next = NULL;
	}
}

//
void	modify_token_types(t_tokn **expanded, t_tokn **redirections, int *count)
{
	bool	command;
	t_tokn	*current;
	t_tokn	*previous;
	t_tokn	*redir_list;

	*count = 0;
	command = false;
	previous = NULL;
	redir_list = *redirections;
	current = *expanded;
	while (current)
	{
		if (valid_lexeme(current, IRED, ARED))
		{
			append_redirections(redirections, &redir_list, &current);
			if (previous)
				previous->next = current;
			else
				*expanded = current;
		}
		else
		{
			previous = current;
			if (command)
				set_state(&(*expanded)->type, ARGUMNT);
			else
			{
				command = true;
				set_state(&(*expanded)->type, COMMAND);
			//	if (is_builtin((*expanded)->value))
			//		set_state(&(*expanded)->type, BUILTIN);
			}
			(*count)++;
			move_pointer(&current);
		}
	}
}
