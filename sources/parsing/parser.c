/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:02:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/08 11:02:52 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

t_tokn	*create_node(char *type, char *value)
{
    t_tokn *node;

	node = (t_tokn *)malloc(sizeof(t_tokn));
	if (node)
	{
    	node->type = type;
		//node->value = value ? strdup(value) : NULL;
		node->value = strdup(value);
    	node->next = NULL;
    	return (node);
	}
	return (NULL);
}

//Handles quote less explicitly than the previous stack/state approach
char	*handle_quotes(const char *input, int *pos)
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


char *handle_special_chars(const char *input, int *pos)
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

char *handle_words(const char *input, int *pos)
{
    int start;

	start = *pos;
    while (input[*pos] && !isspace(input[*pos]) && !strchr("&|()<>'\"", input[*pos]))
		(*pos)++;
    return (strndup(input + start, *pos - start));
}

void	create_new_token(t_tokn **head, t_tokn **current, char *token)
{
	t_tokn *new_node;

	new_node = create_node("Token", token);
	if (new_node)
	{
        if (!(*head))
			*head = new_node;
        else
			(*current)->next = new_node;
        *current = new_node;
	}
}

//
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

void print_tokens(t_tokn *node)
{
    while (node)
	{
        printf("%s -> %s\n", node->type, node->value);
        node = node->next;
    }
}

/*
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
