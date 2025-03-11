#include "minislay.h"

bool	move_env_pointer(t_env **pointer)
{
	if (*pointer)
	{
		*pointer = (*pointer)->next;
		return (true);
	}
	return (false);
}

//We use this util to consume the current pointer
bool	move_pointer(t_tokn **pointer)
{
	if (*pointer)
	{
		*pointer = (*pointer)->next;
		return (true);
	}
	return (false);
}
//We use this utility to move to the next token 
bool	move_list_pointer(t_tokn **pointer, t_tokn **save)
{
	if (*pointer)
	{
		*save = *pointer;
		*pointer = (*pointer)->next;
		return (true);
	}
	return (false);
}
