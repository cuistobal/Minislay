/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:49:32 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/15 15:56:29 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Initialize the sub_type based on the current token's type
static void	sub_type_initialisation(t_tokn **token, int *sub_type)
{
    *sub_type = 0;
    if (is_state_active((*token)->type, DQTE))
        set_state(sub_type, DQTE);
    if (is_state_active((*token)->type, SQTE))
        set_state(sub_type, SQTE);
    if (is_state_active((*token)->type, WORD))
        set_state(sub_type, WORD);
}

// Check for initial special characters and set the state
static void check_initial_special_content(t_tokn **token, int *index)
{
    *index = 0;
    if ((*token)->value[*index] == '$')
        set_state(&(*token)->type, DOLL);
    else if ((*token)->value[*index] == '*')
        set_state(&(*token)->type, STAR);
    (*index)++;
}

// Handle the '$' character by creating a new token and splitting the string
static bool create_sub_token(t_tokn **token, int index, int sub_type, int mask)
{
    t_tokn *new_token;

	new_token = create_node(strdup((*token)->value + index), sub_type | mask);
    if (new_token)
	{
        (*token)->value[index] = '\0';
		(*token)->next = new_token;
        *token = new_token;
    }
    // Memory allocation failed
    return (new_token != NULL);
}

// Function to split a word token into meaningful tokens. Has to be splited into
// sub functions.
bool	check_word_content(t_tokn **token)
{
    int		index;
    int		sub_type;
    t_tokn	*new_token;

    if (*token && (*token)->value)
	{
        sub_type_initialisation(token, &sub_type);
        check_initial_special_content(token, &index);
        while ((*token)->value[index])
		{
			if ((*token)->value[index] == '$')
			{
           	    if (!create_sub_token(token, index, sub_type, DOLL))
           	        return (false);
           	    return (check_word_content(token));
           	}
			else if ((*token)->value[index] == '*')
			{
           	    if (!create_sub_token(token, index, sub_type, STAR))
           	        return (false);
				return (check_word_content(token));
			}
			else if (isspace((*token)->value[index])) 
			{
				if (is_state_active((*token)->type, DOLL | STAR)) 
				{
					new_token = create_node((*token)->value + index, sub_type);
                	if (new_token)
					{
                	    (*token)->value[index] = '\0';
						(*token)->next = new_token;
                	    *token = new_token;
                		return (check_word_content(token));
                	}
					// Memory allocation failed
                	return (new_token != NULL);
				}
			}
            index++;
        }
    }
    return (*token != NULL);
}
