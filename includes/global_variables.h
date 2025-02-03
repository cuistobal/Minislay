/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variables.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:39:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/03 10:44:55 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_VARIABLES_H
# define GLOBAL_VARIABLES_H

//Various states of the parser
# define STATE_NORML 0b00000000
# define STATE_SQUOT 0b00000001
# define STATE_DQUOT 0b00000010
# define STATE_SSHEL 0b00000100
# define STATE_SREDI 0b00001000
# define STATE_HREDI 0b00010000
# define STATE_SSHEL 0b00100000
# define STATE_ERROR 0b01000000

//Tokens definition
# define OPAR '('
# define CPAR ')'
# define SQTE '''
# define DQTE '"'
# define PIPE '|'
# define AMPR '&'
# define IRDR '<'
# define ORDR '>'
# define DOLL '$'

extern char	g_hash[4] = {OPAR, SQTE, DQTE, CPAR};

#endif
