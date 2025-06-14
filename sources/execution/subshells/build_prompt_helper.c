/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:45:37 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 15:46:48 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
bool	build_prompt_helper(char **prompt, t_tree *branch)
{
	if (branch->left && !build_prompt(prompt, branch->left))
		return (false);
	if (branch->right && !build_prompt(prompt, branch->right))
		return (false);
	return (true);
}
