/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 09:55:41 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/10 12:03:54 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void print_export(t_env *list)
{
    t_env   *head;
    t_env   *sorted;

    head = sort_env_list(list);
    sorted = head;
    while (sorted)
    {
        printf("export ");
        printf("%s", sorted->var[KEY]);
        if (sorted->var[VALUE])
            printf("=%s", sorted->var[VALUE]);
        printf("\n");
        sorted = sorted->next;
    }
    free_env_list(head);
}

//
int	is_valid_identifier(const char *s)
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
void export_new_variable(t_shell **minishell, char *argument)
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
bool split_token(char *token, char **key, char **value)
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

