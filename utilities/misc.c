#include "minislay.h"

//We use this utility to move to the next token 
inline bool	move_list_pointer(t_tokn **pointer)
{
	if (*pointer)
		*pointer = (*pointer)->next;
	return (*pointer);
}
