/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:52:44 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/27 15:55:14 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_readline.h"

//test
int main(int argc, char **argv)
{
    size_t	n;
    char	*line;
	t_rlhs	*history;

	line = NULL;
	history = NULL;
	n = MYRL_BUFFER_SIZE;
	if (argc != 2)
		return -1;
	history = create_history_node();
    line = my_readline(history, argv[1], &n);
	while (line)
	{
		if (line)
		{
			my_add_history(&history, line);
			free(line);
			line = NULL;
		}
		line = my_readline(history, argv[1], &n);
	}
	if (!line)
		return (perror("my_readline()"), free(line), -1);
    return 0;
}
