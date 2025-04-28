#include <unistd.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*infile;
	char	*message;
	char	*outfile;
	int		pipefd[2];
	int		redirection[2];

	if (argc == 4)
	{
		infile = argv[1];
		message = argv[2];	
		outfile = argv[3];
		redirection[0] = open(infile, O_RDONLY);
		redirection[1] = open(outfile, O_RDWR);
		dup2(STDIN_FILENO, pipefd[1]);
		pid = fork();
		if (pid == 0)
		{

		}
	}	
}
