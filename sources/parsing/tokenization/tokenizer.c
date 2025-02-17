/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:02:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/17 15:04:16 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static bool	comply_to_norm(const char *input, int *pos, int *t, int s, char *q)
{
	if (*q)
	{
        if (input[*pos] == *q)
			*q = '\0';
	}
	else
	{
		if (is_quote(input[*pos]))
           	*q = input[*pos];
		else if (isspace(input[*pos]))
			return (false);
		else if (input[*pos] == '=' && *pos > s)
			*t = EQUL; 
	}
	return (true);
}

//We use this fucntion to handle non special characters, hence building words.
static char	*handle_words(const char *input, int *pos, int *type)
{
	int		start;
	char	quote;

	quote = '\0';
	start = *pos;
	*type = WORD;
    while (input[*pos] && !strchr("&|()<>", input[*pos]))
	{
		if (!comply_to_norm(input, pos, type, start, &quote))
			break;
		(*pos)++;
	}
	if (quote)
		return (NULL);
    return (strndup(input + start, *pos - start));
}

//We use this function to build a token list based on the user's input. If this
//list is valid, its send to the lexer module.
bool	tokenize(t_tokn **head, const char *input, int len)
{
    int 	pos;
	int		type;
	char	*token;
	t_tokn	*current;

	pos = 0;
	token = NULL;
	current = NULL;
    while (pos < len)
	{
		type = 0;
        while (isspace(input[pos]))
			pos++;
        if (input[pos] == '\0')
			break;
		else if (strchr("&|()<>", input[pos]))
            token = handle_special_chars(input, &pos, &type);
        else
            token = handle_words(input, &pos, &type);
		if (!create_new_token(head, &current, token, type))
			return (false);
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
