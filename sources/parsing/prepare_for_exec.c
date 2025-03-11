#include "minislay.h"

/*
 *
 *		USELESS FOR NOW
 *
 *
 */



//
static void	handle_assignations(t_tokn **current)
{
	if (*current)
	{
		if (is_state_active((*current)->type, EQUL))
		{
			//(*current)->type = ASSIGNS;
			*current = (*current)->next;
			handle_assignations(current);
		}
	}
}

//
static void	handle_commands(t_tokn **current, bool *command)
{
	while (*current)
	{
		if (*command)
			(*current)->type = ARGUMNT;
		else
		{
			*command = true;
			(*current)->type = EXECTBL;
		}
		*current = (*current)->next;
	}
}

//
static void handle_redirections(t_tokn **current)
{
	if (*current)
	{
		if (valid_lexeme(*current, IRED, ARED))
		{
			*current = (*current)->next;
			if (*current)
			{
				(*current)->type = FILENAM;
				*current = (*current)->next;
				handle_redirections(current);	
			}	
		}
	}
}

//Turning the branch's token list into an execution block
void	prepare_for_exec(t_tree *branch)
{
	bool	command;
	t_tokn	*current;

	current = NULL;
	command = false;
	if (branch)
	{
		current = branch->tokens;
		if (current)
		{
			handle_assignations(&current);
			while (current)
			{
				if (valid_lexeme(current, IRED, ARED))
					handle_redirections(&current);
				handle_commands(&current, &command);
			}
		}
	//	return (!current);
	}
//	return (branch);
}
/*
			if (!handle_redirection(current))
			{
				
			}
			if (!command)
			{
			}
			



			if (valid_lexeme(current, IRED, ARED))
			{
				current = current->next;
				if (!current)
					return (current);
				current->type = FILENAM;
			}
			else if (!command && !is_state_active(current->type, EQUL))
			{
				command = true;
				current->type = EXECTBL;
			}
			else
				current->type = ARGUMNT;
			current = current->next;
		}
	}
	return (branch);
}*/
