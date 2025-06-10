/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:37:15 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/10 09:19:39 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
static void print_export(t_env *list)
{
    t_env   *head;
    t_env   *sorted; 

    head = sort_env_list(list);
    sorted = head;
    while (sorted)
    {
        printf(EXPORT_PROMPT);
        printf("%s", sorted->var[KEY]);
        if (sorted->var[VALUE])
            printf("=%s", sorted->var[VALUE]);
        printf("\n");
        sorted = sorted->next;
    }
    free_env_list(head);
}

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

    new = create_env_node(argument);
    if (!new)
        return ;
    tail = get_env_tail_node((*minishell)->envp);
    insert_env_node(&(*minishell)->envp, &tail, new);
}

//
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

/* //Il faut ajouter la promotion depuis l'environement local
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
            return (BUILTINS);
		else if (is_valid_identifier(key))
        {
            node = get_env_node(*minishell, key, value);
            if (!node)
                export_new_variable(minishell, args[i]);
            else if (value && node->var[VALUE] && \
					strcmp(node->var[VALUE], value) != 0)
            {
                free(node->var[VALUE]);
                node->var[VALUE] = strdup(value);
            }
            else if (!value && node->var[VALUE])
            {
                free(node->var[VALUE]);
                node->var[VALUE] = NULL;
            }
			else if (value && !node->var[VALUE])
				node->var[VALUE] = strdup(value);
        }
        else
			return (free(key), free(value), BUILTINS); 
        free(key);
        free(value);
		i++;
	}
    if (i == 0)
        print_export((*minishell)->envp);
	return (SUCCESS);
}
 */

 /*
** Updates an existing environment variable node
** - Manages value updates and memory allocation
** - Handles cases where value exists or is NULL
*/
static void	update_env_node(t_env *node, char *value)
{
    if (value && node->var[VALUE] && strcmp(node->var[VALUE], value) != 0)
    {
        free(node->var[VALUE]);
        node->var[VALUE] = strdup(value);
    }
    else if (!value && node->var[VALUE])
    {
        free(node->var[VALUE]);
        node->var[VALUE] = NULL;
    }
    else if (value && !node->var[VALUE])
        node->var[VALUE] = strdup(value);
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
    node = get_env_node(*minishell, key, value);
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