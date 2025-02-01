#ifndef TEST_MODULE_H
# define TEST_MODULE_H

# include <string.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct  token
{
    char            type;
    char            *content;
    struct  token   *next;
}   t_tokn;


//whitespaces_collapsing.c:
bool    is_space(char c);
void    append_char(char *dest, char c, int *pos);
bool    whitespaces_collapsing(char *input, char *collapsed);

//tokenize_user_input.c:
bool    tokenize_user_input(t_tokn **list, char *input, char *separator);
bool    create_token_node_and_append_list(t_tokn **list, char *token);
t_tokn  *create_token_node(char *content, char type);

#endif
