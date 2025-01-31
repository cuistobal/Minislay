/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespaces_collapsing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <chrleroy@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:57:13 by chrleroy          #+#    #+#             */
/*   Updated: 2025/01/31 11:57:53 by chrleroy         ###   ########.fr       */
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
            else
            {
                if (space && j > 0)
                    append_char(collapsed, ' ', &j);
                append_char(collapsed, input[i], &j);
                space = false;
            }
            i++;
        }
        collapsed[j] = '\0';
        return (true);
    }
    return (false);
}/*

#include <stdio.h>
int main(int argc, char **argv)
{
    char *trimmed;

    if (argc == 2)
    {
        trimmed = argv[1];
        (whitespaces_collapsing(argv[1], trimmed)) ? printf("%s\n%s\n", trimmed, argv[1]) : printf("Trimming error\n");
    }
    return 0;
}*/
