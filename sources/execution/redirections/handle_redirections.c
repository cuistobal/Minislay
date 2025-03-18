#include "minislay.h"

// Function to open an output file in append mode
static bool open_outfile_append(t_tokn **redirections)
{
	int	fd;

	if (*redirections)
	{
        move_pointer(redirections);
		if (*redirections)
		{
			if (!(*redirections)->next || is_state_active((*redirections)->next->type, WORD))			
			{
				fd = open((*redirections)->value, O_RDONLY);
				if (fd == -1)
				{
					printf("Unable to open %s\n", (*redirections)->value);
					return (false);
				}
				(*redirections)->type = fd; 
        		move_pointer(redirections);
				return (true);	
			}
			//Error message -> Ambiguous syntax
			printf("Ambiguous syntax\n");
			return (false);	
		}
	}
    return (!*redirections);
}

// Function to open a here-document
static bool open_here_doc(t_tokn **redirections)
{
	int	fd;

	if (*redirections)
	{
        move_pointer(redirections);
		if (*redirections)
		{
			if (!(*redirections)->next || is_state_active((*redirections)->next->type, WORD))			
			{
				fd = open((*redirections)->value, O_RDONLY);
				if (fd == -1)
				{
					printf("Unable to open %s\n", (*redirections)->value);
					return (false);
				}
				(*redirections)->type = fd; 
        		move_pointer(redirections);
				return (true);	
			}
			//Error message -> Ambiguous syntax
			printf("Ambiguous syntax\n");
			return (false);	
		}
	}
    return (!*redirections);
}

// Function to open an output file in overwrite mode
static bool open_outfile(t_tokn **redirections)
{
	int	fd;

	if (*redirections)
	{
        move_pointer(redirections);
		if (*redirections)
		{
			if (!(*redirections)->next || is_state_active((*redirections)->next->type, WORD))			
			{
				fd = open((*redirections)->value, O_RDONLY);
				if (fd == -1)
				{
					printf("Unable to open %s\n", (*redirections)->value);
					return (false);
				}
				(*redirections)->type = fd; 
        		move_pointer(redirections);
				return (true);	
			}
			//Error message -> Ambiguous syntax
			printf("Ambiguous syntax\n");
			return (false);	
		}
	}
    return (!*redirections);
}

// Function to open an input file
static bool open_infile(t_tokn **redirections)
{
	int	fd;

	if (*redirections)
	{
        move_pointer(redirections);
		if (*redirections)
		{
			if (!(*redirections)->next || is_state_active((*redirections)->next->type, WORD))			
			{
				fd = open((*redirections)->value, O_RDONLY);
				if (fd == -1)
				{
					printf("Unable to open %s\n", (*redirections)->value);
					return (false);
				}
				(*redirections)->type = fd; 
        		move_pointer(redirections);
				return (true);	
			}
			//Error message -> Ambiguous syntax
			printf("Ambiguous syntax\n");
			return (false);	
		}
	}
    return (!*redirections);
}

// Function to handle redirections
bool	handle_redirection_list(t_tokn **list)
{
	t_tokn	*redirections;

	redirections = *list;
    while (redirections)
    {
        if (valid_lexeme(redirections, IRED, ARED))
        {
            if (redirections->type == IRED)
                open_infile(&redirections);
            else if (redirections->type == ORED)
                open_outfile(&redirections);
            else if (redirections->type == ARED)
                open_outfile_append(&redirections);
            else if (redirections->type == HDOC)
                open_here_doc(&redirections);
        }	
        move_pointer(&redirections);
    }
    return true;
}
