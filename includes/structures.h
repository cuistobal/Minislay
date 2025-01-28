/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:51:57 by chrleroy          #+#    #+#             */
/*   Updated: 2025/01/28 12:51:59 by chrleroy         ###   ########.fr       */
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

//We use this enum to track the parser's state
enum parser_state
{
    STATE_NORMAL,       // Standard parsing mode
    STATE_SINGLE_QUOTE, // Inside single quotes
    STATE_DOUBLE_QUOTE, // Inside double quotes
    STATE_REDIR,        // After a redirection operator
    STATE_HEREDOC,      // Handling heredoc input
    STATE_SUBSHELL,     // Inside subshell parentheses
    STATE_ERROR         // Error state
};

#endif
