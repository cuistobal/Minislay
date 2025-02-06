/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <chrleroy@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:20:06 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/06 13:55:42 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Réimplémentation de strtok_r
char	*my_strtok_r(char *str, const char *delim, char **saveptr)
{
    char	*token_start;

    if (str == NULL)
        str = *saveptr;
    while (*str && strchr(delim, *str)) 
        str++;
    if (*str == '\0') 
        return NULL;
    token_start = str;
    while (*str && !strchr(delim, *str))
        str++;
    if (*str) 
    {
        *str = '\0';
		str++;
    }
    *saveptr = str;
    return (token_start);
}
/*

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv) 
{
    char 		*str;
    char 		*token;
    const char 	*delim;
    char 		*saveptr;

	if (argc == 3)
	{
		str = argv[1];
		delim = argv[2];
    	token = my_strtok_r(str, delim, &saveptr);
    	while (token != NULL) 
		{
            printf("Token: %s\n", token);
            token = my_strtok_r(NULL, delim, &saveptr);
    	}
	}
    return 0;
}*/
