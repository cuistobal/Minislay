#include "test_module.h"

int main(int argc, char **argv)
{
    t_tokn  *tokens = NULL;
    char    *trimmed = NULL;

    if (argc == 2)
    {
        trimmed = (char *)malloc(sizeof(char) * strlen(argv[1]));
        if (trimmed)
        {
            whitespaces_collapsing(argv[1], trimmed);
            printf("Original    ->  %s\nProcessed   ->  %s\n", argv[1], trimmed);
            tokenize_user_input(&tokens, trimmed, "|"); 
            while (tokens)
            {
                printf("%s\n", tokens->content);
                tokens = tokens->next;
            }
        }
    }
}
