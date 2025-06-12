/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:26:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:21:59 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static int	print_new_line(bool newline)
{
	if (newline)
		printf("\n");
	return (SUCCESS);
}

int	builtin_echo(char **argv)
{
	int		i;
	int		j;
	bool	newline;

	i = 1;
	newline = true;
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		newline = false;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	return (print_new_line(newline));
}
