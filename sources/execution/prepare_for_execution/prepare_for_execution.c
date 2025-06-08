/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_for_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:04:54 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/08 15:35:25 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
t_exec	*prepare_for_exec(t_shell **m, t_tokn *tokens)
{
	t_exec	*node;

	if (!m || !tokens)
		return (NULL);
	node = (t_exec *)malloc(sizeof(t_exec));
	if (!node)
		return (NULL);
    node->assignations = NULL;
	node->redirections = create_token_sub_list(&tokens, HDOC | IRED | ORED | ARED);
	node->redirs[INFILE] = -1;
	node->redirs[OUTFILE] = -1;
	node->command = get_command_and_arguments(*m, tokens);
	node->environ = get_env(*m);
	node->next = NULL;
	free_tokens(tokens);
	return (node);
}
