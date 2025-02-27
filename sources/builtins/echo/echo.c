#include "minislay.h"

bool	echo(const char **arguments, bool flag)
{
	while (*arguments)
	{
		printf("%s", *arguments);
		if (!flag)
			pritnf("\n");
		*arguments++;
	}
}
