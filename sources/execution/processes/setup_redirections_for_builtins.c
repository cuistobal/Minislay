/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections_for_builtins.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:48:08 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/11 16:08:50 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

static void	resetter(struct termios *term, struct termios *term_original, \
		char *tty_path, bool set)
{
	int	fd;

	if (set)
		return ;
	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, term);
		term = term_original;
		tcsetattr(STDIN_FILENO, TCSANOW, term);
	}
	fd = open(tty_path, O_RDWR);
	if (fd >= 0)
	{
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

static void	setter(struct termios *term_original, char **tty_path, \
		t_exec *node, bool set)
{
	if (!set)
		return ;
	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, term_original);
		if (!tty_path)
			*tty_path = ttyname(STDIN_FILENO);
	}
	if (node->redirs[INFILE] != -1)
		dup2(node->redirs[INFILE], STDIN_FILENO);
	if (node->redirs[OUTFILE] != -1)
		dup2(node->redirs[OUTFILE], STDOUT_FILENO);
}

//Cette fonction gère les redirections dans le processus enfant pour les builtins.
//Si set == true, elle duplique les descripteurs de fichiers d'entrée et de sortie
//et les redirige vers les fichiers spécifiés dans node->redirs.
//Si set == false, elle restaure les descripteurs de fichiers d'entrée et de sortie
//aux valeurs d'origine et ferme les descripteurs de fichiers redirigés.
// Elle est utilisée pour les builtins qui nécessitent des redirections, comme 'cd' ou 'export'.
void	setup_redirections_for_builtin(t_exec *node, int original[2], \
		bool set)
{
    //int                     fd;
    struct termios          term;
    static char             *tty_path;
    static struct termios   term_original;

	setter(&term_original, &tty_path, node, set);
	resetter(&term, &term_original, tty_path, set);
}
