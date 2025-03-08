#include "minislay.h"

//Turning the branch's token list into an execution block
bool	prepare_for_exec(t_tree *branch)
{
	bool	command;
	t_tokn	*current;

	if (branch)
	{
		command = false;
		current = branch->tokens;
		while (current)
		{
			if (valid_lexeme(current, IRED, ARED))
			{
				current->type >> CONVERT;
				current = current->next;
				if (!current)
					return (current);
				current->type = FILENAM;
			}
			else if (!command)
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
}
