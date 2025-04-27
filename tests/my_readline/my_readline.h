/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:06:07 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/27 14:49:28 by chrleroy         ###   ########.fr       */
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
//# define ARROW_UP
//# define ARROW_DN

typedef struct rl_h
{
	char			*line;
	struct t_rlhs	*next;
	struct t_rlhs	*prev;
}	t_rlhs;

ssize_t	my_readline(char **line, char *prompt, size_t *read);

void	my_add_history(t_rlhs **head, t_rlhs **tail, char *line);

ssize_t	my_rl_replace();

# endif
