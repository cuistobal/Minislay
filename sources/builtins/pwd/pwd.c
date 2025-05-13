/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:27:56 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/13 18:30:47 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"


int	pwd(t_shel *minishell)
{
	int		count;
	char	*value;
	char	*current;
	char	temp[BUFFER_SIZE];

	count = 0;
	current = NULL;
	memset(temp, 0, BUFFER_SIZE);
	if (getcwd(temp, BUFFER_SIZE))
	{
		current = strdup(temp);
		write(1, current, strlen(current));
		find_key(minishell, &value, "PWD");
		if (value && strncmp(value, current, strlen(value) != 0))
		{
			free(value);
			value = strdup(current);
		}
		free(current);
	}
	write(1, temp, strlen(temp));
	write(1, "\n", 1);
	return (0);
	//APpend error code
}

/*

int	pwd(t_shel *minishell, char **arguments)
{
	int		count;
	char	*value;
	char	*current;
	char	temp[BUFFER_SIZE];

	count = 0;
	current = NULL;
	memset(temp, 0, BUFFER_SIZE);
	while (arguments[count])
	{
		free(arguments[count]);
		arguments[count] = NULL;
		count++;
	}

	if (arguments)
	{
		free(arguments);
		arguments = NULL;
	}
	if (*arguments)
	{
		while (arguments[count])
			count++;
	//	need a proper error management here.
		printf("pwd: expected 0 arguments; got %d\n", count);
		return (-1);
	}
	if (getcwd(temp, BUFFER_SIZE))
	{
		current = strdup(temp);
		write(1, current, strlen(current));
		find_key(minishell, &value, "PWD");
		if (value && strncmp(value, current, strlen(value) != 0))
		{
			free(value);
			value = strdup(current);
		}
		free(current);
	}
	write(1, temp, strlen(temp));
	write(1, "\n", 1);
	return (0);
	//APpend error code
}
*/
