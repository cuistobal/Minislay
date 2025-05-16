#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2);

char	*extract_key(char *token, int *index, int start)
{
	int	tlen;

	tlen = 0;
	while (token[*index])
	{
		(*index)++;
		if (!isalnum(token[*index]) && token[*index] != '_')
		{
			if (tlen == 0)
			{
				if (token[*index] == '$' || token[*index] == '?')
				{
					tlen++;	
					(*index)++;
				}
				return strndup(token + start, tlen + 1);
			}
			break ;
		}
		tlen++;	
	}
	return strndup(token + start + 1, tlen);
}

char	*handle_assignations(char *token, int *index)
{
	int		start;
	bool	dollar = false;

	start = *index;
	if (token[*index])
	{
		while (token[*index])
		{
			if (token[*index] == '$')
			{
				if (*index == start)
					return extract_key(token, index, start);
				return strndup(token + start, *index - start);	
			}
			(*index)++;
		}
	}
	return (NULL);
}


char	*expand_token(char *token)
{
	int		index;
	char	*temp;
	char	*merged;
	char	*expanded;

	index = 0;
	temp = NULL;
	expanded = NULL;
	while (token[index])
	{
		temp = handle_assignations(token, &index);
		if (temp)
		{
			printf("%s\n", temp);
			merged = ft_strjoin(expanded, temp);
			if (merged)
			{
				free(temp);
				temp = NULL;
				free(expanded);
				expanded = merged;
			}
			else
			{
				free(temp);
				temp = NULL;
				free(expanded);
				expanded = NULL;
				return NULL;
			}
		}
//		printf("t+i		->	%s\n", token + index);
	}
	return (expanded);
}

int	main(int argc, char **argv)
{
	char	*assigned;

	assigned = NULL;
	if (argc > 1)
	{
		argv++;
		while (*argv)
		{
			assigned = expand_token(*argv);
			printf("%s\n", assigned);
			free(assigned);
			assigned = NULL;
			argv++;
		}
	}
	return 0;
}
