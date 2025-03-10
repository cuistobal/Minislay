#include "minislay.h"

bool	pwd(char *current_dir)
{
	char	*current;
	char	temp[BSIZE];

	current = NULL;
	if (getcwd(temp, BSIZE))
	{
		current = strdup(temp);
		//mettre dans la struct;
		return (true);
	}
	//APpend error code
	return (false);
}
