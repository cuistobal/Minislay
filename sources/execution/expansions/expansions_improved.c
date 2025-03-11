#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

# define LIMITERS "     *"
# define SPECIALS "$?"

char    *expansion(char *token, int *index, int *blen)
{
    while (token[*index + *blen] && !strchr(LIMITERS, token[*index + *blen]))
    {
        (*blen)++;
        if (strchr(SPECIALS, token[*index + *blen]))
        {
            (*blen)++;
            break ;
        }
    }
    return (strndup(token + *index, *blen));
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
	char	*temp;

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
				index += blen;
				blen = 0;
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
