/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:51:57 by chrleroy          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/03 11:20:20 by chrleroy         ###   ########.fr       */
=======
/*   Updated: 2025/02/03 09:20:02 by chrleroy         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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

//Those one are fine
# define STATE_NORML 0b00000000
# define STATE_SQUOT 0b00000001
# define STATE_DQUOT 0b00000010
# define STATE_SSHEL 0b00000100
# define STATE_SREDI 0b00001000
# define STATE_HREDI 0b00010000
# define STATE_SSHEL 0b00100000
# define STATE_ERROR 0b01000000

//We use this enum to append the right token type
enum token_type
{
    TOKEN_WORD,         // General word or argument
    TOKEN_ASSIGNMENT,   // VAR=value
    TOKEN_REDIR_IN,     // <
    TOKEN_REDIR_OUT,    // >
    TOKEN_APPEND,       // >>
    TOKEN_HEREDOC,      // <<
    TOKEN_PIPE,         // |
    TOKEN_SINGLE_QUOTE, // '
    TOKEN_DOUBLE_QUOTE, // "
    TOKEN_DOLLAR,       // $ or $?
    TOKEN_NEWLINE,      // \n
    TOKEN_EOF,          // End of input
    TOKEN_AND_IF,       // &&
    TOKEN_OR_IF,        // ||
    TOKEN_PAREN_OPEN,   // (
    TOKEN_PAREN_CLOSE,  // )
    TOKEN_WILDCARD      // *
};

typedef enum s_type 
{
	OPAR,
	SQTE,
	DQTE,
	CPAR,
	MISC,
}	t_type;

//We use this enum to track the parser's state
enum parser_state
{
    STATE_NORML,
	STATE_SQUOT,
	STATE_DQUOT,
	STATE_SREDI,
	STATE_HREDI,
	STATE_SSHEL,
	STATE_ERROR,
};

typedef struct parser
{
	char	*input;
	char	*stack;
	char	syntax[4];
    char	state;
}   t_pars;

#endif
