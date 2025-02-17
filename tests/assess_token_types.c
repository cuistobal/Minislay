#include "minislay.h"

static const char	g_delim[DELIMITERS] = {};

static bool	append_token_list()
{

}

static bool	create_sub_token(char *value, int pos)
{
	int		type;
	char	*next_token;


}

static int	is_delimiter(char c)
{
	int	index;

	index = 0;
	while (index < DELIMITERS)
	{
		if (c == g_delim[index])
			return (index);
	}
	return (DELIMITERS);
}

static bool	find_delimiter(char *value, int *pos)
{
	int start;

	start = *pos;
	while (value[*pos])
	{
		if ()
		(*pos)++;
}

bool	assess_token_type(t_tokn *current)
{
	int		pos;
	t_tokn	*next;
//	t_parse	parser;
	t_tokn	*sub_token;
	
	if (current && current->value)
	{
		pos = 0;
		next = current->next;
		while (current->value[pos])
		{
			find_delimiter( ,&pos);	//pos = la position du delimiteur.
			create_sub_token(current->value, pos);
			modify_current();
			append_token_list();
		}
	}
	return (true);
}
