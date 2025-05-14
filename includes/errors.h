/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:45:50 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/14 09:01:38 by chrleroy         ###   ########.fr       */
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
# define ERROR 127
# define REDIRECTION_ERROR -1
#endif
