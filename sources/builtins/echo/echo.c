#include "minislay.h"

//Echo built-in. Prints the argument followed by a new_line unless the flag is
//spefied.
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
