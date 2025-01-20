/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <chrleroy@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:20:06 by chrleroy          #+#    #+#             */
/*   Updated: 2025/01/19 08:28:36 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minislay.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Réimplémentation de strtok_r
char *my_strtok_r(char *str, const char *delim, char **saveptr)
{
    char *token_start;
    
    token_start = str;
    if (str == NULL) 
    {
        // Si la chaîne est NULL, continue à partir de la dernière position enregistrée
        str = *saveptr;
    }
    // Ignorer les délimiteurs au début
    while (*str && strchr(delim, *str)) 
    {
        str++;
    }
    if (*str == '\0') 
    {
        // Si nous avons atteint la fin de la chaîne
        return NULL;
    }
    // Avancer jusqu'au prochain délimiteur ou à la fin de la chaîne
    while (*str && !strchr(delim, *str))
    {
        str++;
    }
    if (*str) 
    {
        // Terminer le token en insérant un caractère nul et avancer le pointeur
        *str = '\0';
        str++;
    }
    // Enregistrer la position pour le prochain appel
    *saveptr = str;
    return (token_start);
}

// Exemple d'utilisation
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
}
