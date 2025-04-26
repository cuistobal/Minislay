/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:27:56 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/26 14:28:44 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

// Needs a proper implementation too.
//void	pwd(char *current_dir)
void	pwd(void *p1, void *p2)
{
	char	*current;
	char	temp[BSIZE];
	char	*current_dir;
	t_shel	*minishell;

	current = NULL;
	memset(temp, 0, BSIZE);
	minishell = (t_shel *)p1;
	current_dir = (char *)p2;
	if (getcwd(temp, BSIZE))
	{
		current = strdup(temp);
		write(1, current, strlen(current));
		//mettre dans la struct;
	}
	write(1, current_dir, strlen(current_dir));
	//APpend error code
}
