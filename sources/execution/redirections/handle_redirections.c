#include "minislay.h"

static const char	*g_redir[] = {}

//
static bool	open_outfile_append()
{

}

//
static bool	open_here_doc()
{

}

//
static bool	open_outfile()
{

}

//
static bool	open_infile()
{

}

bool	handle_redirections(t_tokn *redirections)
{
	int	fd;

	while (redirections)	
	{
		if (valid_lexeme(redirections, IRED, ARED))
		{


			if (redirections->next)
			{

			}
		}
	}
}
