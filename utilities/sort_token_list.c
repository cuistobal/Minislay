/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuistobal <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:09:36 by cuistobal         #+#    #+#             */
/*   Updated: 2025/06/10 14:23:59 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

/* 
** Performs case-insensitive merge sort of two token lists
** - Compares token values ignoring case (bash --posix behavior)
** - Maintains stable sorting for equal values
*/
static t_tokn	*merge_sort(t_tokn *left, t_tokn *right)
{
    t_tokn	*sorted;

    sorted = NULL;
    if (!left)
        return (right);
    if (!right)
        return (left);
    if (strcasecmp(left->value, right->value) < 0)
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

static t_tokn	*get_middle_node(t_tokn *list)
{
    t_tokn	*slow;
    t_tokn	*fast;

    slow = list;
    fast = list->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return (slow);
}

static t_tokn	*sort_list(t_tokn *list)
{
    t_tokn	*mid;
    t_tokn	*temp;
    t_tokn	*left;
    t_tokn	*right;

    if (!list || !list->next)
        return (list);
    mid = get_middle_node(list);
    temp = mid->next;
    mid->next = NULL;
    left = sort_list(list);
    right = sort_list(temp);
    return (merge_sort(left, right));
}

void	sort_token_list(t_tokn **list)
{
    if (!list || !*list)
        return ;
    *list = sort_list(*list);
}