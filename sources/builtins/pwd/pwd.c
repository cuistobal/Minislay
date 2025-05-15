/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:27:56 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/15 22:45:41 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"


int	pwd(t_shell *minishell)
{
	char	temp[BUFFER_SIZE];
	int		len;

	(void)minishell;
	memset(temp, 0, BUFFER_SIZE);
	if (!getcwd(temp, BUFFER_SIZE))
		return (write(2, "minislay: pwd: error\n", 22), ERROR);
	len = strlen(temp);
	write(1, temp, len);
	write(1, "\n", 1);
	return (SUCCESS);
}