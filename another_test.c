#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void free_array(char **array, int count)
{
    if (array)
    {
        while (count--)
            free(array[count]);
        free(array);
        array = NULL;
    }
}

static char *add_string(char *string, char *delimiter, int *start, int *index)
{
    char *new;

    new = NULL;
    if (string)
    {
        new = strndup(string + *start, *index - *start);
        if (!new)
            return (NULL);
        while (string[*index] && strchr(delimiter, string[*index]))
            (*index)++;
        *start = *index + 1;
    }
    return (new);
}

static int  count_words(char *string, char *delimiter)
{
    int count;
    int index;

    index = 0;
    count = 0;
    while (string[index])
    {
        if (!strchr(delimiter, string[index]))
            index++;
        else
        {
            if (index != 0)
                count++;
            while (*string && strchr(delimiter, string[index]))
                index++;
        }
    }
    count++;
    return (count);
}

char    **reworked_split(char *string, char *delimiter)
{
    int index;
    int start;
    int count;
    int i;
    char **splited;

    splited = NULL;
    if (string && delimiter)
    {
        index = 0;
        start = 0;
        count = count_words(string, delimiter);
        splited = (char **)malloc(sizeof(char *) * (count + 1));
        if (!splited)
            return (NULL);
        i = 0;
        while (string[index])
        {
            if (!strchr(delimiter, string[index]))
                index++;
            else
            {
                splited[i] = add_string(string, delimiter, &start, &index);
                if (!splited[i])
                    free_array(splited, i);
                i++;
            }
        }
        splited[i] = add_string(string, delimiter, &start, &index);
        splited[count] = NULL;
    }
    return (splited);
}

int main(int argc, char **argv)
{
    char *delimiters;
    char **splited_args;

    if (argc > 2)
    {
        argv++;
        delimiters = *argv;
        argv++;
        while (*argv)
        {
            splited_args = reworked_split(*argv, delimiters);
            if (splited_args)
            {
                for (int i = 0; splited_args[i]; i++)
                {
                    printf("%s\n", splited_args[i]);
                    free(splited_args[i]);
                }
                free(splited_args);
            }
            argv++;
        }
        return 0;
    }
    printf("Usage: ./a.out 'delimiters' 'string' ...\n");
    return 1;
}
