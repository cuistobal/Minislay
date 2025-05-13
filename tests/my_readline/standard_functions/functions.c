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
		struct winsize	resize;
		resize.ws_row = 10;
		resize.ws_col = 100;
		resize.ws_xpixel = 0;
		resize.ws_ypixel = 0;
		ioctl(0, TIOCSWINSZ, &resize);
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
	}
	return 0;
}
