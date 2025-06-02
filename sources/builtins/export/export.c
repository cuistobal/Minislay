/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:37:15 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/02 09:53:13 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || !*s || (s[0] != '_' && (s[0] < 'A' || s[0] > 'Z')
		&& (s[0] < 'a' || s[0] > 'z')))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (s[i] != '_' && (s[i] < 'A' || s[i] > 'Z')
			&& (s[i] < 'a' || s[i] > 'z') && (s[i] < '0' || s[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

static void	print_export(t_env *env)
{
	while (env)
	{
		if (env->var[0])
		{
			write(1, "declare -x ", 11);
			write(1, env->var[0], strlen(env->var[0]));
			if (env->var[1])
			{
				write(1, "=\"", 2);
				write(1, env->var[1], strlen(env->var[1]));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		env = env->next;
	}
}

//Il faut ajouter la promotion depuis l'environement local
int	export(t_shell *minishell, char **args)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal;

	value = NULL;	
	if (!args || !args[0])
		return (print_export(minishell->envp), SUCCESS);
	i = 0;
	while (args[i])
	{
		equal = strchr(args[i], '=');
		if (equal)
		{
			key = strndup(args[i], equal - args[i]);	

			if (find_key_in_local(minishell->local, &value, key))
			{
				
			}
			else if (!is_valid_identifier(key))
			{
				write(2, "minislay: export: `", 20);
				write(2, args[i], strlen(args[i]));
				write(2, "': not a valid identifier\n", 27);
			}
			else
				update_key_value(minishell, key, equal + 1);
			free(key);
		}
		else if (!is_valid_identifier(args[i]))
		{
			write(2, "minislay: export: `", 20);
			write(2, args[i], strlen(args[i]));
			write(2, "': not a valid identifier\n", 27);
		}
		else
			update_key_value(minishell, args[i], NULL);
		i++;
	}
	return (SUCCESS);
}
