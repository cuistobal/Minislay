
//#include "libft.h"
#include "minislay.h"

//Appends s2 to the joined string
static char	*join_s1(const char *s1, char *joined)
{
	size_t	string_index;

	string_index = 0;
	while (s1[string_index] != '\0')
	{
		*joined = s1[string_index];
		string_index++;
		joined++;
	}
	return (joined);
}

//Appends s1 to the joined string
static char	*join_s2(const char *s2, char *joined)
{
	size_t	string_index;

	string_index = 0;
	while (s2[string_index] != '\0')
	{
		*joined = s2[string_index];
		string_index++;
		joined++;
	}
	return (joined);
}

//New version
//Joins 2 string and handle more edge cases
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*joined;
	size_t	size;

	joined = "";
	if (s1 != NULL && s2 != NULL)
	{
		size = strlen(s1) + strlen(s2);
		joined = (char *)malloc(sizeof(char) * (size + 1));
		if (joined)
		{
			join_s1(s1, joined);
			join_s2(s2, joined + strlen(s1));
			joined[size] = '\0';
		}
		return (joined);
	}
	else if (s1 != NULL || s2 != NULL)
	{
		if (s1 != NULL)
			return (strdup(s1));
		return (strdup(s2));
	}
	return (joined);
}

