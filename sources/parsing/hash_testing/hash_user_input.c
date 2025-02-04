/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_user_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:59:43 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/04 14:56:14 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Determines the group of a character and return its group index.
static int get_group(bool (*group_functions[])(char), char c)
{
    int 	index;

    index = 0;
    while (index < GROUP_OTHER)
    {
        if (group_functions[index](c))
            return (index);
        index++;
    }
    return (GROUP_OTHER);
}

//Initialises the array of function pointers.
static void	initialise_check_type(bool (*group_functions[])(char))
{
    group_functions[0] = is_paren;
    group_functions[1] = is_amp_pipe;
    group_functions[2] = is_iredir;
    group_functions[3] = is_oredir;
    group_functions[4] = is_squotes;
    group_functions[5] = is_dquotes;
    group_functions[6] = is_var_wild;
    group_functions[7] = is_whitespace;
}

//Hashing function that turns the user's input into a chain of digits rannging
//from 0 to 9 included.
//We use this array to identify tokens and construct our execution tree. 
uint8_t	*hash_input(char *user_prompt, int len)
{
    int 	index;
    uint8_t	*input;
	bool	(*check_type[9])(char);

    input = NULL;
    if (user_prompt)
    {
        input = (int *)malloc(sizeof(int) * len);
        if (input)
		{
			index = 0;
			initialise_check_type(check_type);
        	while (index < len)
        	{
        	    input[index] = get_group(check_type, user_prompt[index]);
        	    index++;
        	}
			return (input);
		}
    }
    return (NULL);
}
/*
 *	Module test main
 *

int main(int argc, char **argv)
{
    int len;
    int *input;
    int index;

    if (argc == 2)
    {
        len = strlen(argv[1]);
        input = hash_input(argv[1], len);
        if (input)
        {
            index = 0;
            while (index < len)
            {
                printf("%d", input[index]);
                index++;
            }
            printf("\n");
            free(input);
            printf("%s\n", argv[1]);
        }
    }
    return 0;
}*/
