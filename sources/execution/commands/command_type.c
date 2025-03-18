#include "minislay.h"

static const char *g_b[BCNT] = {BCDD, BPWD, BENV, BECO, BEXT, BUST, BEXP};

//static bool	is_builtin(char *command)
bool	is_builtin(char *command)
{
	int	index;

	index = 0;
	while (index < BCNT)
	{
		if (strcmp(command, g_b[index]) == 0)
			break;
		index++;
	}
	return (index < BCNT);
}

static bool	is_absolute(char *command)
{
	return (*command == '/');
}

//We use this fonction to assess the type of the current command
bool	command_type(char *command)
{
	if (command)
	{
		if (!is_absolute(command))
		{
			if (!is_builtin(command))
				return (true);			//It's the only case were path retrieval
										//is mandatory.
		}
	}
	return (false);						//Can run into issues if !command but
										//this case is unexpected as we get into
										//this module only if the current expression
										//containes at least 1 WORD token.
}
