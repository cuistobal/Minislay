#include "minislay.h"

static bool get_expanded(t_shel *minishell, t_tokn **list)
{
    int     index;
    int     blen;
    char    *buffer;
    char    *expanded;
    
    blen = 0;
    index = 0;
    buffer = NULL;
    expanded = NULL;
    while (find_expansions(&buffer, list->value, &index, &blen))
    {
        check_key
                    //Modify list->value
                    list->value
    }
}

//Entry point of the dollar expansion
bool    expand(t_shel *minishell, t_tokn *list)
{
    if (minishell)
    {
        while (list)
        {
            if (list->type & DOLL)
            {
                if (!get_expanded(list))
                    return (false);
            }
            move_pointer(&list);
        }
        return (!list);
    }
    return (minishell);
}
