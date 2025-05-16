/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_key_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:27:30 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/13 13:21:24 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	update_key_value(t_shel *minishell, char *key, char *new_value)
{
	char	*value;

	find_key(minishell, &value, key);

	value = new_value;
}
