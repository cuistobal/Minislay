
//Check if the current token's value contains expansion char and apply scenario
//depedning on quote state.
bool	asses_token(char *token)
{
	char	*key;
	int		klen;
	int		index;
	char	quote;
	char	dollar;

	if (token)
	{
		index = 0;
		while (token[index])
		{
			if (token[index] == '$')
			{
				if (dollar = '$')
					expand_current_pid();
				else
				{
					key = token + index;
					dollar = '$';
				}
			}
			else if (isspace(token[index]))
			{
				//stop key and expand it
			}
			index++;
			dollar = INIT;
		}
	}
	return (token[index]);
}
