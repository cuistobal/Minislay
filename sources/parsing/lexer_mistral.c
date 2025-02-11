/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_mistral.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:27:28 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/11 08:34:12 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Function prototypes
bool parse_script(t_tokn **list);
bool parse_command_list(t_tokn **list);
bool parse_command(t_tokn **list);
bool parse_simple_command(t_tokn **list);
bool parse_pipeline(t_tokn **list);
bool parse_compound_command(t_tokn **list);
bool parse_expression(t_tokn **list);
bool parse_argument(t_tokn **list);
bool parse_redirection(t_tokn **list);
bool match(t_tokn *token, char type);
void consume(t_tokn **list);

bool parse_script(t_tokn **list)
{
    return parse_command_list(list);
}

bool parse_command_list(t_tokn **list)
{
    while (*list != NULL && !match(*list, TOKEN_EOF))
	{
        if (!parse_command(list))
		{
            return false;
        }
        if (match(*list, TOKEN_AND) || match(*list, TOKEN_OR))
		{
            consume(list);
        }
		else
		{
            break;
        }
    }
    return true;
}

bool parse_command(t_tokn **list)
{
    if (match(*list, TOKEN_LPAREN))
	{
        return parse_compound_command(list);
    }
	else if (match(*list, TOKEN_PIPE))
	{
        return parse_pipeline(list);
    }
	else
	{
        return parse_simple_command(list);
    }
}

//Non
bool parse_simple_command(t_tokn **list)
{
    while (match(*list, TOKEN_WORD) && match((*list)->next, TOKEN_ASSIGN))
	{
        consume(list);  // Consume WORD
        consume(list);  // Consume '='
        if (!parse_expression(list))
		{
            return false;
        }
    }
    if (match(*list, TOKEN_WORD))
	{
        consume(list);
    }

    while (*list != NULL && !match(*list, TOKEN_EOF) && !match(*list, TOKEN_AND) && !match(*list, TOKEN_OR) && !match(*list, TOKEN_PIPE) && !match(*list, TOKEN_RPAREN))
	{
        if (match(*list, TOKEN_WORD))
		{
            if (!parse_argument(list))
			{
                return false;
            }
        }
		else if (match(*list, TOKEN_REDIRECT_OUT) || match(*list, TOKEN_REDIRECT_APPEND) || match(*list, TOKEN_REDIRECT_IN) || match(*list, TOKEN_REDIRECT_HERE))
		{
            if (!parse_redirection(list))
			{
                return false;
            }
        }
		else
		{
            break;
        }
    }
    return true;
}

bool parse_pipeline(t_tokn **list)
{
    while (*list != NULL && !match(*list, TOKEN_EOF))
	{
        if (!parse_command(list))
		{
            return false;
        }
        if (match(*list, TOKEN_PIPE))
		{
            consume(list);
        }
		else
		{
            break;
        }
    }
    return true;
}

bool parse_compound_command(t_tokn **list)
{
    consume(list);  // Consume '('
    if (!parse_command_list(list))
	{
        return false;
    }
    if (match(*list, TOKEN_RPAREN))
	{
        consume(list);
    } else
	{
        fprintf(stderr, "Expected closing parenthesis.\n");
        return false;
    }
    return true;
}

bool parse_expression(t_tokn **list)
{
    if (match(*list, TOKEN_WORD))
	{
        consume(list);
        return true;
    }
	else
	{
        fprintf(stderr, "Expected expression.\n");
        return false;
    }
}

bool parse_argument(t_tokn **list)
{
    if (match(*list, TOKEN_WORD))
	{
        consume(list);
        return true;
    }
	else
	{
        fprintf(stderr, "Expected argument.\n");
        return false;
    }
}

bool parse_redirection(t_tokn **list)
{
    if (match(*list, TOKEN_REDIRECT_OUT) || match(*list, TOKEN_REDIRECT_APPEND) || match(*list, TOKEN_REDIRECT_IN) || match(*list, TOKEN_REDIRECT_HERE))
	{
        consume(list);
        if (match(*list, TOKEN_WORD))
		{
            consume(list);
            return true;
        }
		else 
		{
            fprintf(stderr, "Expected word after redirection operator.\n");
            return false;
        }
    }
	else
	{
        fprintf(stderr, "Expected redirection operator.\n");
        return false;
    }
}

bool match(t_tokn *token, char type)
{
    return token != NULL && token->type == type;
}

void consume(t_tokn **list)
{
    if (*list != NULL)
	{
        *list = (*list)->next;
    }
}
