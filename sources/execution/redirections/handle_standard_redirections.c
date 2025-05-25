/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_standard_redirections.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuistobal <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 09:41:28 by cuistobal         #+#    #+#             */
/*   Updated: 2025/05/25 09:58:47 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void    open_infile(t_tokn *redirections)
{
	redirections->type = open((redirections)->value, O_RDONLY);
	if (redirections->type < 0)
		printf("Failed to open %s\n", (redirections)->value);
}

void    open_outfile(t_tokn *redirections)
{
    int fd;

    fd = open(redirections->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	    printf("Unable to open %s\n", (redirections)->value);
	redirections->type = fd;
}

void    open_outfile_append(t_tokn *redirections)
{
	int	fd;

	fd = open((redirections)->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
        printf("Unable to open %s\n", (redirections)->value);
	redirections->type = fd;
}
