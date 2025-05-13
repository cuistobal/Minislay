#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	current[1024];

	if (argc == 1)
		return 1;
	getcwd(current, 1024);
	printf("%s\n", current);
	if (argv[1])
	{
		if (chdir(argv[1]) != 0)
			printf("Unable to change direcroty\n");
		else
		{
			getcwd(current, 1024);
			printf("%s\n", current);
		}
	}
	return 0;
}
