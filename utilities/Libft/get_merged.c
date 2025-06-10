/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_merged.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:01:34 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/09 17:54:41 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
char    *get_merged(char **merged, char **temp, char **value)
{
    char    *joined;

    joined = ft_strjoin(*temp, *value);
    if (!joined)
        return (NULL);
    if (*temp && *temp != *merged && *temp != *value)
        free(*temp);
    if (*value && *value != *merged)
        free(*value);
    *temp = NULL;
    *value = joined;
    free(*merged);
    return (joined);
}