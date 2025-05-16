//#include "minislay.h"
#include "globing.h"

//
int	main(int argc, char **argv)
{
	int				count;
	int				index;
	const char		*pattern;
	char			**expansions;

	expansions = NULL;
	if (argc > 2)
	{
		argv++;
		index = 0;
		count = 1;
		pattern = *argv;
		argv++;
		while (*argv)
		{
			expansions = globing(pattern, *argv, &count);
			if (expansions)
			{
				while (expansions[index])
				{
					printf("%s\n", expansions[index]);
					index++;
				}
				free_array(expansions, index);
			}
			argv++;
		}
	}
	else
		printf("Invalid argc. Usage: ./a.out pattern dir_path ...\n");
	return 0;
}
