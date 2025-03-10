#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

# define LIMITERS "     *"
# define SPECIALS "$?"

char    *expansion(char *token, int *index, int *blen)
{
    int start;

    start = *index;
    while (token[*index] && !strchr(LIMITERS, token[*index]))
    {
        (*blen)++;
        (*index)++;
        if (strchr(SPECIALS, token[*index]))
        {
            (*blen)++;
            (*index)++;
            break ;
        }
    }
    return strndup(token + start, *index - start);
}

bool    find_expansions(char **buffer, char *token, int *index, int *blen)
{
    if (token)
    {
        while (token[*index])
        {
            while (token[*index] && token[*index] != '$')
                (*index)++;
            if (token[*index])
            {
                *buffer = expansion(token, index, blen);
                return (*buffer);
            }
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    int     blen;
    int     index;
    char    *buffer;

    buffer = NULL;
    if (argc > 1)
    {
        argv++;
        blen = 0;
        index = 0;
        while (*argv)
        {
            while (find_expansions(&buffer, *argv, &index, &blen))
            {
                printf("%s\n", buffer);
                free(buffer);
                buffer = NULL;
            }
            argv++;
        }
        return 0;
    }
    printf("Usage: ./a.out arg1 ... argn\n");
    return 1;
}
