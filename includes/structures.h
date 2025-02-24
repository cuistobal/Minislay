/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:51:57 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/24 08:38:40 by chrleroy         ###   ########.fr       */
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

///////////////////////////////////////////////////////////////////////////////
//																			 //
//									PARSER									 //
//																			 //

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

/*OLD
typedef struct parser
{
	char	*user;
	uint8_t	*hashed;
	char	*stack;
	bool	(*check_type[9])(char);
	char	syntax[4];
    char	state;
	int		top;
	int		capacity;
}   t_pars;*/


// Enum for different character groups
typedef enum e_char_group
{
    GROUP_PAREN,
	GROUP_AMP_PIPE,
	GROUP_IREDIR,
	GROUP_OREDIR,
	GROUP_SQUOTES,
	GROUP_DQUOTES,
	GROUP_VAR_WILD,
	GROUP_WHITESPACE,
	GROUP_OTHER
}	t_char_group;

//Pas besoin
typedef enum
{
    SSTATE,
    USTATE,
    GSTATE,
    CMD_COUNT
}	state_manager;

//Used
typedef struct tokens
{
	int				type;	// Modifier pour utiliser un enum type (?)
	char			*value;
	struct tokens	*next;
}	t_tokn;

/*OLD
typedef struct stack
{
	int		top;
	int		capacity;
	char 	*stack;
}	t_stck;*/

//Used
typedef	struct	tree
{
	struct tokens	*tokens;
	struct tree		*left;
	struct tree		*right;
}	t_tree;

//Used
typedef struct parser
{
	int		state;
	t_tokn	*tokens;
	t_tree	**ast;
}	t_pars;

#endif
