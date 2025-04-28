/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_streams.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:07:56 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/27 11:10:12 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//
void	create_pipeline(int fd[2])
{
	pipe(fd);
}

//
void	redirect_std(int std, int fd)
{
	dup2(std, fd);
}
