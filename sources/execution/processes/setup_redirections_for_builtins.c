/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections_for_builtins.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:48:08 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/11 15:48:27 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minislay.h"

//Cette fonction gère les redirections dans le processus enfant pour les builtins.
//Si set == true, elle duplique les descripteurs de fichiers d'entrée et de sortie
//et les redirige vers les fichiers spécifiés dans node->redirs.
//Si set == false, elle restaure les descripteurs de fichiers d'entrée et de sortie
//aux valeurs d'origine et ferme les descripteurs de fichiers redirigés.
// Elle est utilisée pour les builtins qui nécessitent des redirections, comme 'cd' ou 'export'.
void	setup_redirections_for_builtin(t_exec *node, int original[2], \
		bool set)
{
    int                     fd;
    struct termios          term;
    static char             *tty_path;
    static struct termios   term_original;

    tty_path = NULL;
    if (set)
    {
        if (isatty(STDIN_FILENO))
        {
            tcgetattr(STDIN_FILENO, &term_original);
            if (!tty_path)
                tty_path = ttyname(STDIN_FILENO);
        }
        if (node->redirs[INFILE] != -1)
            dup2(node->redirs[INFILE], STDIN_FILENO);
        if (node->redirs[OUTFILE] != -1)
            dup2(node->redirs[OUTFILE], STDOUT_FILENO);
    }
    else if (tty_path)
    {
        if (isatty(STDIN_FILENO))
        {
            tcgetattr(STDIN_FILENO, &term);
            term = term_original;
            tcsetattr(STDIN_FILENO, TCSANOW, &term);
        }
        fd = open(tty_path, O_RDWR);
        if (fd >= 0)
        {
            dup2(fd, STDIN_FILENO);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
    }
}
