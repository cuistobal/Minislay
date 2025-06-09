/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_standard_redirections.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuistobal <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 09:41:28 by cuistobal         #+#    #+#             */
/*   Updated: 2025/06/09 15:23:19 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static int	open_file(char *filename, int mask, int permissions)
{
	int	fd;

	if (mask & O_CREAT)
		fd = open(filename, mask, permissions);
	else
		fd = open(filename, mask);
	if (fd < 0)
    {
        error_message(OPEN_ERROR);
        error_message(filename);
    }
	return (fd);
}

//
int	open_infile(t_tokn *redirections)
{
	int	fd;

	fd = -1;
	if (access(redirections->value, F_OK) != 0)	
		return (printf("Missing file: %s\n", (redirections)->value), fd);
	if (access(redirections->value, R_OK) != 0)
		return (printf("%s%s\n", PERMISSION_ERROR, (redirections)->value), fd);
	return (open_file(redirections->value, O_RDONLY, 0)); 
}

//
int	open_outfile(t_tokn *redirections)
{
	if (access(redirections->value, F_OK) != 0)
		return (open_file(redirections->value, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else 
	{
		if (access(redirections->value, W_OK) == 0)	
			return (open_file(redirections->value, O_WRONLY | O_TRUNC, 0));
		else
			printf("%s%s\n", PERMISSION_ERROR, (redirections)->value);
	}
	return (-1);
}

//
int	open_outfile_append(t_tokn *redirections)
{
	if (access(redirections->value, F_OK) != 0)
		return (open_file(redirections->value, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else 
	{
		if (access(redirections->value, W_OK) == 0)	
			return (open_file(redirections->value, O_WRONLY | O_APPEND, 0));
		else
			printf("%s%s\n", PERMISSION_ERROR, (redirections)->value);
	}
	return (-1);
}

