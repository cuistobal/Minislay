/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:32:51 by chrleroy          #+#    #+#             */
/*   Updated: 2025/04/27 14:33:50 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "my_readline.h"

//
static void	resize_line(char **line, size_t *len, size_t new_len)
{
	size_t	old_len;
	
	old_len = *len;
	*line = (char *)realloc(*line, sizeof(char) * new_len);
	if (!*line)
		return ;
	*len = new_len;
	memset(*line + old_len, 0, new_len - old_len);
	
}

//
static char	*init_line(size_t *n)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * MYRL_BUFFER_SIZE);
	if (!new)
		return (NULL);
	*n = MYRL_BUFFER_SIZE;
	memset(new, 0, *n - 1);
	return (new);	
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

//
ssize_t	my_readline(char **lineptr, char *prompt, size_t *n)
{
    char		c;
    size_t		total_read;
    ssize_t		read_count;
    struct		termios old_attr;
    struct		termios new_attr;

    if (!*lineptr)
		*lineptr = init_line(n);
	c = '\0'; 
	total_read = 0;
	save_term_state(&old_attr, &new_attr);
	write(STDOUT_FILENO, prompt, strlen(prompt)); 
	while (c != '\n' && c != '\r')
	{
        read_count = read(STDIN_FILENO, &c, 1);
        if (read_count <= 0 || (c == '\n' || c == '\r'))
			break;
      	else if (total_read + 1 >= *n)
			resize_line(lineptr, n, (*n << 1));
        (*lineptr)[total_read++] = c;
		c = '\0';
	}
    tcsetattr(STDIN_FILENO, TCSANOW, &old_attr);
    return (total_read);
}

/*
//test
int main(int argc, char **argv)
{
    char	*line;
    size_t	n;
    ssize_t	read_count;

	line = NULL;
	n = MYRL_BUFFER_SIZE;
	if (argc != 2)
		return -1;
    read_count = my_readline(&line, argv[1], &n);
	if (read_count == -1)
		return (perror("my_readline()"), free(line), -1);	
	if (line)	
	{
		printf("Your line is ->	%s\n", line);
		free(line);	
		line = NULL;
	}
    return 0;
}
*/
