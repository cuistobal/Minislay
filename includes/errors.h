/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynyamets <ynyamets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:45:50 by chrleroy          #+#    #+#             */
/*   Updated: 2025/06/14 14:52:38 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define BASH "bash: "
# define TOKENIZATION "Tokenization error.\n"
# define PARSING "Failed to parse.\n"
# define SYNTAX "Syntax error: "
# define UNEXPECTED "unexpected token: "
# define PIPE_FAILED "Pipe failed.\n"
# define MEMALLOC "Malloc failed.\n"
# define DUP_FAILED "dup() failed.\n"
# define RTRD "My brother in CHrist, you are r3t4rd3d.\n"
# define FORK_FAILED "Fork failed\n."
# define INV_COMMAND "Invalid command.\n"
# define CMD_NOT_FOUND ": command not found\n"
# define INV_ENV "Invalid env.\n"
# define OPEN_ERROR "Failed to open: "
# define PERMISSION_ERROR "Invalid permissions: "
# define AMBIGUOUS_REDIRECTION ": ambiguous redirection\n"
# define UNMATCHED_PAR "unmatched '('\n"
# define EXPORT1 "minislay: export: `"
# define EXPORT2 "': not a valid identifier\n"
# define SIG_HERE_DOC "bash: warning: here-document delimited by end-of-file \
	(wanted '"
# define MISSING_FILE "Missing file: "

//Error codes

# define MISSING_ERROR -2
# define AMBIGUOUS_ERROR -3
# define PERM_ERROR -4

# define SUCCESS 0
# define GENERAL_ERROR 1
# define PARSING_ERROR 2
# define ERROR 1
# define BUILTINS 2
# define COMMAND_EXEC 126
# define COMMAND_NOT_FOUND 127
# define DEAD_SIGNAL 130
# define INVALID_EXIT_STATUS 255
# define REDIRECTION_ERROR -1
# define EXIT_CODE 55

/*
0:		Success. The command or script executed successfully.
1:		General errors. This is a generic code for when a command fails.
2:		Misuse of shell built-ins. This indicates incorrect usage of a shell 
		command.
126: 	Command invoked cannot execute. This could be due to permission issues 
		or the command not being executable.
127: 	Command not found. The specified command does not exist.
128: 	Invalid exit argument. The exit code specified is out of the valid 
		range (0-255).
130: 	Script terminated by Control-C. The script was interrupted by the user.
255: 	Exit status out of range. This indicates that the exit code is outside 
		the valid range of 0-255.
*/

#endif
