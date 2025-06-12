/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:21:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 20:07:43 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static int	is_numeric(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		else
			i++;
	}
	return (1);
}

//
int	my_exit(char **args)
{
	long	code;

	write(1, "exit\n", 5);
	if (!*args)
		return (SUCCESS);
	if (!is_numeric(args[0]))
	{
		write(2, "minislay: exit: numeric argument required\n", 43);
		return (BUILTINS);
	}
	else if (args[1])
		return (write(2, "minislay: exit: too many arguments\n", 35), );
	else
		code = atol(args[0]);
	code = (code % 256 + 256) % 256;
	return (EXIT_CODE);
}
