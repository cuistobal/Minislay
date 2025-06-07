/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:37:15 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/03 12:00:24 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || !*s || (s[0] != '_' && (s[0] < 'A' || s[0] > 'Z')
		&& (s[0] < 'a' || s[0] > 'z')))
    {
		write(2, "minislay: export: `", 20);
		write(2, s, strlen(s));
		write(2, "': not a valid identifier\n", 27);
		return (0);
    }
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (s[i] != '_' && (s[i] < 'A' || s[i] > 'Z')
			&& (s[i] < 'a' || s[i] > 'z') && (s[i] < '0' || s[i] > '9'))
        {
		    write(2, "minislay: export: `", 20);
		    write(2, s, strlen(s));
		    write(2, "': not a valid identifier\n", 27);
		    return (0);
        }
		i++;
	}
	return (1);
}

//
static void export_new_variable(t_shell **minishell, char *argument)
{
    t_env   *new;
    t_env   *tail;
    t_env   *head;
    t_avlt  *root;
    
    new = create_env_node(argument);
    if (!new)
        return ;
    head = (*minishell)->envp;
    tail = get_env_tail_node((*minishell)->envp);
    root = (*minishell)->expt;
    insert_env_node(&head, &tail, new); 
    insert_avlt_node(&root, new, strlen(new->var[VALUE]));
}

static bool split_token(char *token, char **key, char **value)
{
    char *equal;

    equal = strchr(token, '=');
    if (equal)
    {
        *key = strndup(token, equal - token);
        *value = strdup(equal + 1);
    }
    else
    {
        *key = strdup(token);
        *value = NULL;
    }
    return (*key && (*value || !equal));
}

//Il faut ajouter la promotion depuis l'environement local
int	export(t_shell **minishell, char **args)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal;
    t_env   *node;

	i = 0;
    key = NULL;
    value = NULL;
	while (args[i])
	{
        node = NULL;
        if (!split_token(args[i], &key, &value))
            return (GENERAL_ERROR);
		else if (is_valid_identifier(key))
        {
            node = get_env_node(*minishell, key, value);
            if (!node)
                export_new_variable(minishell, args[i]);
            else if (value && strcmp(node->var[VALUE], value) != 0)
            {
                free(node->var[VALUE]);
                node->var[VALUE] = strdup(value);
            }
            else if (!value && node->var[VALUE])
            {
                free(node->var[VALUE]);
                node->var[VALUE] = NULL;
            }
        }
        else
        {
            free(key);
            free(value);
            printf("minislay: export: `%s': not a valid identifier\n", args[i]);
            return (GENERAL_ERROR);
        }
        free(key);
        free(value);
		i++;
	}
    if (i == 0)
        pre_order_display((*minishell)->expt); 
	return (SUCCESS);
}
