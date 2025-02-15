/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:02:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/15 13:03:06 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Handles quote less explicitly than the previous stack/state approach
static char	*handle_quotes(const char *input, int *pos, int *type)
{
	int		start;
	char	quote;
    char	*token;

    quote = input[(*pos)++];
    start = *pos;
    while (input[*pos] && input[*pos] != quote)
		(*pos)++;
	if (input[*pos])
	{
    	token = (char *)malloc(sizeof(char) * (*pos - start + 3));
		if (token)
		{
    		*token = quote;
    		strncpy(token + 1, input + start, *pos - start);
    		token[*pos - start + 1] = quote;
    		token[*pos - start + 2] = '\0';
			*type = WORD;
			if (quote == '"')
				*type |= DQTE;
			else
				*type |= SQTE;
			(*pos)++;
		}
    	return (token);
	}
	return (NULL);
}

//We use this fucntion to handle non special characters, hence building words.
static char	*handle_words(const char *input, int *pos, int *type)
{
    int start;

	start = *pos;
    while (input[*pos] && !isspace(input[*pos]) && !strchr("&|()<>'\"", input[*pos]))
		(*pos)++;
	*type = WORD;
    return (strndup(input + start, *pos - start));
}

/*
//For now, we don't parse expansions and assignations because they're performed
//dureing the execution phase -source: bash's man-.
//Since we don't collapse quotes while parsing, they can be interpreted whenever
//a WORD token is encountered while executiong -source: bash's man-.
static char	*handle_expansions(const char *input, int *pos)
{

}*/

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
        while (isspace(input[pos]))
			pos++;
        if (input[pos] == '\0')
			break;
        if (input[pos] == '\'' || input[pos] == '"')
            token = handle_quotes(input, &pos, &type);
		else if (strchr("&|()<>", input[pos]))
            token = handle_special_chars(input, &pos, &type);
		//SPlit en 1 fichier contenant les differents cas.
		else
            token = handle_words(input, &pos, &type);
		//printf("%d	&	%s\n", type, token);
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
