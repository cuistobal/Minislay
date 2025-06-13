/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:02:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/13 17:37:40 by chrleroy         ###   ########.fr       */
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
	bool	dollar;

	quote = INIT;
	start = *pos;
	dollar = false;
	set_state(type, WORD);
	while (input[*pos])
	{
		if (strchr(SPECIAL, input[*pos]) && quote == INIT)
			break ;
		expansion_flags(input[*pos], &dollar, type, quote);
		if (!norminette(input[*pos], type, &quote, !(dollar && *pos != start)))
			break ;
		(*pos)++;
	}
	if (quote)
		return (NULL);
	return (strndup(input + start, *pos - start));
}

//
static char	*determinism(const char *input, int *pos, int *type, bool *init)
{
	static char	prev;
	char		*token;

	token = NULL;
	if (*init)
	{
		*init = false;
		prev = INIT;
	}
	if (!strchr(SPECIAL, input[*pos]))
	{
		prev = INIT;
		token = handle_words(input, pos, type);
	}
	else if (!tokenizer_helper(&prev, input[*pos]))
		return (NULL);
	else
		token = handle_special_chars(input, pos, type);
	if (token)
		prev = *token;
	if (input[*pos] == '\0')
		prev = INIT;
	return (token);
}

//We use this function to build a token list based on the user's input. If this
//list is valid, its send to the lexer module.
bool	tokenize(t_tokn **head, const char *input, int len)
{
	int		pos;
	int		type;
	bool	init;
	char	*token;
	t_tokn	*current;

	pos = INIT;
	token = NULL;
	init = true;
	current = NULL;
	while (pos < len)
	{
		type = INIT;
		while (isspace(input[pos]))
			pos++;
		if (input[pos] == '\0')
			break ;
		token = determinism(input, &pos, &type, &init);
		if (!create_new_token(head, &current, token, type))
			return (free(token), token = NULL, false);
	}
	return (valid_token_list(*head));
}
