/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:59:08 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/08 13:54:06 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

t_tokn	*tokenize(const char *input, int len);
bool	lexer(t_tokn *head);
bool	create_new_token(t_tokn **head, t_tokn **current, char *token);

#endif
