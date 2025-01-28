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

#endif
