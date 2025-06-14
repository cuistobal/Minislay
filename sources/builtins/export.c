/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:37:15 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/12 17:25:45 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/*
** Updates an existing environment variable node
** - Manages value updates and memory allocation
** - Handles cases where value exists or is NULL
*/
static void	update_env_node(t_env *node, char *value)
{
	if (value && node->var[VALUE] && ft_strcmp(node->var[VALUE], value) != 0)
	{
		free(node->var[VALUE]);
		node->var[VALUE] = ft_strdup(value);
	}
	else if (!value && node->var[VALUE])
	{
		free(node->var[VALUE]);
		node->var[VALUE] = NULL;
	}
	else if (value && !node->var[VALUE])
		node->var[VALUE] = ft_strdup(value);
}

/*
** Processes a single export argument
** - Splits argument into key/value
** - Validates identifier format
** - Creates or updates environment variable
*/
static int	process_export_arg(t_shell **minishell, char *arg)
{
	char	*key;
	char	*value;
	t_env	*node;

	key = NULL;
	value = NULL;
	if (!split_token(arg, &key, &value))
		return (BUILTINS);
	if (!is_valid_identifier(key))
	{
		free(key);
		free(value);
		return (BUILTINS);
	}
	node = get_env_node(*minishell, key);
	if (!node)
		export_new_variable(minishell, arg);
	else
		update_env_node(node, value);
	free(key);
	free(value);
	return (SUCCESS);
}

/*
** Main export builtin function
** - Handles export with no args (prints env)
** - Processes multiple export arguments
** - Returns appropriate exit status
*/
int	export(t_shell **minishell, char **args)
{
	int		i;
	int		status;

	i = 0;
	if (!args[i])
	{
		print_export((*minishell)->envp);
		return (SUCCESS);
	}
	while (args[i])
	{
		status = process_export_arg(minishell, args[i]);
		if (status != SUCCESS)
			return (status);
		i++;
	}
	return (SUCCESS);
}
