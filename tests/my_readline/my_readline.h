/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:06:07 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/02 08:32:46 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_READLINE_H
# define MY_READLINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/time.h>

# define MYRL_BUFFER_SIZE 256
# define ARROW_UP "^[[A"
# define ARROW_DN "^[[B"

typedef struct histo
{
	struct hist	*head;
	struct hist	*tail;
	struct hist	*current;
}	t_rlhs;

typedef struct hist 
{
	char		*line;
	struct hist	*next;
	struct hist	*prev;
}	t_hist;

char	*my_readline(t_rlhs *history, char *prompt, size_t *read);

t_rlhs *create_history_node(void);

void	my_add_history(t_rlhs **history, char *line);

void	navigate_history(t_rlhs **history, bool uparrow);
//	, char **line);

ssize_t	my_rl_replace();

# endif
