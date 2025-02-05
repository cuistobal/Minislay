/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:51:57 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/05 09:14:38 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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
//We don't actually use it atm

typedef void (*operate)(int *, int);

void increment(int *, int);
void decrement(int *, int);

enum 
{
  INCR,
  DECR
};

struct action
{
	operate act[2];
};

typedef struct parser
{
	char	*input;
	char	*stack;
	char	syntax[4];
    char	state;
}   t_pars;

typedef struct tokens
{
	char			type;	// Modifier pour utiliser un enum type (?)	
	char			*token;
	struct token	*next;
}	t_tokn;

#endif
