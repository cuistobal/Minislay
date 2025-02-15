/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variables.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:39:59 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/11 17:20:46 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_VARIABLES_H
# define GLOBAL_VARIABLES_H

//Not used anymore
//Various states of the parser
# define STATE_NORML 0b00000000
# define STATE_SQUOT 0b00000001
# define STATE_DQUOT 0b00000010
# define STATE_SSHEL 0b00000100
# define STATE_IREDI 0b00001000
# define STATE_OREDI 0b00010000
# define STATE_ERROR 0b00100000
//

//Those status need to be reworked
# define TOKEN_WORD          0
# define TOKEN_ASSIGNMENT    1
# define TOKEN_REDIR_IN      2
# define TOKEN_REDIR_OUT     3
# define TOKEN_APPEND        4
# define TOKEN_HEREDOC       5
# define TOKEN_PIPE          6
# define TOKEN_SINGLE_QUOTE  7
# define TOKEN_DOUBLE_QUOTE  8
# define TOKEN_DOLLAR        9
# define TOKEN_NEWLINE       10
# define TOKEN_EOF           11
# define TOKEN_AND_IF        12
# define TOKEN_OR_IF         13
# define TOKEN_PAREN_OPEN    14
# define TOKEN_PAREN_CLOSE   15
# define TOKEN_WILDCARD      16

/*
//Tokens definition
# define OPAR '('
# define CPAR ')'
# define SQTE '\''
# define DQTE '"'
# define PIPE '|'
# define AMPR '&'
# define IRDR '<'
# define ORDR '>'
# define DOLL '$'
# define EQLS '='
# define STAR '*'
*/

//Tokens definition by list
# define GRAMMAR "()|&><$=*\""
# define IAE "$=*"

//Masks for terminal parser state
# define WORD 0b0000000000000001
# define IRED 0b0000000000000010
# define HDOC 0b0000000000000100
# define ORED 0b0000000000001000
# define ARED 0b0000000000010000
# define PIPE 0b0000000000100000
# define LAND 0b0000000001000000
# define LORR 0b0000000010000000
# define SQTE 0b0000000100000000
# define DQTE 0b0000001000000000
# define DOLL 0b0000010000000000
# define STAR 0b0000100000000000
# define EQUL 0b0001000000000000
# define XXXX 0b0010000000000000
# define YYYY 0b0100000000000000
# define ZZZZ 0b1000000000000000

//Enum for terminal parser state


//Others
# define STACK_SIZE 1

#endif

