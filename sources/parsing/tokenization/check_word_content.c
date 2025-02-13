/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:49:32 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/13 17:42:21 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

#include "minislay.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Initialize the sub_type based on the current token's type
static void sub_type_initialisation(t_tokn **token, int *sub_type) {
    *sub_type = 0;
    if (is_state_active((*token)->type, DQTE))
        set_state(sub_type, DQTE);
    else if (is_state_active((*token)->type, SQTE))
        set_state(sub_type, SQTE);
}

// Check for initial special characters and set the state
static void check_initial_special_content(t_tokn **token, int *index) {
    *index = 0;
    if ((*token)->value[*index] == '$')
        set_state(&(*token)->type, DOLL);
    else if ((*token)->value[*index] == '*')
        set_state(&(*token)->type, STAR);
    (*index)++;
}

// Handle the '$' character by creating a new token and splitting the string
static bool handle_dollar(t_tokn **token, int index, int sub_type) {
    t_tokn *new_token = create_node((*token)->value + index, sub_type | DOLL);
    if (new_token) {
        (*token)->value[index] = '\0'; // Null-terminate the current token
        (*token)->next = new_token;
        *token = new_token;
        return true;
    }
    return false; // Memory allocation failed
}

// Handle the '*' character by creating a new token and splitting the string
static bool handle_star(t_tokn **token, int index, int sub_type) {
    t_tokn *new_token = create_node((*token)->value + index, sub_type | STAR);
    if (new_token) {
        (*token)->value[index] = '\0'; // Null-terminate the current token
        (*token)->next = new_token;
        *token = new_token;
        return true;
    }
    return false; // Memory allocation failed
}

// Function to split a word token into meaningful tokens
bool check_word_content(t_tokn **token) {
    int index = 0;
    int sub_type;

    if (*token && (*token)->value) {
        sub_type_initialisation(token, &sub_type);
        check_initial_special_content(token, &index);
        while ((*token)->value[index]) {
            if ((*token)->value[index] == '$') {
                if (!handle_dollar(token, index, sub_type))
                    return false;
                return check_word_content(token);
            } else if ((*token)->value[index] == '*') {
                if (!handle_star(token, index, sub_type))
                    return false;
                return check_word_content(token);
            } else if (isspace((*token)->value[index]) && is_state_active((*token)->type, DOLL | STAR)) {
                // Split the token if a flag is active and whitespace is encountered
                t_tokn *new_token = create_node((*token)->value + index, sub_type);
                if (new_token) {
                    (*token)->value[index] = '\0'; // Null-terminate the current token
                    (*token)->next = new_token;
                    *token = new_token;
                    return check_word_content(token);
                }
                return false; // Memory allocation failed
            }
            index++;
        }
    }
    return (*token != NULL);
}


/*
#include "minislay.h"

// Initialize the sub_type based on the current token's type
static void	sub_type_initialisation(t_tokn **token, int *sub_type)
{
	*sub_type = 0;
	if (is_state_active((*token)->type, DQTE))
		set_state(sub_type, DQTE);
	else if (is_state_active((*token)->type, SQTE))
		set_state(sub_type, SQTE);
}

static void	check_intial_special_content(t_tokn **token, int *index)
{
	*index = 0;
	if ((*token)->value[*index] == '$')
		set_state(&(*token)->type, DOLL);
	else if ((*token)->value[*index] == '*')
		set_state(&(*token)->type, STAR);
	(*index)++;
}

static bool	handle_dollar(t_tokn **token, int index)
{
	t_tokn *new;

	
}

static bool	handle_star(t_tokn **token, int index)
{

}

// Function to split a word token into meaningful tokens
bool	check_word_content(t_tokn **token)
{
    int		index;
    int		sub_type;
    t_tokn	*new_token;

    if (*token && (*token)->value)
	{
        sub_type_initialisation(token, &sub_type);
		check_intial_special_content(token, &index);
        while ((*token)->value[index])
		{
			if (!is_state_active((*token)->type, DOLL | STAR))
			{
            	if ((*token)->value[index] == '$')
					handle_dollar();
            	else if ((*token)->value[index] == '*')
					handle_star();
			}
			else if (isspace((*token)->value[index]))
				c
			index++;
		}
	}
	return (*token != NULL);
}*/
/*			{
                sub_type |= DOLL;
                new_token = create_node((*token)->value + index, sub_type);
                if (new_token) {
                    (*token)->next = new_token;
                    *token = new_token;
                    return check_word_content(token);
                }
                // Memory allocation failed
                return false;
            } else if ((*token)->value[index] == '*') {
                sub_type |= STAR;
                new_token = create_node((*token)->value + index, sub_type);
                if (new_token) {
                    (*token)->next = new_token;
                    *token = new_token;
                    return check_word_content(token);
                }
                // Memory allocation failed
                return false;
            }
            index++;
        }
    }
    return (*token != NULL);
}*/
