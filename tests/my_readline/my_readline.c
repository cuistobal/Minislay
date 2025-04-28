/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:32:51 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/28 09:56:14 by cuistobal        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "my_readline.h"

//
static bool	resize_line(char **line, size_t *len, size_t new_len)
{
	size_t	old_len;
	
	old_len = *len;
	*line = (char *)realloc(*line, sizeof(char) * new_len);
	if (!*line)
		return (false);
	*len = new_len;
	memset(*line + old_len, 0, new_len - old_len);
	return (true);	
}

//
static bool	init_line(char **line, size_t *n)
{
	*line = (char *)malloc(sizeof(char) * MYRL_BUFFER_SIZE);
	if (!*line)
		return (false);
	*n = MYRL_BUFFER_SIZE;
	memset(*line, 0, *n - 1);
	return (true);
}

//
static void	save_term_state(struct termios *old_attr, struct termios *new_attr)
{
    tcgetattr(STDIN_FILENO, old_attr);
    new_attr = old_attr;
    new_attr->c_lflag &= ~(ICANON);
	new_attr->c_cc[VMIN] = 1;
	new_attr->c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, new_attr);
}

/*
static bool	read_and_append(char **line, char *c, size_t *read_count, size_t *n)
{
	*read_count += read(STDIN_FILENO, &c, 1);
	if (*read_count <= 0 || (*c == '\n' || *c == '\r'))
		return (false);
    else if (*read_count + 1 >= *n)
		return (resize_line(line, n, (*n << 1)));
    *line[*read_count - 1] = *c;
	*c = '\0';
	return (true);
}
*/

//
static void	handle_arrow_keys(t_rlhs **history, char **line, char c, char *prompt)
{
	char	*temp;
	char	seq[3];

	temp = *line;
    if (c != '\033')
		return ;
	read(STDIN_FILENO, seq, 2);
	if (strcmp(seq, ARROW_UP))
		navigate_history(history, true);
	else if (strcmp(seq, ARROW_DN))
        navigate_history(history, false);
    if (*line)
        *line = temp;
}

//
char	*my_readline(t_rlhs *history, char *prompt, size_t *n)
{
	char			c;
	char			*line;
    size_t			read_count;
    struct termios	old_attr;
    struct termios	new_attr;

	if (!init_line(&line, n))
		return (NULL);
	c = '\0'; 
	save_term_state(&old_attr, &new_attr);
	write(STDOUT_FILENO, prompt, strlen(prompt)); 
	while (c != '\n' && c != '\r')
	{
        read_count = read(STDIN_FILENO, &c, 1);
        if (read_count <= 0 || (c == '\n' || c == '\r'))
            break;
        else if (c == '\033')
            handle_arrow_keys(&history, &line, c, prompt);
        else
		{
			if (read_count >= *n)
            	resize_line(&line, n, (*n << 1));
        	line[read_count - 1] = c;
		}
		c = '\0';
	}
    return (tcsetattr(STDIN_FILENO, TCSANOW, &old_attr), line);
}
