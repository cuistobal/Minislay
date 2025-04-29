/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuistobal <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:54:37 by cuistobal         #+#    #+#             */
/*   Updated: 2025/04/29 19:57:24 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

void    create_pipeline(t_tokn *redirections, int pipefd[2])
{
    if (pipe(pipefd) < 0)
        return ;

}

void    pipe_handler()
{
     
}
