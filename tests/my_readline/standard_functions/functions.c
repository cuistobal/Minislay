/*
isatty
ttyname
ttyslot
ioctl
getenv
tcsetattr
tcgetattr
tgetent 
tgetflag
tgetnum
tgetstr
tgoto 
tputs
*/
#include <term.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>

int	main(int argc, char **argv)
{
	int		fd;
	void	*ptr;
	char	*terminal_name;

	fd = open("test", O_CREAT, 0644);

	terminal_name = argv[0];
/*
	while (true)
	{

	}
*/
//	return (isatty(0)) ? printf("is a tty\n") : printf("Is not a tty\n");
	
	if (isatty(0))
	{
		printf("Name	->	%s\n", ttyname(0));
		printf("Slot	->	%d\n", ttyslot());
		if (ioctl(0, TIOCGWINSZ, ptr) == 0)
		{
			struct winsize *window = ptr;
			if (window)
			{
				printf("%u\n", window->ws_row);
				printf("%u\n", window->ws_col);
				printf("%u\n", window->ws_xpixel);
				printf("%u\n", window->ws_ypixel);
			}
		}
		if (ioctl(0, TIOCSWINSZ, ptr) == 0)
		{
			struct winsize *resize = ptr;

		}
	}
	return 0;
}
