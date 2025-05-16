/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_tokenization.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:02:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/17 14:13:40 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//CURRENT MODULE IMPLEMENTATION

#include "minislay.h"

//Creates initial words.
static char	*handle_words(const char *input, int *pos)
{
    int		start;
    char	quote;

    start = *pos;
    quote = '\0';
    while (input[*pos])
	{
        if (quote)
		{
            if (input[*pos] == quote)
                quote = '\0';
        }
		else
		{
			if (is_quote(input[*pos]))
            	quote = input[*pos];
			else if (isspace(input[*pos]))
            	break;
		}
        (*pos)++;
    }
	if (quote)
		return (NULL);
    return (strndup(input + start, *pos - start));
}

//Builds a token list based on the user's input. basically whitespaces 
//collapsing
bool tokenize(t_tokn **head, const char *input, int len)
{
    int		pos;
    char	*token;
    t_tokn	*current;

	pos = 0;
	token = NULL;
	current = NULL;
	while (pos < len)
   // while (input[pos])
	{
        while (isspace(input[pos]))
            pos++;
        if (input[pos] == '\0')
            break;
        token = handle_words(input, &pos);
        if (!create_new_token(head, &current, token, WORD))
		{
            free(token);
            return (false);
        }
        free(token);
    }
    return (true);
}

/*	UTILS && TESTS
void print_tokens(t_tokn *node)
{
    while (node)
	{
        printf("%s -> %s\n", node->type, node->value);
        node = node->next;
    }
}

int main(int argc, char **argv)
{
	t_tokn	*temp;
	t_tokn	*tokens;

	temp = NULL;
	tokens = NULL;
    if (argc == 2)
	{
		tokens = tokenize(argv[1], strlen(argv[1]));
    	print_tokens(tokens);
    	while (tokens)
		{
        	temp = tokens;
        	tokens = tokens->next;
        	free(temp->value);
        	free(temp);
    	}
		return (0);
	}
    fprintf(stderr, "Usage: %s \"<command_string>\"\n", argv[0]);
    return (127);
}*/
