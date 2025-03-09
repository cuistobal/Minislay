#include "minislay.h"

bool	append_list(t_tokn **current, t_tokn **save)
{
	if (*current)
		(*save)->next = NULL;
	return (*current);	
}

inline bool	move_list_pointer(t_tokn **pointer, t_tokn **save)
{
	if (*pointer)
	{
		*save = *pointer;
		*pointer = (*pointer)->next;
		return (true);
	}
	return (false);
}

//We use this function to split the current's branch list into a list of
//assignation tokens, and a list containing the rest of the tokens.
//Basically, any leading expansions token ends up in the assignation list, while
//all tokens with the EQUL status active met after the first non assignation
//tokens are considered a command/argument.
//Tokens ending up in the expansions list are expanded right after. If the
//expansions list is empty, the assignations are sent to the local list of 
//variable in the Minishell struct. Otherwise, they're active only during the
//execution of the command block.
bool	split_list(t_tokn *current, t_tokn **assignations, t_tokn **expansions)
{
	t_tokn	*save;

	save = NULL;
	while (current)
	{
		if (current->type & EQUL)
		{
			*assignations = current;
			while (current && is_state_active(current->type, EQUL))
				move_list_pointer(&current, &save);
		}
		if (append_list(&current, &save))
			*expansions = current;
	}
	return (!current);
}
