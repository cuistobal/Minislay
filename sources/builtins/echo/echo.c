/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:26:53 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/26 14:13:02 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Echo built-in. Prints the argument followed by a new_line unless the flag is
//spefied.
//void	echo(const char **arguments, bool flag)
void	echo(void *p1, void *p2)
{
	bool		flag;
	const char 	**arguments;

	flag = (bool)p2;
	arguments = (const char **)p1;
	while (*arguments)
	{
		printf("%s", *arguments);
		if (!flag)
			printf("\n");
		arguments++;
	}
}
