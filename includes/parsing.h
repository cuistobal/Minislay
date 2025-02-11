/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:59:08 by chrleroy          #+#    #+#             */
/*   Updated: 2025/02/11 13:16:40 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//# define WORD 0b00000000
# define SUBS 0b00000001
# define PUNC 0b00000010
# define REDI 0b00000100
# define DQOT 0b00001000

bool	tokenize(t_tokn **head, const char *input, int len);
bool	lexer(t_tokn *head);
bool	create_new_token(t_tokn **head, t_tokn **current, char *token, int type);

//tests
bool    validate_syntax(t_tokn *head);

// Function prototypes
bool parse_script(t_tokn *tokens, int *index);
bool parse_command_list(t_tokn *tokens, int *index);
bool parse_command(t_tokn *tokens, int *index);
void parse_simple_command(t_tokn *tokens, int *index);
void parse_pipeline(t_tokn *tokens, int *index);
void parse_compound_command(t_tokn *tokens, int *index);
void parse_assignment(t_tokn *tokens, int *index);
void parse_argument(t_tokn *tokens, int *index);
void parse_redirection(t_tokn *tokens, int *index);
void parse_expression(t_tokn *tokens, int *index);

#endif
