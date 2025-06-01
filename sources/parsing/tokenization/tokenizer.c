/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:02:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/01 09:32:17 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Making this stew fit the norminette recipe. IYKYK FRFR
static bool	norminette(const char input, int *type, char *quote, bool check)
{
	if (*quote)
	{
        if (input == *quote)
			*quote = INIT;
	}
	else
	{
		if (is_quote(input))
           	*quote = input;
		else if (isspace(input))
			return (false);
		else if (input == '=' && check)
			set_state(type, EQUL);
	}
	return (true);
}

static void	expansion_flags(char input, bool *dollar, int *type, char quote)
{
    if (*type & WORD)
    {
	    if (!*dollar && quote != '\'' && input == '$')
        {
            set_state(type, DOLL);
		    *dollar = true;
        }
        else if (!quote && input == '*')
        {
            if (*dollar)
		        *dollar = false;
            set_state(type, STAR);
        }
    }
}

//We use this fucntion to handle non special characters, hence building words.
//Ungracefully handling the assignements vs words here:
//
//	->	If we get a '=', the word becomes an assignation if the '=' was not 
//		preceded by an expansion inside the current token. Expansions past the
//		'=' are ok though.
//		Also, the token is considered a word if it starts with a '='. And that
//		makes total sense. Btw, this case isnt throwing a syntax error, it's
//		interpreted either as a command, or a command argument down the road.
//
//The function returns NULL if the quote is unclosed, or a duplicated copy of
//the token's memory zone.
static char	*handle_words(const char *input, int *pos, int *type)
{
	int		start;
	char	quote;
	char	*word;	
	bool	dollar;

	quote = INIT;
	start = *pos;
    dollar = false;
	set_state(type, WORD);
	while (input[*pos])
	{
		if (strchr(SPECIAL, input[*pos]) && quote == INIT)
			break;

        expansion_flags(input[*pos], &dollar, type, quote);
		
		if (!norminette(input[*pos], type, &quote, !(dollar && *pos != start)))
			break;
		(*pos)++;
	}
	if (quote)
		return (NULL);
// This is why we have a 1 bit invalid read problem
	return (strndup(input + start, *pos - start));
}

//
static char	*determinism(const char *input, int *pos, int *type)
{
	if (strchr(SPECIAL, input[*pos]))
		return (handle_special_chars(input, pos, type));
	return (handle_words(input, pos, type));
}

//Un static and move to utils
static void	skip_whitespaces(const char *input, int *pos)
{
	while (isspace(input[*pos]))
		(*pos)++;
}

//We use this function to build a token list based on the user's input. If this
//list is valid, its send to the lexer module.
bool	tokenize(t_tokn **head, const char *input, int len)
{
    int 	pos;
	int		type;
	char	*token;
	t_tokn	*current;

	pos = INIT;
	token = NULL;
	current = NULL;
    while (pos < len)
	{
		type = INIT;
		skip_whitespaces(input, &pos);
        if (input[pos] == '\0')
			break;
		token = determinism(input, &pos, &type);
		if (!create_new_token(head, &current, token, type)) 
		{
			free(token);
			token = NULL;
			printf("Tokenization error @ %c for %s", input[pos], input + pos - 1);
			return (false);
		}
    }
	return (true);
}
