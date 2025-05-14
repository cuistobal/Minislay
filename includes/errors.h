/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:45:50 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 13:07:37 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define TOKENIZATION "Tokenization error.\n"
# define PARSING "Failed to parse.\n"
# define SYNTAX "Syntax error"
# define UNEXPECTED "unexpected token :"
# define PIPE_FAILED "Pipe failed.\n"
# define MEMALLOC "Malloc failed.\n"
# define DUP_FAILED "dup() failed.\n"
# define RTRD "My brother in CHrist, you are r3t4rd3d.\n"
# define FORK_FAILED "Fork failed\n."
# define INV_COMMAND "Invalid command.\n"
# define INV_ENV "Invalid env.\n"

//Error codes

# define SUCCESS 0
# define GENERAL_ERROR 1
# define BUILTINS 2
# define COMMAND_EXEC 126
# define COMMAND_NOT_FOUND 127
# define DEAD_SIGNAL 130
# define INVALID_EXIT_STATUS 255
# define REDIRECTION_ERROR -1

/*
0: Success. The command or script executed successfully.
1: General errors. This is a generic code for when a command fails.
2: Misuse of shell built-ins. This indicates incorrect usage of a shell command.
126: Command invoked cannot execute. This could be due to permission issues or the command not being executable.
127: Command not found. The specified command does not exist.
128: Invalid exit argument. The exit code specified is out of the valid range (0-255).
130: Script terminated by Control-C. The script was interrupted by the user.
255: Exit status out of range. This indicates that the exit code is outside the valid range of 0-255.
*/

#endif
