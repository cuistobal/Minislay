/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:02:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/09 12:21:33 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Handles quote less explicitly than the previous stack/state approach
static char	*handle_quotes(const char *input, int *pos)
{
	int		start;
	char	quote;
    char	*token;

    quote = input[(*pos)++];
    start = *pos;
    while (input[*pos] && input[*pos] != quote)
		(*pos)++;
    token = (char *)malloc(sizeof(char) * (*pos - start + 3));
    token[0] = quote;
    strncpy(token + 1, input + start, *pos - start);
    token[*pos - start + 1] = quote;
    token[*pos - start + 2] = '\0';
    (*pos)++;
    return (token);
}

//Handles special grammar char	->	Needs some improvments on token type
static char	*handle_special_chars(const char *input, int *pos)
{
	char	*token;

	token = NULL;
    if ((input[*pos] == '&' || input[*pos] == '|') && input[*pos + 1] == input[*pos])
	{
        token = strndup(input + *pos, 2);
        (*pos) += 2;
        return (token);
    } 
    if ((input[*pos] == '>' || input[*pos] == '<') && input[*pos + 1] == input[*pos])
	{
        token = strndup(input + *pos, 2);
        (*pos) += 2;
        return (token);
    }
    token = strndup(input + *pos, 1);
    (*pos)++;
    return (token);
}

//We use this fucntion to handle non special characters, hence building words.
static char	*handle_words(const char *input, int *pos)
{
    int start;

	start = *pos;
    while (input[*pos] && !isspace(input[*pos]) && !strchr("&|()<>'\"", input[*pos]))
		(*pos)++;
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
t_tokn	*tokenize(const char *input, int len)
{
    int 	pos;
	char	*token;
    t_tokn	*head;
	t_tokn	*current;

	pos = 0;
	token = NULL;
	current = NULL;
	head = NULL;
    while (pos < len)
	{
        while (isspace(input[pos]))
			pos++;
        if (input[pos] == '\0')
			break;
        if (input[pos] == '\'' || input[pos] == '"')
            token = handle_quotes(input, &pos);
		else if (strchr("&|()<>", input[pos]))
            token = handle_special_chars(input, &pos);
		else
            token = handle_words(input, &pos);
		create_new_token(&head, &current, token); 
        free(token);
    }
    return (head);
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
