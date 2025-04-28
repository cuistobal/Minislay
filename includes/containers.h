/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   containers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:22:14 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/26 16:29:06 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINERS_H
# define CONTAINERS_H

typedef struct queue
{
	void	*head;
	void	*tail;
}	t_queu;

bool	create_queue_node(t_queu **queue);

typedef struct stack
{
	void	*top;
	
}	t_stck;

typedef struct vector
{
	void	*size;
	void	*head;
	void	*tail;
	void	(* resize)(void *, void *);
}	t_vect;

void	resize_vector(void *, void *);

#endif
