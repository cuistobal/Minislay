/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:29:27 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/06 10:40:07 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//create_tokens.c:
bool	create_tokens(t_tokn **tokens, t_pars *parser);

//parsing.c:
bool	parsing(t_tokn **tokens, char *input);

//handle_char.c:
bool	handle_char(t_pars *parser, char *input, int index);

#endif
