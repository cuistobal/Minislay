#include "minislay.h"

bool    dollar_expansions(char *token)
{
    if (token)
    {
        while (*token)
        {
            if (*token == '$')

        }
    }
}

//This module handles expansions. First, we send the expansion list, then the
//assignation list.
bool    expand(t_tokn *list)
{
    while (list)
    {
        if (list->type & DOLL)
            dollar_expansions();
        if (list->type & STAR)
        {
            globing();
        }
    }
}
