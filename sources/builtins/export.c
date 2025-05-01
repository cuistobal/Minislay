/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:20:48 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/01 09:23:04 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	export(t_shel *minishell, char **command)
{
	char	*key;
	char	*value;
	t_env	*node;

	if (!*command)
		print_env();
	key = command[0];
	value = command[1];


		

}
