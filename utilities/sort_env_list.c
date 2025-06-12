/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:09:36 by cuistobal         #+#    #+#             */
/*   Updated: 2025/06/12 17:25:45 by ynyamets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static t_env	*merge_sort(t_env *left, t_env *right)
{
	t_env	*sorted;

	sorted = NULL;
	if (!left)
		return (right);
	if (!right)
		return (left);
	if (ft_strcmp(left->var[KEY], right->var[KEY]) < 0)
	{
		sorted = left;
		sorted->next = merge_sort(left->next, right);
	}
	else
	{
		sorted = right;
		sorted->next = merge_sort(left, right->next);
	}
	return (sorted);
}

static t_env	*get_middle_node(t_env *list)
{
	t_env	*slow;
	t_env	*fast;

	slow = list;
	fast = list->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return (slow);
}

static t_env	*sort_list(t_env *list)
{
	t_env	*mid;
	t_env	*temp;
	t_env	*left;
	t_env	*right;

	if (!list || !list->next)
		return (list);
	mid = get_middle_node(list);
	temp = mid->next;
	mid->next = NULL;
	left = sort_list(list);
	right = sort_list(temp);
	return (merge_sort(left, right));
}

t_env	*copy_env_list(t_env *list)
{
	t_env	*copy;
	t_env	*head;
	t_env	*tail;

	head = NULL;
	tail = NULL;
	while (list)
	{
		copy = malloc(sizeof(t_env));
		if (!copy)
			return (free_env_list(head), NULL);
		copy->var[KEY] = NULL;
		copy->var[VALUE] = NULL;
		insert_env_node(&head, &tail, copy);
		if (list->var[KEY])
			copy->var[KEY] = ft_strdup(list->var[KEY]);
		if (list->var[VALUE])
			copy->var[VALUE] = ft_strdup(list->var[VALUE]);
		copy->next = NULL;
		list = list->next;
	}
	return (head);
}

t_env	*sort_env_list(t_env *list)
{
	t_env	*duplicate;

	duplicate = copy_env_list(list);
	return (sort_list(duplicate));
}
