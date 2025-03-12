#include "minislay.h"

//We use this function to split the current's branch list into a list of
//assignation tokens, and a list containing the rest of the tokens.
//
//Basically, any leading expansions token ends up in the assignation list, while
//all tokens with the EQUL status active met after the first non assignation
//tokens are considered a command/argument.
//
//Tokens ending up in the expansions list are expanded right after. If the
//expansions list is empty, the assignations are sent to the local list of 
//variable in the Minishell struct.
//Otherwise, they're active only during the execution of the command block, and
//get sent to the command list of variable in Minishell struct.
bool	split_list(t_tokn *current, t_tokn **assignations, t_tokn **expansions)
{
	t_tokn	*save;

	save = current;	
	if (current)
	{
		if (is_state_active(current->type, EQUL))
		{
			//Implement check_assignation
			//check_assignation();
			//
			*assignations = current;
			while (current && is_state_active(current->type, EQUL))
			{
		//		if (!check_assignation())
		//			break ;
				move_list_pointer(&current, &save);
			}
		}
		if (current)
		{
			if (*assignations)
				save->next = NULL;
			*expansions = current;
		}
		//TBM
		return true;
	}
	return (!current);
}

//IL FAUT INTEGRER LE MODULE DE CHECK DE VALIDITE POUR LES ASSIGNATIONS
