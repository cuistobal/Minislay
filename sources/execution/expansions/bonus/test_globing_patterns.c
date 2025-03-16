#include "minislay.h"
//#include "globing.h"

//
void	free_array(char **array, int count)
{
	if (array)
	{
		while (count--)
		{
			free(array[count]);
			array[count] = NULL;
		}
		free(array);
		array = NULL;
	}
}

//
static char	*create_sub_string(const char *string, int length)
{
	if (string)
		return (strndup(string, length));
	return (NULL);
}

//
static char	*handle_words(const char *globing, int *index)
{
	int	start;

	if (globing)
	{
		start = *index;
		while (globing[*index])
		{
			(*index)++;
			if (globing[*index] == '*')
				break ;
		}
		return (create_sub_string(globing + start, *index - start));
	}
	return (false);
}

//
static char	*handle_stars(const char *globing, int *index)
{
	int	start;

	if (globing)
	{
		start = *index;
		while (globing[*index])
		{
			(*index)++;
			if (globing[*index] != '*')
				break ;
		}
		return (create_sub_string(globing + start, 1));
	}
	return (false);
}

//
static char *handle_pattern(char *globing, int *index)
{
	char	*new;

	new = NULL;
	if (globing[*index] == '*')
		new = handle_stars(globing, index);
	else
		new = handle_words(globing, index);
	return (new);
}

//
static bool	valid_pattern(const char globing, char ***patterns, int pindex)
{
	if (globing != '\0')
	{
		free_array(*patterns, pindex);
		return (false);
	}
	return (true);
}

//We use this function to identify the patterns within the the globing variable
char	**identify_globing_patterns(char *globing)
{
	int		index;
	int		pindex;
	char	**patterns;
	
	patterns = NULL;
	if (globing)
	{
		index = 0;	
		pindex = 0;
		while (globing[index])
		{	
			pindex++;
			patterns = (char **)realloc(patterns, sizeof(char *) * (pindex + 1));
			if (patterns)
			{
				patterns[pindex - 1] = handle_pattern(globing, &index);
				patterns[pindex] = NULL;
			/*
				patterns[pindex] = NULL;
				if (globing[index] == '*')
					patterns[pindex - 1] = handle_stars(globing, &index);
				else
					patterns[pindex - 1] = handle_words(globing, &index);
			*/
				if (!patterns[pindex - 1])
					break ;
			}
		}
		valid_pattern(globing[index], &patterns, pindex);
	}
	//error -> invalid globing variable
	return (patterns);
}
/*
//TEST
int	main(int argc, char **argv)
{
	char	*temp;
	int		index;
	int		pindex;
	char	**patterns;

	pindex = 1;
	patterns = NULL;
	if (argc == 2)
	{
		patterns = identify_globing_patterns((const char *)argv[1], &pindex);
		if (patterns)
		{
			index = 0;
			while (patterns[index])
			{
				printf("%s\n", patterns[index]);
				index++;
			}
			free_array(patterns, pindex);
		}
		else
			printf("patterns is NULL.\n");
	}
	else
		printf("Invalid argc. Usage: ./a.out pattern\n");
	return 0;
}*/
