/*
static char	*handle_expansions(const char *input, int *pos, int *type)
{
    int		start;

	start = *pos;
	*type = DOLL;
    while (input[*pos] && !isspace(input[*pos]) && !strchr("&|()<>'\"=", input[*pos]))
	{
		(*pos)++;
		if (input[*pos] == '$')
		{
			if (*pos == start + 1)
				(*pos)++;
			break;
		}	
	}
    return (strndup(input + start, *pos - start));
}

//Precedence rule is enforced, yet what if we get ===== ?
static char *handle_assignations(const char *input, int *pos, int *type)
{
    int start;

    start = *pos;
    if (*pos > 0 && !isspace(input[*pos - 1]))
        *type = EQUL;
    else
        *type = WORD;
    (*pos)++;
    return (strndup(input + start, *pos - start));
}*/
/*
//Handles quote less explicitly than the previous stack/state approach
//The magic number corresponds to the 2 quotes + the '\0' terminating byte.
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
    		return ((*pos)++, token);
		}
	}
	return (NULL);
}*/

