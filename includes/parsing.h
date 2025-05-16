/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:59:08 by chrleroy          #+#    #+#             */
/*   Updated: 2025/03/14 10:11:49 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//parse_terminals.c:
bool	parse_assignment(t_tokn **current, t_pars *parser);
bool	parse_argument(t_tokn **current, t_pars *parser);
bool	parse_redirection(t_tokn **current, t_pars *parser);
bool	parse_expression(t_tokn **current, t_pars *parser);

//build_tree.c:
t_tree	*create_tree_node(t_tokn *tokens);
bool	build_ast(t_pars **parser);

//parse_terminals1.c:
bool	argument_or_redirection(t_tokn **current, t_pars *parser);
bool	assignations(t_tokn **current, t_pars *parser);

//parse_non_terminal.c:
bool	parse_simple_command(t_tokn **current, t_pars *parser);
bool	parse_pipeline(t_tokn **current, t_pars *parser);
bool	parse_compound_command(t_tokn **current, t_pars *parser);
bool	parse_command(t_tokn **current, t_pars *parser);

//parse_list.c:
bool	parse_command_list(t_tokn **current, t_pars *parser);
bool	parse_script(t_pars **parser);

//tokenizer.c:
bool	tokenize(t_tokn **head, const char *input, int len);

//modify_tokens.c:
bool	split_assignation_token(t_tokn **token);

//handle_special_chars.c:
char	*handle_special_chars(const char *input, int *pos, int *type);

//create_tokens.c:
t_tokn	*create_token_node(char *value, int type);
void	insert_token(t_tokn **head, t_tokn **current, t_tokn **new);
bool	get_stacked(t_tokn **head, t_tokn *current, int *mask);
bool	create_new_token(t_tokn **head, t_tokn **current, char *token, int type);

#endif
