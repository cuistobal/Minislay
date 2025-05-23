/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:08:04 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/23 17:17:20 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void	open_all_redirections(t_shell *minishell, t_tokn **redirections, t_tokn **heredocs)
{
	t_tokn	*hcurrent;
	t_tokn	*rcurrent;


	*heredocs = create_token_sub_list(redirections, HDOC); 	
	hcurrent = *heredocs;
	while (hcurrent)
	{
		handle_here_doc(minishell, hcurrent);
		move_pointer(&hcurrent);
	}
	rcurrent = *redirections;
	while (rcurrent)
	{
		move_pointer(&rcurrent);
	}
}
