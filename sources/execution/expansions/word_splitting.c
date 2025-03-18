#include "minislay.h"

static bool words(t_tokn **current, char *delimiter)
{
    t_tokn  *new;
    t_tokn  *save;
    char    *word;
    char    *expanded;

    save = (*current)->next;
   // expanded = strdup((*current)->value);
    expanded = (*current)->value;
    if (expanded)
    {
        word = strtok_r(expanded, delimiter, &expanded);
	    (*current)->value = word;
        word = strtok_r(expanded, delimiter, &expanded);
        while (word && expanded)
        {
            new = create_token_node(strdup(word), (*current)->type);
		    if (!new)
                break ;
		    (*current)->next = new;
		    *current = new;
            word = strtok_r(expanded, delimiter, &expanded);
        }
        (*current)->next = save;
        //*current = save;
    }
    return (!*expanded);
}

//We use this module to split tokens after their expansion.
bool	word_splitting(t_shel *minishell, t_tokn **current)
{
	char	*delimiter;

	delimiter = minishell->special[DIFSI];
	if (*current && delimiter)
        return (words(current, delimiter));
    return (false);
}
