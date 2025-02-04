/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:54:45 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/04 11:37:01 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "minislay.h"

#define HASH_SIZE 128

# define OPAR '('
# define CPAR ')'
# define SQTE '\''
# define DQTE '"'
# define PIPE '|'
# define AMPR '&'
# define IRDR '<'
# define ORDR '>'
# define DOLL '$'
# define STAR '*'
# define TABS 9
# define NLIN 10
# define VTAB 11
# define FEED 12
# define CRET 13
# define SPCE 32

enum special
{
	OPAR_E,
	CPAR_E,
	SQTE_E,
	DQTE_E,
	PIPE_E,
	AMPR_E,
	IRDR_E,
	ORDR_E,
	DOLL_E,
	STAR_E,
	TABS_E,
	NLIN_E,
	VTAB_E,
	FEED_E,
	CRET_E,
	SPCE_E,
	SPECIAL_SIZE
};

static	int	is_special(char special_chars[], char c)
{
	int	index;

	index = 0;
	while (index < SPECIAL_SIZE)
	{
		if (c == special_chars[index])
			return (index);
		index++;
	}
	return (SPECIAL_SIZE);
}

static void	init_special_chars(char arr[])
{
	arr[0] = OPAR;
	arr[1] = CPAR;
	arr[2] = SQTE;
	arr[3] = DQTE;
	arr[4] = PIPE;
	arr[5] = AMPR;
	arr[6] = IRDR;
	arr[7] = ORDR;
	arr[8] = DOLL;
	arr[9] = STAR;
	arr[10] = TABS;
	arr[11] = NLIN;
	arr[12] = VTAB;
	arr[13] = FEED;
	arr[14] = CRET;
	arr[15] = SPCE;
}

int	*hash_input(char *user_prompt, int len)
{
	int		index;
	int		*input;
	char	special_chars[SPECIAL_SIZE];

	input = NULL;
	if (user_prompt)
	{
		index = 0;
		init_special_chars(special_chars);
		input = (int *)malloc(sizeof(int) * len);
		if (input)
		{
			index = 0;
			while (index < len)
			{
				input[index] = is_special(special_chars, user_prompt[index]);
				index++;
			}
		}
	}
	return (input);
}

int	main(int argc, char **argv)
{
	int len;
	int	*input;

	input = NULL;
	if (argc == 2)
	{
		len = strlen(argv[1]);
		input = hash_input(argv[1], len);
		if (input)
		{
			for (int i = 0; i < len; i++)
				printf("%d", input[i]);
			free(input);
			printf("\n%s\n", argv[1]);
		}
	}
	return 0;
}
