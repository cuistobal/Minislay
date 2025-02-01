#include <stdio.h>

int main ()
{
    char    *input;
    char    *parsed;
    t_tokn  *list;

    list = NULL;
    parsed = NULL;
    input = readline();
    if (whitespaces_collapsing(input, parsed);
    {
        if (tokenize_user_input(&list, parsed))
        {
            while ((*list)NULL)
            {
                while (*(*list))
                {
                    printf("%s\d", (*list)->content);
                    (*list) = (*list)->next;
                }
                printf("\n");
                ()
        }
    }
}
