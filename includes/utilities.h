/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <chrleroy@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:23:36 by chrleroy          #+#    #+#             */
/*   Updated: 2025/03/02 15:40:13 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

//tokenizer_bools_1.c:
bool	is_amp_pipe(char c);
bool	is_whitespace(char c);
bool	is_var_wild(char c);
bool	is_redir(char c);
bool	is_quote(char c);

//tokenizer_bools_2.c:
bool	is_paren(char c);
bool	is_squotes(char c);
bool	is_dquotes(char c);
bool	is_iredir(char c);
bool	is_oredir(char c);

//state_management.c:
bool	set_state(int *state, int flag);
bool	unset_state(int *state, int flag);
bool	is_state_active(int state, int flag);

//my_strtok_r.c:
char	*my_strtok_r(char *str, const char *delim, char **saveptr);

//tokens_utils1.c:
void	free_tokens(t_tokn *tokens);

//tokens_utils1.c:
void	free_tokens(t_tokn *tokens);

//parsing_utils.c:
void	delete_links(t_pars *parser);
bool	consume_token(t_tokn **current, t_pars *parser);
bool	valid_lexeme(t_tokn *current, int min, int max);

//parser_utils.c:
bool	append_token_tab(t_tokn *tab[], t_tokn *pointer, int token_type);
bool	reset_parser(t_pars *parser, t_tokn *token, int i, t_tree **branch);
bool	define_parser(t_pars **parser, t_tree **ast, t_tokn *tokens);

#endif
