#include "minislay.h"
//#include "globing.h"

//
bool	match_pattern(char **patterns, char *current)
{
	char	*temp;

	if (patterns && current)
	{
		temp = NULL;
		if (*patterns)
		{
			if	(strcmp(*patterns, "*") == 0)
				return (match_pattern(patterns + 1, current));
			else
			{
				temp = strstr(current, *patterns);
				if (temp)
					return (match_pattern(patterns + 1, temp + strlen(temp)));
				return false;
			}
		}
		return (true);
	}
	return (false);
}
