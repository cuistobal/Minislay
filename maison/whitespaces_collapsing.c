/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespaces_collapsing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <chrleroy@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:57:13 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/01 17:03:49 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

//To me moved to utilities
bool    is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

//This function appends valid char to dest at the right index.
void    append_char(char *dest, char c, int *pos)
{
    if (dest)
    {
        dest[*pos] = c;
        (*pos)++;
    }
}

//Not tested    ->  To implement
/*
void    process_collapsed_and_stack(char *collapsed, char bool *space, int *j)
{
    if (space && (*j) > 0)
        append_char(collapsed, ' ', j); //remplacer ' ' par SPACE
    append_char(collapsed, input[i], j);
    space = false;
    if (is_syntax(element))
        stack();
}*/

//We use this function to trim the execessive whitespaces && remove leading &
//ending ones. 
//The idea is to set collapssed as equal to input in the calling function so we
//don't have to malloc unnecessarily.
bool    whitespaces_collapsing(char *input, char *collapsed)
{
    int     i;
    int     j;
    bool    space;

    if (input && collapsed)
    {
        i = 0;
        j = 0;
        space = false;
        while (input[i] != '\0')
        {
            if (is_space(input[i]))
                space = true;
//          else
//              process_collapsed_and_stack();
//create a sub_function
            else
            {
//stack
                if (space && j > 0)
                    append_char(collapsed, ' ', &j); //remplacer ' ' par SPACE
                append_char(collapsed, input[i], &j);
                space = false;
            }
//end of sub_function
            i++;
        }
        return (collapsed[j] = '\0', true);
    }
    return (false);
}/*

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char *trimmed;

    if (argc == 2)
    {
        trimmed = strdup(argv[1]);
        printf("%ld\n", strlen(trimmed));
        (whitespaces_collapsing(argv[1], trimmed)) ? printf("Original    ->  %s\nProcessed   ->  %s\n", argv[1], trimmed) : printf("Trimming error\n");
        printf("%ld\n", strlen(trimmed));
        free (trimmed);
        return 0;
    }
    printf("Usage: ./a.out argv\n");
    return 0;
}*/
