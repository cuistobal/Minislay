/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:47:22 by chrleroy          #+#    #+#             */
/*   Updated: 2025/03/16 09:40:52 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Cette fonction compte le nombre de mots presents dans la chaine.
//Chaque suite de char sans separateur est consideree comme etant un mot.
static size_t	ft_countword(char const *s, char c)
{
	size_t		i;
	size_t		word;

	i = 0;
	while (*s)
	{
		word = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			if (!word)
			{
				i++;
				word++;
			}
			s++;
		}
	}
	return (i);
}

//Cette fonction permet d'allouer l espace necessaire & copie le mot dans le
//tableau ou il doit etre split.
static char	*ft_fill(const char *s, char c)
{
	char	*word;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_free(char **dest, int words)
{
	while (words--)
		free(dest[words]);
	free(dest);
	return (0);
}

//Split - i est l'index de debut de mot, la boucle avance grace a j tant que
//le char est != c, on incremente k pour mettre le mot dans le bon sous tab.
//Si l'allocation foire, on envoie le sosu tableau dans ft_free.
char	**ft_split(char const *s, char c)
{
	char	**dest;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!dest)
		return (NULL);
	while (i < ft_strlen(s) && k < ft_countword(s, c))
	{
		while (s[i] == c)
			i++;
		dest[k] = ft_fill(s + i, c);
		if (!dest[k])
			return (ft_free(dest, k));
		k++;
		while (s[i] && s[i] != c)
			i++;
	}
	dest[k] = NULL;
	return (dest);
}
/*

#include <stdio.h>

int	main()
{
	int	i = 0;
	char const *s = "hello!";
	char c = ' ';
	char **dest = ft_split(s, c);
	while (dest[i])
	{
		printf("%s\n", dest[i]);
		free(dest[i]);
		i++;
	}
	free(dest);
}*/
