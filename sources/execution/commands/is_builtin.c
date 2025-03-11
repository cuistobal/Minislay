#include "minislay.h"

static const char *g_b[BCNT] = {BCDD, BPWD, BENV, BECO, BEXT, BUST, BEXP};

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
