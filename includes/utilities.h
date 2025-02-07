/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <chrleroy@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:23:36 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/07 12:12:28 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

//my_strtok_r.c:
char	*my_strtok_r(char *str, const char *delim, char **saveptr);

//tokenizer_bools_2.c:
bool	is_paren(char c);
bool	is_squotes(char c);
bool	is_dquotes(char c);
bool	is_iredir(char c);
bool	is_oredir(char c);

//state_management.c:
bool	set_state(t_pars *parser, int flag);
bool	unset_state(t_pars *parser, int flag);
bool	is_state_active(t_pars *parser, int flag);

//tokenizer_bools_1.c:
bool	is_amp_pipe(char c);
bool	is_whitespace(char c);
bool	is_var_wild(char c);
bool	is_redir(char c);

//stack_operations.c:
void	push(t_pars *parser, char c);
char	pop(t_pars *parser);
char	peek(t_pars *parser);

#endif
